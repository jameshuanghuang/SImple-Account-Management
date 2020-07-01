//
//  doubleLinkedlist.hpp
//  503final
//
//  Created by jameshuang on 2019/11/28.
//  Copyright © 2019 jameshuang. All rights reserved.
//

#ifndef doubleLinkedlist_hpp
#define doubleLinkedlist_hpp
#include "listnode.hpp"
#include <stdio.h>
using namespace std;

class doubleLinkedlist {
public:
    doubleLinkedlist() {
        head = 0;tail = 0;mySize = 0;total_val = 0;
    }
    ~doubleLinkedlist() {delete head;delete tail;}

    int getsize();
    double get_totalVal();
    void addToEnd(listnode*);
    void remove(string);//remove SYM
    bool removeFromStart();
    bool removeFromEnd();
    int getshare(string);
    bool increase_share(string,int);
    bool decrease_share(string,int);
    void sort_list_selection();
    void sort_bubble();
    void swap(listnode*,listnode*);
    void test_print();
    void updateportfolio();
private:
    listnode *head;
    listnode *tail;
    int mySize;
    double total_val;
};




#endif /* doubleLinkedlist_hpp */
