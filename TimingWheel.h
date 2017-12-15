/* 
 * File:   TimingWheel.h
 * Author: anita and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on December 9, 2017, 3:52 PM
 * 
 * Class containing the timing wheel for better cpu scheduling data structure
 */

#ifndef TIMINGWHEEL_H
#define TIMINGWHEEL_H

#include "Partition.h"
#include "PCBQueue.h"
#include "fstream"
using namespace std;


class TimingWheel {
    int max_delay;
    Partition **slot;
    int current_slot, cpunum;
    static TimingWheel *instance;
    TimingWheel();
    ofstream outfile;
    bool *cpu;
public:
    static TimingWheel* Instance();
    void setCpu(bool *cpus);
    void insert(int burstTime, int cpu_num, PCB *pcb);
    void setMaxDelay(int delay);
    void schedule(int clock, PCBQueue** PCBqueues);
    PCB* getNextJob(PCBQueue** PCBqueues);
    void clear_current_slot();
    
};

#endif /* TIMINGWHEEL_H */

