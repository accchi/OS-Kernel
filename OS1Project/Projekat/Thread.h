/*
 * Thread.h
 *
 *  Created on: May 10, 2018
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;

class PCB; // Kernel's implementation of a user's thread
class Idle;

class Thread {
public:
	ID getId(); // for TESTS DELETE LATER
	friend class Idle; // need to access to myPCB from Idle
	void start();
	void waitToComplete();
	virtual ~Thread();
	static void sleep(Time timeToSleep);
protected:
	friend class PCB; // obrisi nakon testa
	Thread (StackSize stackSize = defaultStackSize, Time timeSlice=defaultTimeSlice);
	virtual void run() {}
private:
	static void wrapper(Thread*);
	ID myPCB; // changed task 2
};

void dispatch ();

#endif /* THREAD_H_ */
