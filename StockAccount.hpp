//
//  StockAccount.hpp
//  503final
//
//  Created by jameshuang on 2019/11/26.
//  Copyright © 2019 jameshuang. All rights reserved.
//

#ifndef StockAccount_hpp
#define StockAccount_hpp

#include <stdio.h>
#include "Account.hpp"
#include "doubleLinkedlist.hpp"
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
/* inherit from Account */
class StockAccount: public Account{
    friend class BankAccount;
public:
    StockAccount();
    double get_Mprice(string filename,string SYM); //market price
    double getportvalue();
    int buy_shares(string filename,string SYM,int num_share, double amt);
    int sell_shares(string filename,string SYM,int num_share,double amt);
    void show_stock(string filename,string SYM);
    void show_portfolio();
    void view_trxn_history();
    void getcashbal();
    void viewGraph(); //use Matlab.
    
private:
    doubleLinkedlist *portfolio;
    
    
};

#endif /* StockAccount_hpp */
