/* 
 * File:   PCBQueue.cpp
 * Author: anita and lucia
 *
 * Created on November 19, 2017, 6:00 PM
 * 
 * Compiler Used: Netbeans 8
 * 
 * Implementation for the custom PCB queue
 */

#include "PCBQueue.h"
#include "Priority.h"
#include "PCB.h"
#include "Recurring.h"
/**
 * Function to sort two PCB based on their arrival time
 * Two PCB's with the same arrival time is sorted based on their Burst time
 * @param p1
 * @param p2
 * @return 
 */
bool sortbyAT(PCB* p1, PCB* p2) {
    if(p1->getArrivalTime() < p2->getArrivalTime())
        return true;
    else if(p1->getArrivalTime() == p2->getArrivalTime()) {
        p1->setsameAT(true);
        p2->setsameAT(true);
        if(p1->getBurstTime() < p2->getBurstTime()){
            return true;
        } else if(p1->getBurstTime() == p2->getBurstTime()) {
            return true;
        } else
            return false;
    } else 
        return false;  
}
/**
 * Function to sort two PCB based on their burst time
 * Two PCB's with the same burst time is sorted based on their arrival time
 * @param pcb1
 * @param pcb2
 * @return 
 */
bool sortbyBT(PCB* pcb1, PCB* pcb2) {
    if(pcb1->getBurstTime() < pcb2->getBurstTime())
        return true;
    else if(pcb1->getBurstTime() == pcb2->getBurstTime()) {
        if(pcb1->getArrivalTime() < pcb2->getArrivalTime())
            return true;
        else
            return false;
    } else 
        return false; 
}
/**
 * Function to sort two PCB based on their priority time
 * @param p1
 * @param p2
 * @return 
 */
bool sortbyP(PCB* p1, PCB* p2) {
    Priority *p;
    Priority *q;
    
    p = dynamic_cast<Priority*> (p1);
    q = dynamic_cast<Priority*> (p2);
    
    if(p && q) {
        if(p->getPriority() < q->getPriority()) {
            return true;
        }
        else {
            return false;
        }
    }
}
/**
 * Function to set the sorting property
 * @param s
 */
void PCBQueue::setsortby(int s) {
    sortby = s;
    outfile.open("output.txt", ofstream::app);
}

/**
 * function to sort the PCB's according to their sorting property
 */
void PCBQueue::sort() {
    switch(sortby) {
        case 1:
            pcblist.sort(sortbyAT);
            break;
        case 2:
            pcblist.sort(sortbyBT);
            break;
        case 3:
            pcblist.sort(sortbyP);
            break;
        default:
            break;
    }
}
/**
 * Function to add a PCB pointer to the list
 * @param pcb
 */
void PCBQueue::add(PCB *pcb) {
    pcblist.insert(pcblist.begin(),pcb);
    sort();
}
/**
 * Function to delete a PCB pointer to the list
 * 
 */
PCB* PCBQueue::deletePCB() {
    PCB *pcb = pcblist.front();
    pcblist.pop_front();
    return pcb;
}

/**
 * Function to print the contents of the queue
 */
void PCBQueue::printqueue() {
    for(auto p: pcblist) {
        p->print();
    }
}
/**
 * Function that returns the list 
 * @return 
 */
list<PCB*> PCBQueue::getqueue() {
    return pcblist;
}
/**
 * Checks if the queue is empty
 * @return 
 */
bool PCBQueue::isQueueEmpty() {
    return pcblist.empty();
}
/**
 * Removes a pcb from a list
 * @param pcb
 */
void PCBQueue::removePCB(PCB* pcb) {
    pcblist.remove(pcb);
}
/**
 * Prints the status of the queue
 */
void PCBQueue::printQueueStatus() {
    for(auto p: pcblist) {
        cout<<p->getID()<<" ";
        outfile<<p->getID()<<" ";
    }
    cout<<endl;
    outfile<<endl;
}
/**
 * Method to return the size of the queue
 * @return 
 */
int PCBQueue::getSize() {
    return pcblist.size();
}