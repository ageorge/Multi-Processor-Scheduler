/* 
 * File:   Priority.h
 * Author: anitageorge and lucia
 * 
 * Compiler Used: Netbeans 8
 *
 * Created on November 8, 2017, 10:35 AM
 * 
 * Class that represents the priority job
 */

#ifndef PRIORITY_H
#define PRIORITY_H

class Priority {
    int priority;
public:
    Priority() {
    }
    Priority(int p) {
        priority = p;
    }
    int getPriority() {
        return priority;
    }
};


#endif /* PRIORITY_H */

