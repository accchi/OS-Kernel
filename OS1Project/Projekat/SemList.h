/*
 * SemList.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_

class KernelSem;

class SemList {
public:
	SemList();
	virtual ~SemList();
	struct Elem{ // node struct
		Elem* next;
		KernelSem* sem;
		Elem(KernelSem* p){ // constructor for node
			sem=p;
			next=0;
		}
	};
	void addToEnd(KernelSem*); // inserting element to the end
	KernelSem* takeFirst(); // taking first element
	KernelSem* takeLast(); // taking last element
	KernelSem* takeByID(int); // take element by ID of Sem
	KernelSem* getByID(int); // getter for Sem by ID ( doesnt delete elem, just get it )
	int numOfMem; // number of members in the list
private:
	Elem* first,*last; // head and tail
};

#endif /* SEMLIST_H_ */
