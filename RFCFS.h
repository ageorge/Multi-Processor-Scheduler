/* 
 * File:   RFCFS.h
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:40 AM
 * 
 * Class that represents the recurring FCFS PCB
 */

#ifndef RFCFS_H
#define RFCFS_H

#include "Recurring.h"
using namespace std;

class RFCFS : public Recurring{
    int starvation_time;
    public:
        RFCFS(string id, int at,int bt, int st, int starv) : Recurring(id,at,bt, st) {
            starvation_time = starv;
        }
        virtual void print() {
            Recurring::print();
            cout<<endl;
        }
        bool upgrade() {
            int diff = getStartTime() - getArrivalTime();
            if(diff > starvation_time)
                return true;
            else
                return false;
        }
};

#endif /* RFCFS_H */

