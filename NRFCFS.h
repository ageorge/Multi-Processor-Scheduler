/* 
 * File:   NRFCFS.h
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:41 AM
 * 
 * Class that represents the non-recurring FCFS PCB
 */

#ifndef NRFCFS_H
#define NRFCFS_H

#include "NonRecurring.h"
using namespace std;

class NRFCFS : public NonRecurring {
    public:
        NRFCFS(string id, int at,int bt) : NonRecurring(id,at,bt) {
        }
        virtual void print() {
            NonRecurring::print();
            cout<<endl;
        }
    
};

#endif /* NRFCFS_H */

