//
//  listnode.cpp
//  503final
//
//  Created by jameshuang on 2019/12/6.
//  Copyright © 2019 jameshuang. All rights reserved.
//

#include "listnode.hpp"
#include <string>
//constructor
listnode::listnode(string SYM,double price,int number)
:stock_Name(SYM), num_Share(number), stock_Price(price){
    this->next=0;
    this->pre=0;
}
//changing the share of this stock
void listnode::add_share(int num){
    num_Share+=num;
    //decrease if negative and less than original amount
}
void listnode::deduct_share(int num){
    num_Share-=num;
}
//return the value of this stock
double listnode::getValue(){
    return num_Share*stock_Price;
}
