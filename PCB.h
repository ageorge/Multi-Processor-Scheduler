/* 
 * File:   PCB.h
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:35 AM
 * 
 * class containing the properties of the Process Control Block
 */

#ifndef PCB_H
#define PCB_H

#include<iostream>
#include<string>
using namespace std;

class PCB {
    string ID;
    int arrivalTime;
    int startTime;
    int completionTime;
    int burstTime;
    int turnAround;
    int waitingTime;
    bool sameAT;
  public:
      PCB();
      PCB(string, int, int, bool same = false);
      void compute();
      int getBurstTime();
      bool getsameAt();
      void setsameAT(bool);
      int getArrivalTime();
      void setArrivalTime(int);
      string getID();
      void setID(string);
      void setCompletionTime(int);
      int getCompletionTime();
      int getTurnaroundTime();
      int getWaitingTime();
      void setStartTime(int);
      int getStartTime();
      virtual void print();
      friend bool operator<(const PCB &pcb1, const PCB &pcb2);
};


#endif /* PCB_H */

