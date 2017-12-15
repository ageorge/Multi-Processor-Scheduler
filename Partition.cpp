/* 
 * File:Partition.cpp
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 * 
 * Created on November 10, 2017, 10:34 AM
 * 
 * Implementation file of the Partition class which stores the pcb's processed in a cpu
 */
#include "Partition.h"
#include "iostream"
using namespace std;

/**
 * Parametrized Constructor for the Partition storing the PCB and the allocated cpu
 * @param p
 * @param cpu
 */
Partition::Partition(PCB *p, int cpu) {
    pcb = p;
    cpu_num = cpu;
    next = NULL;
}

/**
 * adding a new partition at the end
 * @param newPartition
 */
void Partition::addPartition(Partition* newPartition) {
    Partition *n = next;
    Partition *last = this;
    while (n != NULL) {
        if(n->next != NULL)
            n = n->next;
        else {
            last = n;
            break;
        }
    }
    last->next = newPartition;
}

/**
 * Printing the contents of the list of Partitions
 */
void Partition::print() {
    cout<<"\tPCB: "<<pcb->getID()<<" BT: "<<pcb->getBurstTime()<<", cpu#: "<<cpu_num;
    
    if(next == NULL) {
        cout<<", next: "<<next<<endl;
    } else {
        cout<<", next: "<<next->pcb->getID()<<endl;
    }
    Partition *n = next;
    while (n != NULL) {
        cout<<"\tPCB: "<<n->pcb->getID()<<", cpu#: "<<n->cpu_num;
        if(n->next != NULL) {
            cout<<", next: "<<n->next->pcb->getID()<<endl;
        } else {
            cout<<", next: "<<n->next<<endl;
        }
        
        n = n->next;
    }

}

/**
 * Method to return the next partition
 * @return 
 */
Partition* Partition::getNext() {
    return next;
}

/**
 * Method to return the cpu#
 * @return 
 */
int Partition::getCPU() {
    return cpu_num;
}

/**
 * Method to return the PCB
 * @return 
 */
PCB* Partition::getPCB() {
    return pcb;
}