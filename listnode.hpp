//
//  listnode.hpp
//  503final
//
//  Created by jameshuang on 2019/12/6.
//  Copyright © 2019 jameshuang. All rights reserved.
//

#ifndef listnode_hpp
#define listnode_hpp
#include <iostream>
#include <string>
#include <stdio.h>
class doubleLinkedlist;
using namespace std;
class listnode{
    friend class doubleLinkedlist;
public:
    listnode(string SYM, double price, int number);//name is the symbol of stock,no is num of share
    void add_share(int);
    void deduct_share(int);
    double getValue(); //the value of this stock
private:
    string stock_Name;
    int num_Share;
    double stock_Price;
    listnode *next;
    listnode *pre;
};
#endif /* listnode_hpp */
