/* 
 * File:   RPriority.h
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:40 AM
 * 
 * Class that represents the recurring Priority PCB
 */

#ifndef RPRIORITY_H
#define RPRIORITY_H

#include "Recurring.h"
#include "Priority.h"
using namespace std;

class RPriority : public Recurring, public Priority {
    public:
        RPriority(string id, int at,int bt,int st, int p) : Recurring(id,at,bt,st) , Priority(p){
        }
        virtual void print() {
            Recurring::print();
            cout<<"P="<<getPriority()<<endl;
        }
    
};

#endif /* RPRIORITY_H */

