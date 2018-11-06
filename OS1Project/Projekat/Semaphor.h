/*
 * Semaphor.h
 *
 *  Created on: May 19, 2018
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_
typedef int ID; // CHECK THIS MAYBE CANNONT BE IN MORE THAN 1

class KernelSem;

class Semaphore {
public:
	friend class KernelSem;
	Semaphore(int init=1);
	virtual ~Semaphore();
	virtual int wait(int);
	virtual void signal();
	int val ()const; // Returns the current value of the semaphore
private:
	ID myImpl;

};

#endif /* SEMAPHOR_H_ */
