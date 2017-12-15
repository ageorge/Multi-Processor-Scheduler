/* 
 * File:   Recurring.h
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:35 AM
 * 
 * Class that represents the recurring PCB
 */

#ifndef RECURRING_H
#define RECURRING_H

#include "string"
#include "PCB.h"
using namespace std;

class Recurring : public PCB{
    int sleepTime;
    int wakeUpTime;
    public:
        Recurring(string id, int at, int bt, int st) : PCB (id, at, bt) {
            sleepTime  = st;
            wakeUpTime = st;
        }
        int getWakeupTime() {
            wakeUpTime--;
            return wakeUpTime;
        }
        virtual void print() {
            PCB::print();
            cout<<"ST="<<sleepTime<<"\t";
        }
};

#endif /* RECURRING_H */

