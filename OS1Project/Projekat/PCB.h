/*
 * PCB.h
 *
 *  Created on: May 10, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "Thread.h"
class List;
class SrtdList;

class PCB {
public:
	friend class Thread; // because of wrapper in Thread
	PCB(StackSize, Time, Thread*);
	PCB(); // constructor for main PCB
	virtual ~PCB();
	enum State{ CREATED, READY, BLOCKED, FINISHED };
	State state; // PCB( Thread ) state
	unsigned ss; // stack segment
	unsigned sp; // stack pointer
	unsigned bp; // base pointer
	Time timeSlice; // given time slice
	unsigned *stack; // array that represents stack
	ID id; // id of PCB
	static volatile PCB* running;
	void waitToComplete();
	void start();
	static void sleep(Time);
	static SrtdList* sleeping; // list for sleeping threads
private:
	List* waiting;
	static int generator;
	Thread *myThread; // pointer for thread for certain PCB
};

#endif /* PCB_H_ */
