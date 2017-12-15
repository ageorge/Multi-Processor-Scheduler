/* 
 * File:   RSJF.h
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:40 AM
 * 
 * Class that represents the recurring SJF PCB
 */

#ifndef RSJF_H
#define RSJF_H

#include "Recurring.h"
using namespace std;

class RSJF : public Recurring {
    int starvation_time;
    public:
        RSJF(string id, int at,int bt, int st, int starv) : Recurring(id,at,bt, st) {
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

#endif /* RSJF_H */

