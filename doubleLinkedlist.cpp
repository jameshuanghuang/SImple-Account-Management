//
//  doubleLinkedlist.cpp
//  503final
//
//  Created by jameshuang on 2019/11/28.
//  Copyright © 2019 jameshuang. All rights reserved.
//

#include "doubleLinkedlist.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

/*constructor*/
int doubleLinkedlist::getsize(){
    return mySize;
}
double doubleLinkedlist::get_totalVal(){
    return total_val;
}
//we store what we bought at the end of portfolio
void doubleLinkedlist::addToEnd(listnode *newnode){
    if (mySize==0) { //set pre and next to 0
        head = tail = newnode;
    }
    else{
        tail->next = newnode;
        newnode->pre = tail; //connect new to tail with pre node
        tail = newnode;//set tail to be newnode
    }
    mySize++;
    total_val+=newnode->getValue();//portafolio increased
}
//remove_check function
bool doubleLinkedlist::removeFromStart()
{
    if (mySize==0) {
        return false;
    }
    else{
        listnode *temptr = head;// placehoder to store address of head
        if (this->mySize==1) {
            head=tail=0;
        }
        else{
            head = head->next;// point to next
            head->pre=0;// set former ptr to 0
        }
        total_val-=temptr->getValue();
        delete temptr;
        mySize--;
        return true;
    }
}
bool doubleLinkedlist::removeFromEnd()
{
    if (mySize==0) {
        return false;
    }
    else{
        listnode *temptr = tail;;
        if (mySize==1) {
            head = tail = 0;
        }
        else{
            tail = tail->pre;
            tail->next=0;
        }
        total_val-=temptr->getValue();
        delete temptr;
        mySize--;
        return true;
    }
}

void doubleLinkedlist::remove(string SYM)//to liquidate
{
    if (mySize==0) {
           cout<<"Error: Nothing in portfolio.\n";
       }
    else if(SYM==head->stock_Name){
           this->removeFromStart();
       }
    else if (SYM==tail->stock_Name){
           this->removeFromEnd();
       }
    else{
           listnode *cptr=head;
           while (cptr!=tail&&cptr->stock_Name!=SYM) {
               cptr=cptr->next;
           }
           if (cptr==tail) {
               cout<<"Error: Such SYM does not found.";
           }
           else{
               listnode *temptr=cptr;
               cptr->pre->next = cptr->next;//set pres next pointer
               cptr->next->pre = cptr->pre;//set nexts pre pointer
               total_val-=temptr->getValue();
               delete temptr;
               mySize--;
           }
       }
}
//find the company's share,return -1 if shares not found
int doubleLinkedlist::getshare(string SYM){
    listnode *cptr = head;
    while (cptr!=0) {
        if (cptr->stock_Name==SYM) {
            return cptr->num_Share;
        }
        cptr = cptr->next;
    }
    return -1;
}
//either increase the share or add new stock to the end of portfolio.
bool doubleLinkedlist::increase_share(string SYM,int amt){
    listnode *cptr = head;
    while (cptr!=0) {
        if (cptr->stock_Name==SYM) {
            cptr->add_share(amt);
            total_val+=cptr->getValue();
            return true;
        }
        cptr = cptr->next;
    }
    return false;
}
//decrease the share
bool doubleLinkedlist::decrease_share(string SYM,int amt){
    listnode *cptr = head;
    while (cptr!=0) {
        if (cptr->stock_Name==SYM) {
            if (cptr->num_Share<amt) {
                return false;
            }
            else if (cptr->num_Share==amt){
                remove(SYM);//if sell out, remove the information
            }
            else{
                cptr->deduct_share(amt);
            }
            total_val-=cptr->getValue();
            return true;
        }
        cptr = cptr->next;
    }
    return false;
}
void doubleLinkedlist::sort_list_selection()
{
    listnode *cptr = head;
    listnode *smallest;
    while (cptr!=tail) {
        cout<<1;
        smallest = cptr;
        listnode *cptr2 = cptr->next;
        while (cptr2!=0) {
            if (cptr2->getValue() < smallest->getValue()) {
                smallest = cptr2;
            }
            cptr2 = cptr2->next;
        }
        if (cptr!=smallest) {
            swap(cptr, smallest);
            cptr=smallest;//switch back.
        }
        cptr = cptr->next;
    }
}
void doubleLinkedlist::sort_bubble(){
    if (mySize>1) {
        for (int i=1; i<=mySize-1; i++) {
            listnode *cptr = head;
            for(int j=0;j<=mySize-1-i;j++) {
                if (cptr->getValue() < cptr->next->getValue()) {
                    swap(cptr, cptr->next);
                    cptr=cptr->pre;//switch back
                }
                cptr=cptr->next;
            }
        }

    }
}

void doubleLinkedlist::swap(listnode *to, listnode *from){
    //separate case by head-mid-tail (4) X next or not next (2)  X  sym head and tail (2) = 12
    //mid to head
    if (to==head&&from!=tail) {
        if (to->next==from) { //if next to
            from->pre->next=from->next;
            from->next->pre=from->pre;
            from->pre=0;
            from->next=head;
            head->pre=from;
            head=from;
        }
        else{
            from->pre->next=from->next;
            from->next->pre=from->pre;
            listnode *temp = to->next;
            to->next = from->next;
            to->pre = from->pre;
            to->next->pre= to;
            to->pre->next = to;
            from->next = temp;
            from->next->pre=from;
            from->pre = 0;
            head = from;
        }
    }
    //tail to mid
    else if (to!=head && from==tail){
        if (from->pre==to) { //if next to
            to->pre->next=to->next;
            to->next->pre=to->pre;
            to->next=0;
            to->pre=tail;
            tail->next=to;
            tail=to;
        }
        else{
            to->pre->next=to->next;
            to->next->pre=to->pre;
            listnode *temp = from->pre;
            from->pre = to->pre;
            from->next = to->next;
            from->next->pre = from;
            from->pre->next = from;
            to->pre = temp;
            to->pre->next=to;
            to->next = 0;
            tail = to;
        }
    }
    //mid to tail
    else if (to==tail && from!=head){
        if (to->pre==from) {
            from->pre->next=from->next;
            from->next->pre=from->pre;
            from->next=0;
            from->pre=tail;
            tail->next=from;
            tail=from;
        }
        else{
            
            from->pre->next=from->next;
            from->next->pre=from->pre;
            listnode *temp = to->pre;
            to->pre = from->pre;
            to->next = from->next;
            to->next->pre = to;
            to->pre->next = to;
            from->pre = temp;
            from->pre->next=from;
            from->next = 0;
            tail = from;
        }
    }
    //head to mid
    else if (to!=tail && from==head){
        if (from->next==to){
            to->pre->next=to->next;
            to->next->pre=to->pre;
            to->pre=0;
            to->next=head;
            head->pre=to;
            head=to;
        }
        else{
            to->pre->next=to->next;
            to->next->pre=to->pre;
            listnode *temp = from->next;
            from->next = to->next;
            from->pre = to->pre;
            from->next->pre = from;
            from->pre->next = from;
            to->next = temp;
            to->next->pre=temp;
            to->pre = 0;
            head = to;
        }
    }
    //head to tail (sym)
    else if ((from ==head&& to==tail)||(from ==tail && to==head)){
        //2 items
        if (mySize==2) {
            tail->pre=0;
            head->next=0;
            tail->next=head;
            head->pre=tail;
            listnode *temp=head;
            head=tail;
            tail=temp;
        }
        //>2 items
        else{
            tail->pre->next=0;
            head->next->pre=0;
            tail->next=head->next;
            head->pre=tail->pre;
            tail->pre=0;
            head->next=0;
            tail->next->pre=tail;
            head->pre->next=head;
            listnode *temp=head;
            head=tail;
            tail=temp;
        }
    }
    //mid to mid
    else{
        if (from->next==to) { //if next to
            from->next=to->next; to->pre=from->pre;
            from->next->pre=from; to->pre->next=to;
            to->next=from; from->pre=to;
        }
        else if(to->next==from){  //if next to
            to->next=from->next; from->pre=to->pre;
            to->next->pre=to; from->pre->next=from;
            from->next=to; to->pre=from;
        }
        else{ //mid----mid
            from->pre->next=from->next;
            from->next->pre=from->pre;
            to->pre->next=to->next;
            to->next->pre=to->pre;
            listnode *temp1=from->next;
            from->next=to->next;
            to->next=temp1;
            listnode *temp2=from->pre;
            from->pre=to->pre;
            to->pre=temp2;
            from->next->pre=from;
            from->pre->next=from;
            to->next->pre=to;
            to->pre->next=to;
        }
    }
}
void doubleLinkedlist::test_print(){
    listnode *ptr = head;
    while (ptr!=0) {
        cout<<ptr->stock_Name<<endl;
        cout<<ptr->stock_Price<<endl;
        cout<<ptr->num_Share<<endl;
        cout<<ptr->getValue()<<endl;
        ptr=ptr->next;
    }
}

void doubleLinkedlist::updateportfolio(){
    ofstream file;
    file.open("portfolio.txt");
    file << left << setw(20) << "CompanySymbol" << left << setw(10) << "Number" << left << setw(20) << "Price-per-share" << left << setw(10) << "Totalvalue" << "\n";
    listnode *ptr = head;
    while (ptr!= 0) {
        file << left << setw(20) << ptr->stock_Name << left << setw(10) << ptr->num_Share <<  std::left << setw(20) << ptr->stock_Price << left << setw(20) << ptr->getValue() << "\n";
        ptr = ptr->next;
    }
    file.close();
}
