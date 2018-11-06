/*
 * EvList.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#include "EvList.h"
#include "KernelEv.h"

EvList::EvList() {
	first=last=0; // initialize all fields
	numOfMem=0;
}

EvList::~EvList() {
	while(first!=0){ // iterating through list and deleting all nodes
			Elem* tmp=first;
			first=first->next;
			delete tmp;
	}
	first=last=0; // leave list in cool state :)
	numOfMem=0;
}


KernelEv* EvList::getByID(ID id){ // getter for KernelEv by ID
	Elem* tmp=first;
	while(tmp!=0 && tmp->event->id!=id) // finding elem which contains given id
		tmp=tmp->next;
	if(tmp!=0)
		return tmp->event;
	return 0;
}

void EvList::addToEnd(KernelEv* event){
	if(first==0){
		first=last=new Elem(event);
	}else{
		last=last->next=new Elem(event);
	}
	numOfMem++; // increase number of elements in list
}

KernelEv* EvList::takeFirst(){ // take from head
	if(first!=0){
		if(first==last){ // case when there is only one element
			Elem* tmp=first;
			first=last=0;
			numOfMem=0;
			KernelEv* event=tmp->event; // save event before deleting tmp
			delete tmp;
			return event;
		}
		Elem* tmp=first; // case when there is more than 1 element
		first=first->next;
		numOfMem--;
		KernelEv* event=tmp->event; // save pcb before deleting tmp
		delete tmp;
		return event;
	}
	return 0; // if list is empty return 0
}

KernelEv* EvList::takeLast(){ // take from end
	Elem* tmp=first;
	if(tmp!=0){
		if(first==last){ // case: one element exist
			Elem* tmp=first;
			first=last=0;
			numOfMem=0;
			KernelEv* event=tmp->event;
			delete tmp;
			return event;
		}else{
			while(tmp->next!=last){ // to get to the element before last
				tmp=tmp->next;
			}
			Elem* tmp1=tmp->next; // tmp1 on last elem
			tmp->next=0; // element before last now pointing to null
			last=tmp; // update pointer to last element
			KernelEv* event=tmp1->event;
			delete tmp1;
			numOfMem--;
			return event;
		}
	}else
		return 0; // empty list
}

KernelEv* EvList::takeByID(ID id){ // take element from list by Event ID ( BUT DELETE IT )
	if(first!=0){
		if(first==last){ // case: only one element
			if(first->event->id == id){ // and i need that element
				Elem* tmp=first;
				first=last=0;
				numOfMem=0;
				KernelEv* event=tmp->event;
				delete tmp;
				return event;
			}else
				return 0; // if there is one element and not with given ID
		}else{
			Elem* tmp=first;
			Elem* tmp1=0;
			while(tmp!=0 && tmp->event->id != id){ // finding element with given ID
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
				KernelEv* event=tmp->event;
				delete tmp;
				return event;
			}else // case : there is no element with such ID
				return 0;
		}
	}else
		return 0;
}
