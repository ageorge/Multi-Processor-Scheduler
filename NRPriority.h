/* 
 * File:   NRPriority.h
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:40 AM
 * 
 * Class that represents the non-recurring priority PCB
 */

#ifndef NRPRIORITY_H
#define NRPRIORITY_H

#include "Priority.h"
#include "NonRecurring.h"
using namespace std;

class NRPriority : public NonRecurring, public Priority {
    public:
        NRPriority(string id, int at,int bt, int p) : NonRecurring(id,at,bt) , Priority(p){
        }
        virtual void print() {
            NonRecurring::print();
            cout<<"P="<<getPriority()<<endl;
        }
    
};

#endif /* NRPRIORITY_H */

