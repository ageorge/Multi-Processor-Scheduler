/* 
 * File:   PCBQueue.h
 * Author: anita and lucia
 *
 * Created on November 19, 2017, 5:56 PM
 * 
 * Compiler Used: Netbeans 8
 * 
 * Class for a custom PCB queue
 */

#ifndef PCBQUEUE_H
#define PCBQUEUE_H

#include "string"
#include "list"
#include "PCB.h"
#include "fstream"
using namespace std;

class PCBQueue {
    int sortby;
    list<PCB*> pcblist;
    ofstream outfile;
public:
    void setsortby(int);
    void sort();
    void add(PCB *pcb);
    PCB* deletePCB();
    void removePCB(PCB *pcb);
    void printqueue();
    void printQueueStatus();
    list<PCB*> getqueue();
    bool isQueueEmpty();
    int getSize();
};


#endif /* PCBQUEUE_H */

