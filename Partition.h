/* 
 * File:   Partition.h
 * Author: anita and lucia
 *
 * Created on November 19, 2017, 7:56 PM
 * 
 * Compiler Used: Netbeans 8
 * 
 * Class for a Partition to add into the timing wheel
 */

#ifndef PARTITION_H
#define PARTITION_H

#include "PCB.h"

class Partition {
    PCB *pcb;
    int cpu_num;
    Partition *next;
public:
    Partition(PCB *p, int cpu);
    void addPartition(Partition *newPartition);
    Partition* getNext();
    int getCPU();
    PCB* getPCB();
    void print();
};

#endif /* PARTITION_H */

