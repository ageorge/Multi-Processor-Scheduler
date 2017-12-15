/* 
 * File:   NonRecurring.h
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:35 AM
 * 
 * Class that represents the non-recurring PCB
 */

#ifndef NONRECURRING_H
#define NONRECURRING_H

#include "string"
#include "PCB.h"
using namespace std;

class NonRecurring : public PCB{
    public:
        NonRecurring(string id, int at, int bt) : PCB (id, at, bt) {
        }
};

#endif /* NONRECURRING_H */

