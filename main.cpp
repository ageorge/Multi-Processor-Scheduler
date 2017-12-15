/* 
 * File:   main.cpp
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 * 
 * Created on November 8, 2017, 10:34 AM
 * 
 * Driver Program to run the application
 */

#include "string"
#include "Scheduler.h"
#include "thread"
using namespace std;

int probability, priority_level, simulationTime, initialcount, cpu_count, choice;
string filename;

/**
 * Function to get Inputs from the user
 */
void get_user_input() {
    
    cout << "Enter the probability of pcb generated" << endl;
    cin >> probability;
    cout << "Enter the priority levels" << endl;
    cin >> priority_level;
    cout << "Enter the file name with file extension" << endl;
    cin >> filename;
    cout << "Enter the simulation time" << endl;
    cin >> simulationTime;
    cout << "Enter the initial PCB count" << endl;
    cin >> initialcount;
    cout << "Do you want the simulator to detect the cpu in your system (1 = YES)" << endl;
    cin >> choice;
    if(choice == 1) {
        cpu_count = thread::hardware_concurrency();
        cout<<"The simulator has detected "<<cpu_count<<" cpu's in your machine"<<endl;
    } else {
        cout<<"Enter the number of cpu's"<<endl;
        cin>>cpu_count;
    } 
}

/**
 * Main Program
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv) {
    Scheduler scheduler;
    
    get_user_input();
    
    scheduler.setPCBProbability(probability);
    scheduler.setPriorityLevels(priority_level);
    
    if(scheduler.populateData(filename)) {
        scheduler.generateInitialPool(initialcount);
        scheduler.schedule(simulationTime, cpu_count);
    }
}

