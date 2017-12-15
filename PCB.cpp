/* 
 * File:   PCB.cpp
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:35 AM
 * 
 * Implementation file for PCB
 */

#include "PCB.h"

/**
 * Default constructor
 */
PCB::PCB() {
    ID = "0";
    arrivalTime = 0;
    burstTime = 0;
    sameAT = false;
}

/**
 * Parametrized constructor for PCB
 * @param id
 * @param arrival
 * @param burst
 */
PCB::PCB(string id, int arrival, int burst, bool same) {
    ID = id;
    arrivalTime = arrival;
    burstTime = burst;
    sameAT = same;
}
/**
 * Method to compute the turnaround time and waiting time for the PCB
 */
void PCB::compute() {
    turnAround = completionTime - arrivalTime + 1;
    waitingTime = turnAround - burstTime;
}

/**
 * Method that returns the Bursttime of the PCB
 * @return 
 */
int PCB::getBurstTime() {
    return burstTime;
}
/**
 * Method to set the arrival time of a PCB
 * @param time
 */
void PCB::setArrivalTime(int time) {
    arrivalTime = time;
}

/**
 * Method that returns the ArrivalTime of the PCB
 * @return 
 */
int PCB::getArrivalTime() {
    return arrivalTime;
}
/**
 * Method to set the ID of the PCB
 * @param id
 */
void PCB::setID(string id) {
    ID = id;
}

/**
 * Method that returns the ID of the PCB
 * @return 
 */
string PCB::getID() {
    return ID;
}

/**
 * Method that returns if the PCB has the same arrival time with another PCB
 * @return 
 */
bool PCB::getsameAt() {
    return sameAT;
}

/**
 * Method to set the sameAT flag
 * @param flag
 */
void PCB::setsameAT(bool flag) {
    sameAT = flag;
}
/**
 * Method to set the starttime
 * @param time
 */
void PCB::setStartTime(int time) {
    startTime = time;
}
/**
 * Method to return the starttime
 * @return 
 */
int PCB::getStartTime() {
    return startTime;
}
/**
 * Method that sets the completion time of the PCB
 * @param time
 */
void PCB::setCompletionTime(int time) {
    completionTime = time;
}
/**
 * Method to return the completion time
 * @return 
 */
int PCB::getCompletionTime() {
    return completionTime;
}
/**
 * Method to return the turnaround time
 * @return 
 */
int PCB::getTurnaroundTime() {
    return turnAround;
}
/**
 * Method to return the waiting time
 * @return 
 */
int PCB::getWaitingTime() {
    return waitingTime;
}
/**
 * Method that prints the Properties of the PCB
 */
void PCB::print() {
    cout<<ID<<"\t"<<arrivalTime<<"\t"<<burstTime<<"\t"<<completionTime<<"\t"<<waitingTime<<"\t"<<turnAround<<"\t";
}
/**
 * Overloaded < operator to compare two PCB objects
 * @param pcb1
 * @param pcb2
 * @return 
 */
bool operator<(const PCB &pcb1, const PCB &pcb2) {
    if(pcb1.burstTime < pcb2.burstTime)
        return true;
    else if(pcb1.burstTime == pcb2.burstTime) {
        if(pcb1.arrivalTime < pcb2.arrivalTime)
            return true;
        else
            return false;
    } else 
        return false;
}