/*
* File:   Scheduler.cpp
* Author: anitageorge and lucia
*
* Compiler Used: Netbeans 8
*
* Created on November 17, 2017, 10:00 PM
*
* class containing the implementation of Scheduler class
*/

#include "Scheduler.h"
#include "list"

#include "RPriority.h"
#include "RSJF.h"
#include "RFCFS.h"
#include "NRSJF.h"
#include "NRFCFS.h"
#include "NRPriority.h"
#include "string"
#include "strstream"
#include "fstream"
#include "ctime"
#include "algorithm"
#include "TimingWheel.h"
using namespace std;

/**
 * Constructor that initializes the PCB queues with their properties
 */
Scheduler::Scheduler() {
    priorityqueue = new PCBQueue;
    sjfqueue = new PCBQueue;
    fcfsqueue = new PCBQueue;
    readyQueue = new PCBQueue;
    resultqueue = new PCBQueue;
    
    priorityqueue->setsortby(3);
    sjfqueue->setsortby(2);
    fcfsqueue->setsortby(1);
    readyQueue->setsortby(1);
    resultqueue->setsortby(0);
    
    PCBqueues = new PCBQueue *[5];
    PCBqueues[0] = priorityqueue;
    PCBqueues[1] = sjfqueue;
    PCBqueues[2] = fcfsqueue;
    PCBqueues[3] = readyQueue;
    PCBqueues[4] = resultqueue;
    upgradecount = 0;
    outfile.open("output.txt", ofstream::app);
}

/**
 * Destructor to deallocate the space allocated for the queues
 */
Scheduler::~Scheduler() {
    for(int i = 0; i < 5; i++) {
        delete PCBqueues[i];
    }
    delete PCBqueues;
}

/**
 * Function to set the priority levels of the PCB
 * @param level
 */
void Scheduler::setPriorityLevels(int level) {
    prioritylevels = level;
}
/**
 * Function to set the probability of the PCB arrival 
 * @param probability
 */
void Scheduler::setPCBProbability(int probability) {
    prob_pcb = probability;
}
/**
 * Function to generate an ID for the PCB based on the the type of the PCB
 * @param jobtype
 * @param pcbtype
 * @param count
 */
void Scheduler::generateID(string jobtype, string pcbtype, int count) {
    id = "#";
    id.append(jobtype);
    id.append(pcbtype);
    id.append(to_string(count));
}
/**
 * Function to populate the data from the input file
 * @param filename
 */
bool Scheduler::populateData(string filename) {
    ifstream in(filename);
    if((filename.find(".") == string::npos)||(in.peek() == fstream::eofbit)) {
        cout<<"Aborting simulation\nReason: Incorrect File Name"<<endl;
        return false;
    }
    string line;
    int val;
    vector<int> v;
    getline(in,line);
    pcb_nos = stoi(line);
    for(int i = 0; i < (pcb_nos/2)+2; i++) {
        getline(in,line);
        string::size_type pos = line.find(" ");
        string::size_type pos2 = line.find(" ", pos+1);
        while(pos != string::npos) {
            int len = pos2 - pos - 1;
            string s = line.substr(pos+1, len);
            if(s.find("R") == string::npos && s.find("B") == string::npos) {
                val = stoi(s);
                v.push_back(val);
            }
            line.replace(0, pos2, "");
            pos = line.find(" ");
            pos2 = line.find(" ", pos+1);
        }
    }
    
    int i = 0;
    sleeptime_min = v.at(i++);
    sleeptime_max = v.at(i++);
    starvationtime_min = v.at(i++);
    starvationtime_max = v.at(i++);
    pcb_priority = v.at(i++);
    rec_pri = v.at(i++);
    nrec_pri = v.at(i++);
    pri_bursttime_min = v.at(i++);
    pri_bursttime_max = v.at(i++);
    sjf = v.at(i++);
    rec_sjf = v.at(i++);
    nrec_sjf = v.at(i++);
    sjf_bursttime_min = v.at(i++);
    sjf_bursttime_max = v.at(i++);
    fcfs = v.at(i++);
    rec_fcfs = v.at(i++);
    nrec_fcfs = v.at(i++);
    fcfs_bursttime_min = v.at(i++);
    fcfs_bursttime_max = v.at(i++);
    findMaxBurstTime();
    return true;
}
/**
 * Function to generate a random number
 * if no limits are specified, the function outputs a random value between 1 and 100
 * @param n
 * @param m
 * @return 
 */
int Scheduler::randomgenerator(int n = 0, int m = 0) {
	int num;
	int min = 1, max = 100;

	if (n == 0 && m == 0) {
		num = rand() % (max - min + 1) + min;
	}
	else if (m == 0) {
		num = rand() % n + 1;
	}
	else {
		num = rand() % (m - n + 1) + n;
	}
	return num;
}
/**
 * Function to generate and populate the queues with a PCB 
 * @param poolcount
 */
void Scheduler::PopulateQueues(int poolcount){
    PCB *pcb = NULL;
    pcbtype = randomgenerator();
    sleeptime = randomgenerator(sleeptime_min, sleeptime_max);
    starvationtime = randomgenerator(starvationtime_min, starvationtime_max);
    
    if (pcbtype <= pcb_priority) {
        //priority pcb block
        rnr = randomgenerator();
        priority = randomgenerator(prioritylevels);
        bursttime = randomgenerator(pri_bursttime_min, pri_bursttime_max);
        if (rnr <= rec_pri) {
            generateID("P","R",rec_pricount++);
            pcb = new RPriority(id, poolcount, bursttime, sleeptime, priority);
        }
        else if (rnr > rec_pri) {
            generateID("P","N",nrec_pricount++);
            pcb = new NRPriority(id, poolcount, bursttime, priority);
        }
        if(pcb != NULL)
            priorityqueue->add(pcb);
    } else if (pcbtype > pcb_priority && pcbtype < fcfs) {
        //sjf pcb block
        rnr = randomgenerator();
        bursttime = randomgenerator(sjf_bursttime_min, sjf_bursttime_max);
        if (rnr > nrec_sjf) {
            generateID("S","R", rec_sjfcount++);
            pcb = new RSJF(id, poolcount, bursttime, sleeptime, starvationtime);
        }
        else if (rnr <= nrec_sjf) {
            generateID("S","N",nrec_sjfcount++);
            pcb = new NRSJF(id, poolcount, bursttime);
        }
        if(pcb != NULL)
            sjfqueue->add(pcb);
    } else if (pcbtype >= fcfs) {
        //fcfs pcb block
        rnr = randomgenerator();
        bursttime = randomgenerator(fcfs_bursttime_min, fcfs_bursttime_max);
        if (rnr <= rec_fcfs) {
            generateID("F","R",rec_fcfscount++);
            pcb = new RFCFS(id, poolcount, bursttime, sleeptime, starvationtime);
        }
        else if (rnr >= nrec_fcfs) {
            generateID("F","N",nrec_fcfscount++);
            pcb = new NRFCFS(id, poolcount, bursttime);
        }
        if(pcb != NULL)
            fcfsqueue->add(pcb);
    }  
}
/**
 * Function to initiate the generation of an Initial Pool of PCBs
 */
void Scheduler::generateInitialPool(int count) {
    initialPCBCount = 0;
    
    while (initialPCBCount < count) {
        PopulateQueues(initialPCBCount++);
    }
    ofstream out("output.txt");
    out.clear();
    cout<<"Initial Pool of PCB's are generated. "<<endl;
    outfile<<"Initial Pool of PCB's are generated. "<<endl;
    printQueueStatus();
}

/**
 * Function to generate the PCB during simulation and schedule the PCB's
 */
void Scheduler::schedule(int time, int cpunum)
{
    clock = initialPCBCount + 1;
    simulationTime = clock + time;
    PCB *currentJob;
    cpu_count = cpunum;
    bool *cpus = new bool[cpu_count + 1];
    
    TimingWheel* TW = TimingWheel::Instance();
    findMaxBurstTime();
    TW->setMaxDelay(maxbursttime);
    
    cpus[0] = false;
    for(int i = 1; i <= cpu_count; i++) {
        cpus[i] = true;
    }
    
    TW->setCpu(cpus);
    
    for(int i = 1; i <= cpu_count; i++) {
        currentJob = getNextJob();
        if(currentJob != NULL) {
            currentJob->setStartTime(clock);
            TW->insert(currentJob->getBurstTime(), i, currentJob);
            cout<<"CPU#"<<i<<" is allocated PCB"<<currentJob->getID()<<" BT:"<<currentJob->getBurstTime()<<endl;
            outfile<<"CPU#"<<i<<" is allocated PCB"<<currentJob->getID()<<" BT:"<<currentJob->getBurstTime()<<endl;
            cpus[i] = false;
        }
    }
    
    while (clock < simulationTime) {
        
        cout<<"Clock: "<<clock<<endl;
        outfile<<"Clock: "<<clock<<endl;
        
        prob = randomgenerator();
        if (prob <= prob_pcb) {
            PopulateQueues(clock);
        }
        
        printQueueStatus();
        
        TW->schedule(clock, PCBqueues);
        
        for(auto p: readyQueue->getqueue()) {
            Recurring *r;
            r = dynamic_cast<Recurring*>(p);
            if(r && (r->getWakeupTime() == 0)) {
                cout<<"\tPCB awake: "<<p->getID()<<endl;
                outfile<<"\tPCB awake: "<<p->getID()<<endl;
                RSJF *rs;
                rs = dynamic_cast<RSJF*> (r);
                RFCFS *rf;
                rf = dynamic_cast<RFCFS*> (r);
                RPriority *rp;
                rp = dynamic_cast<RPriority*> (r);
                if(rp) {
                    priorityqueue->add(p);
                } else if(rs) {
                    sjfqueue->add(p);
                } else if(rf) {
                    fcfsqueue->add(p);
                }
            }
        }
        
        if(readyQueue->getqueue().size() > 0) {
            cout<<"\tReady Queue:"; 
            outfile<<"\tReady Queue:";
            outfile.flush();
            readyQueue->printQueueStatus();
        }
        
        upgradePCB(clock);
        clock++;
    }
    
    cout<<"\nFinished PCB's: "<<endl;
    cout<<"ID#"<<"\t"<<"AT"<<"\t"<<"BT"<<"\t"<<"CT"<<"\t"<<"WT"<<"\t"<<"TT"<<endl;;
    resultqueue->printqueue();
    
    cout<<"\n";
    cout<<"AT = Arrival Time"<<endl;
    cout<<"BT = Burst Time"<<endl;
    cout<<"CT = Completion Time"<<endl;
    cout<<"WT = Waiting Time"<<endl;
    cout<<"TT = Turn around Time"<<endl;
    cout<<"P = Priority"<<endl;
    cout<<"ST = Sleep Time"<<endl;
    
    printFinalStatistics();
}

/**
 * Method to retrieve the next job from the PCB Queue
 * @return 
 */
PCB* Scheduler::getNextJob() {
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
 * Method to upgrade the PCB's if there is starvation in the queues
 * @param clock
 */
void Scheduler::upgradePCB(int clock) {
    list<PCB*> queue = sjfqueue->getqueue();
    PCB *pcb;
    for(auto p: queue) {
        RSJF *q;
        q = dynamic_cast<RSJF*> (p);
        if(q) {
            if(q->upgrade()) {
                generateID("P","R", rec_pricount++);
                sleeptime = randomgenerator(sleeptime_min, sleeptime_max);
                priority = randomgenerator(prioritylevels);
                bursttime = randomgenerator(pri_bursttime_min, pri_bursttime_max);
                pcb = new RPriority(id,clock,bursttime,sleeptime,priority);
                cout<<"\tStarvation detected "<<p->getID()<<" upgraded to "<<pcb->getID()<<endl;
                outfile<<"\tStarvation detected "<<p->getID()<<" upgraded to "<<pcb->getID()<<endl;
                priorityqueue->add(pcb);
                sjfqueue->removePCB(p);
                upgradecount++;
            }
        } 
//        else {
//            if(q->upgrade()) {
//                sjfqueue->removePCB(q);
//            }
//        }
    }
    list<PCB*> queue2 = fcfsqueue->getqueue();
    for(auto p: queue2) {
        RFCFS *r;
        r = dynamic_cast<RFCFS*> (p);
        if(r) {
            if(r->upgrade()) {
                generateID("S","R", rec_sjfcount++);
                sleeptime = randomgenerator(sleeptime_min, sleeptime_max);
                bursttime = randomgenerator(sjf_bursttime_min, sjf_bursttime_max);
                starvationtime = randomgenerator(starvationtime_min, starvationtime_max);
                pcb = new RSJF(id, clock, bursttime, sleeptime, starvationtime);
                cout<<"\tStarvation detected "<<p->getID()<<" upgraded to "<<pcb->getID()<<endl;
                sjfqueue->add(pcb);
                fcfsqueue->removePCB(p);
                upgradecount++;
            }
        } 
//        else {
//            if(r->upgrade()) {
//                fcfsqueue->removePCB(p);
//            }
//        }
    }
}

/**
 * Method to find the maximum burst time among the different types of PCB
 */
void Scheduler::findMaxBurstTime() {
    int max1 = max(fcfs_bursttime_max, pri_bursttime_max);
    maxbursttime = max(max1, sjf_bursttime_max);
}

/**
 * Method to print the status of all the queues in the system
 */
void Scheduler::printQueueStatus() {
    if(!priorityqueue->isQueueEmpty()) {
            cout<<"\tPriority Queue:";
            outfile<<"\tPriority Queue:";
            outfile.flush();
            priorityqueue->printQueueStatus();
        } else {
            cout<<"\tPriority Queue: EMPTY"<<endl;
            outfile<<"\tPriority Queue: EMPTY"<<endl;
        }
        if(!sjfqueue->isQueueEmpty()) {
            cout<<"\tSJF Queue:";
            outfile<<"\tSJF Queue:";
            outfile.flush();
            sjfqueue->printQueueStatus();
        } else {
            cout<<"\tSJF Queue: EMPTY"<<endl;
            outfile<<"\tSJF Queue: EMPTY"<<endl;
        }
        if(!fcfsqueue->isQueueEmpty()) {
            cout<<"\tFCFS Queue:";
            outfile<<"\tFCFS Queue:";
            outfile.flush();
            fcfsqueue->printQueueStatus();
        } else {
            cout<<"\tFCFS Queue: EMPTY"<<endl;
            outfile<<"\tFCFS Queue: EMPTY"<<endl;
        }
}

/**
 * Method to print the final statistics of the PCB's 
 */
void Scheduler::printFinalStatistics() {
    int total = rec_fcfscount + rec_pricount + rec_sjfcount + nrec_fcfscount + nrec_pricount + nrec_sjfcount;
    int r_total = rec_fcfscount + rec_pricount + rec_sjfcount;
    int n_total = nrec_fcfscount + nrec_pricount + nrec_sjfcount;
    
    int processed_total = resultqueue->getSize();
    int total_WT = 0, total_TT = 0, total_CT = 0;
    for(auto p : resultqueue->getqueue()) {
        total_WT += p->getWaitingTime();
        total_TT += p->getTurnaroundTime();
        total_CT += p->getCompletionTime();
    }
    
    avg_CT = total_CT/processed_total;
    avg_TT = total_TT/processed_total;
    avg_WT = total_WT/processed_total;
    
    cout<<"\n Generating Final Statistics"<<endl;
    
    cout<<"# PCBs Generated:"<<total<<endl;
    cout<<"\t# Recurring PCB:"<<r_total<<endl;
    cout<<"\t# Non-Recurring PCB:"<<n_total<<endl;
    
    cout<<"# PCBs Processed:"<<resultqueue->getSize()<<endl;
    cout<<"\tAverage Turnaround Time: "<<avg_TT<<endl;
    cout<<"\tAverage Waiting Time: "<<avg_WT<<endl;
    cout<<"\tAverage Completion Time: "<<avg_CT<<endl;
    
    cout<<"# PCBs Remaining in the queue:"<<endl;
    cout<<"\tPriority Queue: "<<priorityqueue->getSize()<<endl;
    cout<<"\tSJF Queue: "<<sjfqueue->getSize()<<endl;
    cout<<"\tFCFS Queue: "<<fcfsqueue->getSize()<<endl;
    
    cout<<"# PCBs Sleeping:"<<readyQueue->getSize()<<endl;
    cout<<"# PCBs Upgraded after starvation:"<<upgradecount<<endl;
}