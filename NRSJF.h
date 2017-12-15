/* 
 * File:   NRSJF.h
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:41 AM
 * 
 * Class that represents the non-recurring SJF PCB
 */

#ifndef NRSJF_H
#define NRSJF_H

#include "NonRecurring.h"
using namespace std;

class NRSJF : public NonRecurring {
    public:
        NRSJF(string id, int at,int bt) : NonRecurring(id,at,bt) {
        }
        virtual void print() {
            NonRecurring::print();
            cout<<endl;
        }
    
};

#endif /* NRSJF_H */

