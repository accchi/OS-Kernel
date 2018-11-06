/*
 * List.cpp
 *
 *  Created on: May 10, 2018
 *      Author: OS1
 */

#include "List.h"

List::List() { // constructor for list
	first=last=0; // initialize all fields
	numOfMem=0;
}

List::~List() { // destrutor for list
	while(first!=0){ // iterating through list and deleting all nodes
		Elem* tmp=first;
		first=first->next;
		delete tmp;
	}
	first=last=0; // leave list in cool state :)
	numOfMem=0;
}

void List::addToEnd(PCB* pcb){
	if(first==0){
		first=last=new Elem(pcb);
	}else{
		last=last->next=new Elem(pcb);
	}
	numOfMem++; // increase number of elements in list
}

void List::addToHead(PCB* pcb){ // add to head
	if(first==0){
		first=last=new Elem(pcb);
	}else{
		Elem* tmp=new Elem(pcb);
		tmp->next=first;
		first=tmp;
		tmp=0; // leave cool
	}
	numOfMem++;
}

PCB* List::takeFirst(){ // take from head
	if(first!=0){
		if(first==last){ // case when there is only one element
			Elem* tmp=first;
			first=last=0;
			numOfMem=0;
			PCB* pcb=tmp->pcb; // save pcb before deleting tmp
			delete tmp;
			return pcb;
		}
		Elem* tmp=first; // case when there is more than 1 element
		first=first->next;
		numOfMem--;
		PCB* pcb=tmp->pcb; // save pcb before deleting tmp
		delete tmp;
		return pcb;
	}
	return 0; // if list is empty return 0
}

PCB* List::takeLast(){ // take from end
	Elem* tmp=first;
	if(tmp!=0){
		if(first==last){ // case: one element exist
			Elem* tmp=first;
			first=last=0;
			numOfMem=0;
			PCB* pcb=tmp->pcb;
			delete tmp;
			return pcb;
		}else{
			while(tmp->next!=last){ // to get to the element before last
				tmp=tmp->next;
			}
			Elem* tmp1=tmp->next; // tmp1 on last elem
			tmp->next=0; // element before last now pointing to null
			last=tmp; // update pointer to last element
			PCB* pcb=tmp1->pcb;
			delete tmp1;
			numOfMem--;
			return pcb;
		}
	}else
		return 0; // empty list
}

PCB* List::takeByID(ID id){ // take element from list by PCB ID ( BUT DELETE IT )
	if(first!=0){
		if(first==last){ // case: only one element
			if(first->pcb->id == id){ // and i need that element
				Elem* tmp=first;
				first=last=0;
				numOfMem=0;
				PCB* pcb=tmp->pcb;
				delete tmp;
				return pcb;
			}else
				return 0; // if there is one element and not with given ID
		}else{
			Elem* tmp=first;
			Elem* tmp1=0;
			while(tmp!=0 && tmp->pcb->id != id){ // finding element with given ID
				tmp1=tmp;
				tmp=tmp->next;
			}
			if(tmp!=0){ // Element found
				if(tmp==first) // Element is first
					return takeFirst();
				if(tmp==last) // Element is last
					return takeLast();
				tmp1->next=tmp->next; // case: It's not first or last
				numOfMem--;
				PCB* pcb=tmp->pcb;
				delete tmp;
				return pcb;
			}else // case : there is no element with such ID
				return 0;
		}
	}else
		return 0;
}

int List::getNumOfMem(){ // getter for numOfMem
	return numOfMem;
}

PCB* List::getByID(ID id){ // getter for PCB by ID
	Elem* tmp=first;
	while(tmp!=0 && tmp->pcb->id!=id) // finding elem which contains given id
		tmp=tmp->next;
	if(tmp!=0)
		return tmp->pcb;
	return 0;
}











