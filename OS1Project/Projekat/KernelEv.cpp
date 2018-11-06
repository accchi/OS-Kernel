/*
 * KernelEv.cpp
 *
 *  Created on: May 20, 2018
 *      Author: OS1
 */

#include "KernelEv.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "IVTEntry.h"
#include "Global.h"
#include "EvList.h"

int KernelEv::generator=0;

KernelEv::KernelEv(IVTNo ivtNo,Event* event) {
	val=0;
	id=++generator;
	event->myImpl=id;
	myPCB=(PCB*)PCB::running;
	IVTEntry::IVTEntries[ivtNo]->setEvent(this);
	Global::EVENTlist->addToEnd(this);
}

void KernelEv::signal(){
	if(myPCB->state==PCB::READY){
		val=1;
	}else{
		myPCB->state=PCB::READY;
		Scheduler::put(myPCB);
	}
}

void KernelEv::wait(){
	if(myPCB==((PCB*)PCB::running)){
		if(val==0){
			myPCB->state=PCB::BLOCKED;
			Global::requested_dispatch=1;
		}else
			val=0;
	}
}

KernelEv::~KernelEv() {
	signal(); // we need first to free thread if it is waiting on this event
	myPCB=0;
	Global::EVENTlist->takeByID(id); // delete from global list
}

