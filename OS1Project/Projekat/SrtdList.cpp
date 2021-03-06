/*
 * SrtdList.cpp
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#include "SrtdList.h"
#include "PCB.h"
#include "SCHEDULE.H"

SrtdList::SrtdList() { // constructor for Sorted List
	first=0;
	numOfMem=0;
}

SrtdList::~SrtdList() { // destructor for Sorted List
	while(first){
		Elem *tmp=first;
		first=first->next;
		delete tmp;
	}
	first=0;
	numOfMem=0;
}

void SrtdList::insert(PCB* pcb, Time time){ // insertion of Elem
	if(first==0){ // case: List is empty
		first=new Elem(pcb,time);
		numOfMem++;
	}else{ // case: List has elements
		if(time < first->time){ // case: we need to insert it before first Elem; diffrence is <0
			Elem* tmp=new Elem(pcb,time); // make new Elem
			tmp->next=first;
			first->time=first->time - time; // = - diff because next elem is that much bigger than Elem that we are inserting
			first=tmp;
			numOfMem++;
		} else{ // case: we need to find position for inserting
			Elem* tmp1=first;
			Elem* tmp2=0;
			while(tmp1!=0 && time >=tmp1->time){ // iterate throught list until we find position for insertion
				tmp2=tmp1;
				tmp1=tmp1->next;
				time=time-tmp2->time; // update time
			}
			if(tmp1==0){ //  tmp1 == 0 and we are inserting at the end
				Elem* tmp=new Elem(pcb,time);
				tmp->next=0; // because it's a last element now
				tmp2->next=tmp; // tmp2 now pointing to last element in list
				numOfMem++;
			}else{ // we are inserting between tmp2 and tmp1
				Elem* tmp=new Elem(pcb,time);
				tmp->next=tmp1; // tmp2-->tmp1 is order in list now and we need to insert element between these two
				tmp1->time=tmp1->time - tmp->time;
				tmp2->next=tmp;
				numOfMem++;
			}
		}
	}
}

PCB* SrtdList::takeFirst(){ // take from head
	if(first!=0){
		if(numOfMem==1){ // case when there is only one element
			Elem* tmp=first;
			first=0;
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

void SrtdList::update(){ // just decrement first Elem and if it's 0 than put it in Scheduler
	if(first!=0){
		first->time--;
		while(first!=0 && first->time == 0){ // put all elements with time==0 in scheduler
			PCB* pcb=takeFirst();
			pcb->state=PCB::READY; // change state to Ready
			Scheduler::put(pcb); // put it in Scheduler
		}
	}
}

