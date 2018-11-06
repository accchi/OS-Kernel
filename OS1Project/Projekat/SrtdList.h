/*
 * SrtdList.h
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#ifndef SRTDLIST_H_
#define SRTDLIST_H_
#include "Thread.h"

class SrtdList {
public:
	SrtdList();
	virtual ~SrtdList();
	struct Elem{
		Elem* next;
		PCB* pcb;
		Time time;
		Elem(PCB* p,Time t){ // constructor for node
			pcb=p;
			time=t;
			next=0;
		}
	};
	void insert(PCB*,Time); // inserting element with given Time
	void update(); // decrementing time slice of first element and if 0 put it in scheduler
	PCB* takeFirst(); // taking first elem
	void write(); // printing list
private:
	Elem* first; // pointer to last not needed
	int numOfMem;
};

#endif /* SRTDLIST_H_ */
