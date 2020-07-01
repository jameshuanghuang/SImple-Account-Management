//
//  StockAccount.cpp
//  503final
//
//  Created by jameshuang on 2019/11/26.
//  Copyright © 2019 jameshuang. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include "StockAccount.hpp"
#include "StockAccount.hpp"
#include "BankAccount.hpp"
#include <fstream>
#include <time.h>
#include <iomanip>
//#include "windows.h"
//#include <yvals.h>
#if(_MSC_VER>=1600)
#define _STDC_utf_16__
#endif
#include <vector>
//#include"mex.h"
//#include<engine.h>

#pragma comment(lib,"libmx.lib")
#pragma comment(lib,"libmex.lib")
#pragma comment(lib,"libeng.lib")
using namespace std;


StockAccount::StockAccount(){
    ifstream in("bankCashBalance.txt");
    if (!in.is_open()) {
        cashbalance=10000; //CASH_BALANCE
        ofstream out;
        out.open("bankCashBalance.txt");
        out << setiosflags(ios::fixed) << setprecision(2);
        out<<cashbalance;
        out.close();
    }
    else{
        double temp;
        ifstream in("bankCashBalance.txt");
        in>>temp;
        cashbalance=temp;
        in.close();
    }
    ifstream transaction("transactionHistory.txt");
    if (!transaction.is_open()) {
        ofstream out;
        out.open("transactionHistory.txt");
        out << left << setw(10) << "Event" << left << setw(20) << "Company-Symbol" << left << setw(10) << "Number" << left << setw(10) << "Price" << left << setw(15) << "Totalvalue" << left << setw(10) << "Time" << "\n";
        out.close();
    }
    ifstream Portfolioin("portfolio.txt");
    if (!Portfolioin.is_open()) {
        ofstream out;
        out.open("portfolio.txt");
        out<< left << setw(20) << "Company-Symbol" << left << setw(10) << "Number" << left << setw(20) << "Price-per-share" << left << setw(10) << "Totalvalue" << "\n";
    }
    else{
        string firstline;
        Portfolioin>>firstline>>firstline>>firstline>>firstline;//pass the firstline
        string tempname;
        double tempprice;
        int tempshare;
        double temptotal;
        portfolio = new doubleLinkedlist;
        while (Portfolioin>>tempname>>tempshare>>tempprice>>temptotal) {
            listnode *newNode = new listnode(tempname,tempprice,tempshare);
            portfolio->addToEnd(newNode);
        }
        Portfolioin.close();
    }
}
double StockAccount::get_Mprice(string filename,string SYM){
    ifstream file(filename);
    string stockSymbol;
    double price;
    string trash;
    while (!file.eof()) {
        file >> stockSymbol;
        if (stockSymbol == SYM) {
            break;
        }
        file>>price;
        file>>trash;
    }
    if (file.eof()){
        cout << "Error: SYM not found." << endl;
        return -1;
    }
    file >> price;
    return price;
}
void StockAccount::show_stock(string filename,string SYM){
    double price = get_Mprice(filename,SYM);
    if (price!=-1) {
        cout << "Company-symbol price per share" << endl;
        cout << setiosflags(ios::fixed) << setprecision(2);
        cout << left << setw(14)<< SYM << " $" << price << endl;
    }
}
void StockAccount::show_portfolio(){
    getcashbal();
    cout<<"Cash balance = $"<<cashbalance<<endl;
    string company;
    string num;
    string price;
    string total;
    ifstream in("portfolio.txt");
    while (in>>company>>num>>price>>total) {
        cout<<left << setw(20) << company << left << setw(10) << num << left << setw(20) << price << left << setw(10) << total << "\n";
    }
    cout<<"Total portfolio value: $"<<cashbalance+portfolio->get_totalVal()<<endl;
}
//include transaction becareful
int StockAccount::buy_shares(string filename, string SYM, int num_share, double buy_price){
    ifstream file(filename);
    int condition;//set 5 conditions: 0,success -1,-2,-3,-4 fail. return condition
    string stockSymbol;
    double price;
    string trash;
    while (!file.eof()) {
        file >> stockSymbol;
        if (stockSymbol == SYM) {
            break;
        }
        file>>price;
        file>>trash;
    }
    if (file.eof()){
        cout << "Error: SYM not found." << endl;
        return -4;
    }
    file >> price;
    getcashbal();//check cash balance
    if (num_share*price<=cashbalance && price<=buy_price){//allow to buy
        if (!portfolio->increase_share(SYM, num_share)) {
            listnode *newSYM = new listnode(SYM,price,num_share); //not in portforlio, buy new stock
            portfolio->addToEnd(newSYM);
        }
        int sortchoice;//allow user to choose a sorting method
        cout<<"How would you like to sort?\n";
        cout<<"1. bubble sort\n"<<"2. selection sort\n";
        cout<<"Enter you choice:";
        cin>>sortchoice;
        while (sortchoice<1||sortchoice>2) {
            cout<<"Enter a 1 or 2";
            cin>>sortchoice;
        }
        if (sortchoice==1) {
            portfolio->sort_bubble();
        }
        else{
            portfolio->sort_list_selection();
        }
        //set transaction history
        cout<<"You purchased " <<num_share<<" share(s) of "<< SYM <<" at $"<<price<<" each for a total of "<<price*num_share<<endl;
        ofstream file;
        file.open("transactionHistory.txt",ios::app);
        //get time;
        time_t seconds;
        seconds = time(NULL);
        char time[12];
        tm * timeinfo;
        timeinfo = localtime(&seconds);
        strftime(time, 100, "%X", timeinfo);
        file << setiosflags(ios::fixed) << setprecision(2);
        double stockValue = price * num_share;
        file << left << setw(10) << "Buy" << left << setw(20) << SYM << left << setw(10) << num_share<< left << setw(1) << "$" << left << setw(9) << price << left << setw(1) << "$" << left << setw(14) << stockValue << left << setw(10) << time << "\n";
        file.close();
        //update portfolio
        portfolio->updateportfolio();
        //update bank transaction
        BankAccount *bank = new BankAccount();
        bank->withdraw(price * num_share); //use market order, not buy_price * num_share
        delete bank;
        condition=0;
    }
    else if(price>buy_price){
        condition=-1;
    }
    else if (num_share*price>cashbalance){
        condition=-2;
    }
    else{
        condition=-3;
    }
    return condition;
}
int StockAccount::sell_shares(string filename, string SYM, int num_share, double sell_price){
    //you sell at your selling price (not market price)
    ifstream file(filename);
    int condition=1;//set 5 conditions: 0,success -1,-2,-3,-4 fail. initial=-1
    string stockSymbol;
    double price;
    string trash;
    
    while (!file.eof()) {
        file >> stockSymbol;
        if (stockSymbol == SYM) {
            break;
        }
        file>>price;
        file>>trash;
    }
    if (file.eof()){
        cout << "Error: SYM not found." << endl;
        return -2;
    }
    file >> price;
    if (price<sell_price){
        return -1;
    }
    if (portfolio->decrease_share(SYM, num_share)) {
        int sortchoice;//allow user to choose a sorting method
        cout<<"Choose a sorting method\n";
        cout<<"1. bubble sort\n"<<"2. selection sort\n";
        cout<<"Enter you choice:";
        cin>>sortchoice;
        while (sortchoice<1||sortchoice>2) {
            cout<<"Enter 1 or 2";
            cin>>sortchoice;
        }
        if (sortchoice==1) {
            portfolio->sort_bubble();
        }
        else{
            portfolio->sort_list_selection();
        }
        //set the transaction history
        ofstream file;
        file.open("transactionHistory.txt",ios::app);
        //get time;
        time_t seconds;
        seconds = time(NULL);
        char time[12];
        tm * timeinfo;
        timeinfo = localtime(&seconds);
        strftime(time, 100, "%X", timeinfo);
        file << setiosflags(ios::fixed) << setprecision(2);
        double stockValue = price * num_share;
        file << left << setw(10) << "SELL" << left << setw(20) << SYM << left << setw(10) << num_share<< left << setw(1) << "$" << left << setw(9) << price << left << setw(1) << "$" << left << setw(14) << stockValue << left << setw(10) << time << "\n";
        file.close();
        //update portfolio
        portfolio->updateportfolio();
        //udpate bank transaction
        BankAccount *bank = new BankAccount();
        bank->deposit(sell_price * num_share);
        delete bank;
        condition=0;
    }
    else{
        condition=-3;
    }
    return condition;
}
void StockAccount::getcashbal(){
    double temp;
    ifstream in("bankCashBalance.txt");
    in>>temp;
    cashbalance=temp;
    in.close();
}
double StockAccount::getportvalue(){
    return portfolio->get_totalVal(); //get_totalVal from doublelist
}

void StockAccount::view_trxn_history() {
    char line[100];
    ifstream in;
    in.open("transactionHistory.txt");
    while (!in.eof()) {
        in.getline(line, 200);
        cout << line << endl;
    }
    in.close();
}
/*
void StockAccount:: viewGraph(){
    Engine* ep;
    ep = engOpen(NULL);
    if (ep == NULL)
    {
        cout << "ERROR:engine open failed" << endl;
        exit(1);
    }

    //Input data from tatalPortfolioValue.
    vector<double> timeVec;
    vector<double> valueVec;


    //Open tatalPortfolioValue and read data to vector value.
    ifstream portIn("totalPorfolioValue.txt");
    string firstline;
    portIn >> firstline >> firstline >> firstline;
    int time;
    double value;
    int counter = 0;

    while (!portIn.eof()) {
        if (counter % 2 == 0) {
            portIn >> value;
            valueVec.push_back(value);
        }
        if (counter % 2 == 1) {
            portIn >> time;
            timeVec.push_back(time);
        }
        counter++;
    }
    int timeSize = timeVec.size();
    int valueSize = valueVec.size();
    double* timeArray = new double[timeSize];
    double* valueArray = new double[valueSize];

    for (int i = 0; i < timeVec.size(); i++) {
        timeArray[i] = timeVec[i];
        valueArray[i] = valueVec[i];
    }

    mxArray* A;
    A = mxCreateDoubleMatrix(1, timeVec.size(), mxREAL);
    memcpy((void*)mxGetPr(A), (void*)timeArray, sizeof(double) * timeVec.size());
    mxArray* B;
    B = mxCreateDoubleMatrix(1, timeVec.size(), mxREAL);
    memcpy((void*)mxGetPr(B), (void*)valueArray, sizeof(double) * timeVec.size());

    engPutVariable(ep, "time", A);
    engPutVariable(ep, "value", B);
    engEvalString(ep, "plot(time, value)");

    system("pause");

    mxDestroyArray(A);
    engEvalString(ep, "close;");

    engClose(ep);
}
*/

