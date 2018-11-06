/*
 * SemList.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#include "SemList.h"
#include "KernSem.h"

SemList::SemList() {
	first=last=0; // initialize all fields
	numOfMem=0;

}

SemList::~SemList() {
	while(first!=0){ // iterating through list and deleting all nodes
				Elem* tmp=first;
				first=first->next;
				delete tmp;
	}
	first=last=0; // leave list in cool state :)
	numOfMem=0;
}

KernelSem* SemList::getByID(ID id){ // getter for KernelSem by ID
	Elem* tmp=first;
	while(tmp!=0 && tmp->sem->id!=id) // finding elem which contains given id
		tmp=tmp->next;
	if(tmp!=0)
		return tmp->sem;
	return 0;
}

void SemList::addToEnd(KernelSem* sem){
	if(first==0){
		first=last=new Elem(sem);
	}else{
		last=last->next=new Elem(sem);
	}
	numOfMem++; // increase number of elements in list
}

KernelSem* SemList::takeFirst(){ // take from head
	if(first!=0){
		if(first==last){ // case when there is only one element
			Elem* tmp=first;
			first=last=0;
			numOfMem=0;
			KernelSem* sem=tmp->sem; // save sem before deleting tmp
			delete tmp;
			return sem;
		}
		Elem* tmp=first; // case when there is more than 1 element
		first=first->next;
		numOfMem--;
		KernelSem* sem=tmp->sem; // save sem before deleting tmp
		delete tmp;
		return sem;
	}
	return 0; // if list is empty return 0
}

KernelSem* SemList::takeLast(){ // take from end
	Elem* tmp=first;
	if(tmp!=0){
		if(first==last){ // case: one element exist
			Elem* tmp=first;
			first=last=0;
			numOfMem=0;
			KernelSem* sem=tmp->sem;
			delete tmp;
			return sem;
		}else{
			while(tmp->next!=last){ // to get to the element before last
				tmp=tmp->next;
			}
			Elem* tmp1=tmp->next; // tmp1 on last elem
			tmp->next=0; // element before last now pointing to null
			last=tmp; // update pointer to last element
			KernelSem* sem=tmp1->sem;
			delete tmp1;
			numOfMem--;
			return sem;
		}
	}else
		return 0; // empty list
}

KernelSem* SemList::takeByID(ID id){ // take element from list by Sem ID ( BUT DELETE IT )
	if(first!=0){
		if(first==last){ // case: only one element
			if(first->sem->id == id){ // and i need that element
				Elem* tmp=first;
				first=last=0;
				numOfMem=0;
				KernelSem* sem=tmp->sem;
				delete tmp;
				return sem;
			}else
				return 0; // if there is one element and not with given ID
		}else{
			Elem* tmp=first;
			Elem* tmp1=0;
			while(tmp!=0 && tmp->sem->id != id){ // finding element with given ID
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
				KernelSem* sem=tmp->sem;
				delete tmp;
				return sem;
			}else // case : there is no element with such ID
				return 0;
		}
	}else
		return 0;
}

