//
//  BankAccount.cpp
//  503final
//
//  Created by jameshuang on 2019/11/16.
//  Copyright © 2019 jameshuang. All rights reserved.
//

#include "BankAccount.hpp"
#include "StockAccount.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

/* constructor */
BankAccount::BankAccount() {
    ifstream in("bankCashBalance.txt");
    if (!in.is_open()) {
        cashbalance = 10000;
        ofstream file;
        file.open("bankCashBalance.txt");
        file << setiosflags(ios::fixed) << setprecision(2);
        file << 10000 << "\n";
        file.close();

        /*Initialized the bank account history file.*/
        file.open("bankAccountHistory.txt", ios::app);
        file << left << setw(20) << "Event" << left << setw(20) << "Amount" << left << setw(20) << "Date" << left << setw(20) << "Balance" << "\n";
        file.close();
    }
    else {
        double cash;
        ifstream OpenFile("bankCashBalance.txt");
        OpenFile >> cash;
        cashbalance = cash;
        OpenFile.close();
    }
}
double BankAccount::withdraw(double amount) {
    getcashbal();
    if (amount > cashbalance) {
        return -1;
    }
    cashbalance -= amount;
    ofstream file;
    file.open("bankCashBalance.txt");
    file << cashbalance << "\n";
    file.close();
    file.open("bankAccountHistory.txt", ios::app);
    //calcuate the date.
    time_t seconds;
    seconds = time(NULL);
    char date[12];
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    strftime(date, 100, "%D", timeinfo);
    file << setiosflags(ios::fixed) << setprecision(2);
    file << std::left << setw(20) << "Withdrawal" << std::left << setw(1) << "$" << std::left << setw(19) << amount << std::left << setw(20) << date << std::left << setw(20) << cashbalance << "\n";
    file.close();
    storeTotalPortfolioValue();
    return amount;
}
void BankAccount::deposit(double amount) {
    getcashbal();
    cashbalance += amount;
    ofstream file;
    file.open("bankCashBalance.txt");
    file << cashbalance << "\n";
    file.close();
    file.open("bankAccountHistory.txt", ios::app);
    //calcuate the date.
    time_t seconds;
    seconds = time(NULL);
    char date[12];
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    strftime(date, 100, "%D", timeinfo);
    file << setiosflags(ios::fixed) << setprecision(2);
    file << left << setw(20) << "Deposit" << left << setw(1) << "$" << left << setw(19) << amount << left << setw(20) << date << left << setw(20) << cashbalance << "\n";
    storeTotalPortfolioValue();
    file.close();
}
void BankAccount::storeTotalPortfolioValue() {
    //calcuate current time.
    time_t seconds;
    seconds = time(NULL);
    //char date[12];
    //tm * timeinfo;
    //timeinfo = localtime(&seconds);
    //strftime(date, 100, "%D", timeinfo);  seconds->date below
    
    StockAccount *stock = new StockAccount();
    double portval = stock->getportvalue();
    ofstream file("totalPorfolioValue.txt", ios::app);
    if (!file.is_open()) {
        ofstream file;
        file.open("totalPorfolioValue.txt", ios::app);
        file << std::left << setw(15) << "Totalvalue" << std::left << setw(15) << "Time" << "\n";
        file << setiosflags(ios::fixed) << setprecision(2);
        file << std::left << setw(15) << cashbalance+portval<< std::left << setw(15) << seconds << "\n";
        file.close();
    }
    else {
        file << setiosflags(ios::fixed) << setprecision(2);
        file << std::left << setw(15) << cashbalance+portval<< std::left << setw(15) << seconds << "\n";
        file.close();
    }
}
void BankAccount::printHistory() {
    char line[100];
    ifstream inbank("bankCashBalance.txt");
    inbank.getline(line, 100);
    cout << "The cash balance of this account is: " << line << "." << endl;
    cout << endl;

    ifstream in("bankAccountHistory.txt");
    while (!in.eof()) {
        in.getline(line, 100);
        cout << line << endl;
    }
    in.close();
}
void BankAccount::getcashbal(){
    double temp;
    ifstream in("bankCashBalance.txt");
    in>>temp;
    cashbalance=temp;
    in.close();
}
double BankAccount::get(){
    getcashbal();
    return cashbalance;
}
