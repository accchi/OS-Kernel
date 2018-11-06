/*
 * EvList.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef TESTOVI_EVLIST_H_
#define TESTOVI_EVLIST_H_

class KernelEv;

class EvList {
public:
	struct Elem{ // node struct
		Elem* next;
		KernelEv* event;
		Elem(KernelEv* p){ // constructor for node
			event=p;
			next=0;
		}
	};
	EvList();
	virtual ~EvList();
	void addToEnd(KernelEv*); // inserting element to the end
	KernelEv* takeFirst(); // taking first element
	KernelEv* takeLast(); // taking last element
	KernelEv* takeByID(int); // take element by ID of Event
	KernelEv* getByID(int); // getter for Event by ID ( doesnt delete elem, just get it )
	int numOfMem; // number of members in the list
private:
	Elem* first,*last; // head and tail
};

#endif /* TESTOVI_EVLIST_H_ */
