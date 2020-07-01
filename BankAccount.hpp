//
//  BankAccount.hpp
//  503final
//
//  Created by jameshuang on 2019/11/16.
//  Copyright © 2019 jameshuang. All rights reserved.
//

#ifndef BankAccount_hpp
#define BankAccount_hpp
#include "Account.hpp"
#include <stdio.h>
#include <string>
using namespace std;
/* inherit from Account */
class BankAccount: public Account{
public:
       BankAccount();
       double withdraw(double);
       void storeTotalPortfolioValue();
       void deposit(double);
       void printHistory();
       void getcashbal();
       double get();
    
};



#endif /* BankAccount_hpp */
