//
//  main.cpp
//  503final
//
//  Created by jameshuang on 2019/11/15.
//  Copyright © 2019 jameshuang. All rights reserved.

//  Brief: I've created listnode to store individual stock info and use double linked list to link each of them and to sort (bubble/selection).
//  The text file that I created are: bankAccountHistory.txt/bankCashBalance.txt/transactionHistory.txt/portfolio.txt(individual sotck bought)/totalPorfolioValue.txt(total value of our portfolio)

#include <iostream>
#include <fstream>
#include <string>
#include "listnode.hpp"
#include "doubleLinkedlist.hpp"
#include "StockAccount.hpp"
#include "BankAccount.hpp"
using namespace std;
string day1_price = "Result_1.txt";
string day2_price = "Result_2.txt";
void reset(); 
void manage_start();
void Stock_Account();
void Bank_Account();
void Stock_exe(int);
void Bank_exe(int);
int range_of_choice(int,int);
int main(int argc, const char * argv[]) {
        // reset(); use it when open a whole new account.
        int choose_layer1,bank_choice,stock_choice;
        do {
            manage_start();
            choose_layer1 = range_of_choice(1, 3);
            switch (choose_layer1){
                case 1:
                    do {
                        Stock_Account();
                        stock_choice = range_of_choice(1, 7);
                        Stock_exe(stock_choice);
                    } while (stock_choice!=7);
                    break;
                case 2:
                    do {
                        Bank_Account();
                        bank_choice = range_of_choice(1, 5);
                        Bank_exe(bank_choice);
                    } while (bank_choice!=5);
                    break;
                default:
                    break;
            }
        } while (choose_layer1!=3);
        //Note: test sets are put in a saparate file.
        //StockAccount test;
        //BankAccount test2;
        //cout<<test.buy_shares(day1_price,"GOOG", 1, 100); //trxn fail
        //cout<<test.buy_shares(day1_price,"GOOG", 1, 570);
        //cout<<test.buy_shares(day1_price, "MSFT", 1, 30);
        //cout<<test.buy_shares(day1_price, "YHOO", 1, 16);
        //cout<<test.buy_shares(day1_price, "AAPL", 1, 200);
        //cout<<test.sell_shares(day2_price, "GOOG", 1, 10000); //trxn fail
        //cout<<test.sell_shares(day2_price, "GOOG", 2, 450);  //trxn fail
        //cout<<test.sell_shares(day2_price, "GOOG", 2, 10000); // trxn fail
        //cout<<test.sell_shares(day2_price, "GOOG", 1, 200);
        //test.show_portfolio();
        //test.view_trxn_history();
        //test2.deposit(1000);
        //test2.withdraw(3000);
        //test2.printHistory();
        return 0;
}
    
void reset(){
        //reset cash
        double cashbalance=10000;
        ofstream out;
        out.open("bankCashBalance.txt");
        out << setiosflags(ios::fixed) << setprecision(2);
        out<<cashbalance;
        out.close();
        //reset trxn history
        ofstream out2;
        out2.open("transactionHistory.txt");
        out2 << left << setw(10) << "Event" << left << setw(20) << "Company-Symbol" << left << setw(10) << "Number" << left << setw(10) << "Price" << left << setw(15) << "Totalvalue" << left << setw(10) << "Time" << "\n";
        out2.close();
        //reset porfolio
        time_t seconds;
        seconds = time(NULL);
        ofstream out3;
        out3.open("portfolio.txt");
        out3<< left << setw(20) << "Company-Symbol" << left << setw(10) << "Number" << left << setw(20) << "Price-per-share" << left << setw(10) << "Totalvalue" << "\n";
        //reset totalportolio
        ofstream file;
        file.open("totalPorfolioValue.txt");
        file << std::left << setw(15) << "Totalvalue" << std::left << setw(15) << "Time" << "\n";
        file.close();
        //reset bank_Ac history
        file.open("bankAccountHistory.txt");
        file << left << setw(20) << "Event" << left << setw(20) << "Amount" << left << setw(20) << "Date" << left << setw(20) << "Balance" << "\n";
        file.close();
    }

    void manage_start(){
        cout<<"Welcome to the Account Management System.\n";
        cout<<"Please select an account to access:\n";
        cout<<"1. Stock Portfolio Account\n2. Bank Account\n3. Exit\n\nOption: ";
    }
    //option1
    void Stock_Account(){
        cout<<"Stock Portfolio Account\n\n";
        cout<<"Please select an option\n";
        cout<<"1. Display the price for a stock symbol\n2. Display the current portfolio\n3. Buy shares\n4. Sell shares\n5. View a graph for the portfolio value\n6. View transaction history\n7. Return to previous menu\n\nOption: ";
    }
    //option2
    void Bank_Account(){
        cout<<"Bank Account\n\n";
        cout<<"Please select an option:\n";
        cout<<"1. View account balance\n2. Deposit money\n3. Withdraw money\n4. Print out history\n5. Return to previous menu\n\nOption: ";
    }

    void Stock_exe(int option){
        StockAccount Portfolio;
        srand((unsigned)(time(NULL)));
        int fileNo = rand(); //pick result file in random.
        string fileName;
        if (fileNo % 2 == 1) fileName = day1_price;
        else fileName = day2_price;
        switch (option) {
            case 1:{
                string stock;
                cout<<"Please enter the stock symbol: ";
                cin>>stock;
                Portfolio.show_stock(fileName, stock);
                cout<<endl;
                break;
            }
            case 2:{
                Portfolio.show_portfolio();
                cout<<endl;
                break;
            }
            case 3:{ //buy
                string stock;
                cout << "Please enter the stock symbol you wish to purchase: ";
                cin >> stock;
                int shares;
                cout << "Please enter the number of shares: ";
                cin >> shares;
                double price;
                cout << "Please enter the maximum amount you are willing to pay per share: ";
                cin >> price;

                int outcome = Portfolio.buy_shares(fileName, stock, shares, price);
                switch(outcome){
                    case 0:{
                        break;
                    }
                    case -1:{
                        cout << "Error: Over the market price." << endl;
                        break;
                    }
                    case -2:{
                        cout << "Error: You do not have enough cash." << endl;
                        break;
                    }
                    case -3:{
                        cout << "Error: You do not have enough cash and Over the market price." << endl;
                        break;
                    }
                    case -4:{
                        cout << "Error: Such SYM does not exist." << endl;
                        break;
                    }
                }
                cout << endl;
                break;
            }
            case 4:{ //sell
                string stock;
                cout << "Please enter the stock symbol you wish to sell: ";
                cin >> stock;
                int shares;
                cout << "Please enter the number of shares: ";
                cin >> shares;
                double price;
                cout << "Please enter the maximum amount you are willing to pay per share: ";
                cin >> price;

                int outcome = Portfolio.sell_shares(fileName, stock, shares, price);
                switch(outcome){
                    case 0:{
                        cout << "You have selled " <<shares<<" shares of "<<stock<<" at $"<<price<<" each for a total of "<<price*shares<<endl;
                        break;
                    }
                    case -1:{
                        cout << "Error: Over the market price." << endl;
                        break;
                    }
                    case -2:{
                        cout << "Error: Such SYM does not exist." << endl;
                        break;
                    }
                    case -3:{
                        cout << "Error: Not enough shares to sell "<<stock<<"." << endl;
                        break;
                    }
                }
                cout << endl;
                break;
            }
            case 5:{//print graph
              
                break;
            }
            case 6:{
                Portfolio.view_trxn_history();
                cout<<endl;
                break;
            }
            case 7:{
                break;
            }
            default:
                break;
        }
    }
    void Bank_exe(int option){
        BankAccount bank;
        switch (option) {
            case 1: {
                double cash = bank.get();
                cout << setiosflags(ios::fixed) << setprecision(2);
                cout << "1. You have $" << cash << " in your bank account" << endl;
                break;
            }
            case 2: {
                double amount;
                cout << "Please select the amount you wish to deposit: $" ;
                cin >> amount;
                bank.deposit(amount);
                break;
            }
            case 3: {
                double amount;
                cout << "Please select the amount you wish to withdraw: $";
                cin >> amount;
                double outcome = bank.withdraw(amount);
                if (outcome == -1) {
                    cout << "Error: Not enough CASH." << endl;
                    cout << endl;
                }
                else {
                    cout << "$"<<amount<<" Withdrawn." << endl;
                    cout << endl;
                }
                break;
            }
            case 4: {
                bank.printHistory();
                cout << endl;
                break;
            }
            case 5: {
                break;
            }
        }
    }


int range_of_choice(int start,int end){
    int choice;
    cin>>choice;
    while (choice<start||choice>end) {
        cout<<"Enter a valid choice: ";
        cin>>choice;
    }
    return choice;
}
