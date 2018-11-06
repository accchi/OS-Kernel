/*
 * KernSem.h
 *
 *  Created on: May 19, 2018
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_
typedef int ID;
class List;
class SemList;
class Semaphore;

class KernelSem {
public:
	friend class SemList;
	friend class Semaphore;
	KernelSem(int,Semaphore*);
	virtual ~KernelSem();
	void signal();
	int wait(int);
	int getVal()const; // Returns the current value of the semaphore
private:
	static int generator;
	ID id;
	int val; // value for checking to block or not to block
	List* blocked; // blocked threads on this semaphore
};


#endif /* KERNSEM_H_ */
