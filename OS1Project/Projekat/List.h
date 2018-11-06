/*
 * List.h
 *
 *  Created on: May 10, 2018
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_
#include "PCB.h"

class List {
public:
	List(); // List constructor
	virtual ~List(); // List destructor
	struct Elem{ // node struct
		Elem* next;
		PCB* pcb;
		Elem(PCB* p){ // constructor for node
			pcb=p;
			next=0;
		}
	};
	int numOfMem; // number of members in the list
	void addToEnd(PCB*); // inserting element to the end
	void addToHead(PCB*); // inserting element to the beginning
	PCB* takeFirst(); // taking first element
	PCB* takeLast(); // taking last element
	PCB* takeByID(int); // take element by ID of PCB
	int getNumOfMem();
	PCB* getByID(int); // getter for PCB by ID ( doesnt delete elem, just get it )
private:
	Elem* first,*last; // head and tail
};

#endif /* LIST_H_ */
