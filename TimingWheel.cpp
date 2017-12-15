/* 
 * File:   TimingWheel.cpp
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 * 
 * Created on November 8, 2017, 10:34 PM
 * 
 * Timing Wheel implementation for better data structure for cpu scheduling
 */
#include "TimingWheel.h"
#include "iostream"
using namespace std;

/**
 * static instance initialisation of the Timingwheel
 */
TimingWheel* TimingWheel::instance = 0;

/**
 * Singleton Design pattern Implementation for Timing Wheel 
 * @return 
 */
TimingWheel* TimingWheel::Instance() {
    if(instance == 0) {
        instance = new TimingWheel;
    }
    return instance;
}

/**
 * setting the cpu status 
 * @param cpus
 */
void TimingWheel::setCpu(bool *cpus) {
    cpu = cpus;
}

/**
 * Inserting the new partitions into the timing wheel
 * @param burstTime
 * @param cpu_num
 * @param pcb
 */
void TimingWheel::insert(int burstTime, int cpu_num, PCB* pcb) {
    int slot_num = (current_slot + burstTime) % (max_delay + 1);
 
    Partition *newPartition = new Partition(pcb, cpu_num);
    
    if(cpu[cpu_num]) {
        if(slot[slot_num] == NULL) {
            slot[slot_num] = newPartition;
        } else {
            slot[slot_num]->addPartition(newPartition);
        }
        cpu[cpu_num] = false;
    } else {
        cout<<"\tCPU conflicts: #"<<cpu_num<<endl;
    }
}

/**
 * Setting the maximum delay value for determining the size of the Timing wheel
 * @param delay
 */
void TimingWheel::setMaxDelay(int delay) {
    max_delay = delay;
    slot = new Partition*[max_delay + 1];
    for(int i = 0; i <= max_delay; i++) {
        slot[i] = NULL;
    }
}

/**
 * constructor to initialize the value 
 */
TimingWheel::TimingWheel() {
    current_slot = 0;
    outfile.open("output.txt", ofstream::app);
    slot = NULL;
}

/**
 * Function to allocate new jobs to the cpu when they become free
 * @param clock
 * @param PCBqueues
 */
void TimingWheel::schedule(int clock, PCBQueue** PCBqueues) {
    Partition *currentPart = slot[current_slot];
    PCBQueue *readyQueue = PCBqueues[3];
    PCBQueue *resultQueue = PCBqueues[4];
    
    if(currentPart == NULL) {
        cout<<"\tAll CPU's are busy with their jobs"<<endl;
        outfile<<"\tAll CPU's are busy with their jobs"<<endl;
    } else {
        cout<<"\tOne or more CPU's are free"<<endl;
        outfile<<"\tOne or more CPU's are free"<<endl;
    }
    
    while(currentPart != NULL) {
        PCB *pcb = currentPart->getPCB();
        pcb->setCompletionTime(clock);
        pcb->compute();
        resultQueue->add(pcb);
        
        pcb->setStartTime(clock);
        if(pcb->getID().find("R") != string::npos) {
            pcb->setArrivalTime(clock);
            readyQueue->add(pcb);
        }
        cout<<"\tPCB"<<pcb->getID()<<" completed"<<endl;
        outfile<<"\tPCB"<<pcb->getID()<<" completed"<<endl;
        cpu[currentPart->getCPU()] = true;
        cout<<"\tCPU#"<<currentPart->getCPU()<<" is free "<<endl;
        outfile<<"\tCPU#"<<currentPart->getCPU()<<" is free "<<endl;
        PCB *nextPCB = getNextJob(PCBqueues);
        if(nextPCB != NULL) {
            cout<<"\tCPU#"<<currentPart->getCPU()<<" is allocated PCB "<<nextPCB->getID()<<" BT:"<<nextPCB->getBurstTime()<<endl;
            outfile<<"\tCPU#"<<currentPart->getCPU()<<" is allocated PCB "<<nextPCB->getID()<<" BT:"<<nextPCB->getBurstTime()<<endl;
            nextPCB->setStartTime(clock);
            insert(nextPCB->getBurstTime(), currentPart->getCPU(), nextPCB);
        }
        currentPart = currentPart->getNext();
    }
    clear_current_slot();
    current_slot = (current_slot+1) % (max_delay + 1);
}

/**
 * Function to retrieve the next job from the PCBQueue
 * @param PCBqueues
 * @return 
 */
PCB* TimingWheel::getNextJob(PCBQueue** PCBqueues) {
    PCBQueue *priorityqueue = PCBqueues[0];
    PCBQueue *sjfqueue = PCBqueues[1];
    PCBQueue *fcfsqueue = PCBqueues[2];
    
    if(!priorityqueue->isQueueEmpty()) {
        return priorityqueue->deletePCB();
    } else if(!sjfqueue->isQueueEmpty()) {
        return sjfqueue->deletePCB();
    } else if(!fcfsqueue->isQueueEmpty()) {
        return fcfsqueue->deletePCB();
    } 
    
    return NULL;
}

/**
 * Function to clear the current slot in the timing wheel
 */
void TimingWheel::clear_current_slot() {
    if(slot[current_slot] != NULL) {
        if(slot[current_slot]->getNext() == NULL) {
            delete slot[current_slot];
        } else {
            Partition *current = slot[current_slot];
            while(current != NULL) {
                Partition *next = current->getNext();
                delete current;
                current = next;
            }
        }
        cout<<"\tDeleting slot#"<<current_slot<<endl;
        outfile<<"\tDeleting slot#"<<current_slot<<endl;
        slot[current_slot] = NULL;
    }
}