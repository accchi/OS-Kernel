/*
 * KernSem.cpp
 *
 *  Created on: May 19, 2018
 *      Author: OS1
 */

#include "KernSem.h"
#include "List.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "Global.h"
#include "SemList.h"
#include "Semaphor.h"

int KernelSem::generator=0;

KernelSem::KernelSem(int value,Semaphore* sem) {
	if(value>=0)
		val=value;
	else
		val=0; // val cant be negative!
	blocked= new List();
	id=++generator;
	sem->myImpl=id;
	Global::SEMlist->addToEnd(this);
}

void KernelSem::signal(){
	if(val++<0){
		PCB* pcb=blocked->takeFirst(); // take first from blocked
		pcb->state=PCB::READY;
		Scheduler::put(pcb);
	}
}

int KernelSem::getVal()const{
	return val;
}

int KernelSem::wait(int toBlock){ // Kolokvijum 2014. April :)
	int ret=0;
	if(!toBlock && val<=0)
		ret=-1;
	else
		if(--val<0){
			ret=1;
			//block
			PCB::running->state=PCB::BLOCKED;
			blocked->addToEnd((PCB*)PCB::running);
			Global::requested_dispatch=1;
		}
	return ret;
}

KernelSem::~KernelSem() {
	while(val<0) // first unblock all blocked on this semaphore
		signal();
	delete blocked; // delete blocked list
	blocked=0;
	Global::SEMlist->takeByID(id); // delete from global list
}

