/*
* File:   Scheduler.h
* Author: anitageorge and lucia
*
* Compiler Used: Netbeans 8
*
* Created on November 17, 2017, 10:00 PM
*
* class containing properties of the Scheduler
*/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include<iostream>
#include<string>
#include "fstream"
#include "PCB.h"
#include "vector"
#include "PCBQueue.h"
using namespace std;

class Scheduler {
        PCBQueue *readyQueue;
        PCBQueue *priorityqueue;
        PCBQueue *sjfqueue;
        PCBQueue *fcfsqueue;
        PCBQueue *resultqueue;
        PCBQueue **PCBqueues;
        
        int clock = 0;
        int prob_pcb;
	int prob, pcbtype, rnr, pcb_nos;
	int sjf;
	int pcb_priority, prioritylevels, priority;
	int fcfs;
	int rec_sjf, nrec_sjf, sjf_bursttime_min, sjf_bursttime_max, rec_sjfcount = 0, nrec_sjfcount = 0;
	int rec_pri, nrec_pri, pri_bursttime_min, pri_bursttime_max, rec_pricount = 0, nrec_pricount = 0;
	int rec_fcfs, nrec_fcfs, fcfs_bursttime_min, fcfs_bursttime_max, rec_fcfscount = 0, nrec_fcfscount = 0;
	int bursttime, maxbursttime;
        int avg_WT, avg_TT, avg_CT;
	int sleeptime_min, sleeptime_max;
        int sleeptime;
	int starvationtime_min, starvationtime_max;
        int starvationtime;
        int initialPCBCount;
        int upgradecount;
	string id;
        int cpu_count;
        int simulationTime;
        ofstream outfile;
        int randomgenerator(int, int);
        void PopulateQueues(int poolcount);
        void generateID(string jobtype,string pcbtype,int count);
        void upgradePCB(int);
        PCB* getNextJob();
        void findMaxBurstTime();
public:
	Scheduler();
        ~Scheduler();
        int getcount(int type);
        bool populateData(string);
	void schedule(int,int);
        void setPriorityLevels(int);
        void setPCBProbability(int);
        void generateInitialPool(int);
        void printQueueStatus();
        void printFinalStatistics();
};

#endif /* SCHEDULER_H */

