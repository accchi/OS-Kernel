/*
 * IVTEntry.cpp
 *
 *  Created on: May 20, 2018
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "dos.h"
#include "KernelEv.h"
#include "Event.h"

IVTEntry* IVTEntry::IVTEntries[numOfEntries]= {0};

IVTEntry::IVTEntry(IVTNo ivtNo,IntFun newRoutine) {
#ifndef BCC_BLOCK_IGNORE
	oldRoutine=getvect(ivtNo);
	setvect(ivtNo,newRoutine);
#endif
	ivtNumb=ivtNo;
	IVTEntries[ivtNumb]=this;
	myEvent=0;
}

void IVTEntry::setEvent(KernelEv* event){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf
		cli
	}
#endif
	myEvent=event;
	asm popf
}

void IVTEntry::callOldRoutine(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf
		cli
	}
#endif
	oldRoutine();
	asm popf
}

IVTEntry::~IVTEntry() {
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNumb,oldRoutine);
#endif
	IVTEntries[ivtNumb]=0;
}

void IVTEntry::signal(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf
		cli
	}
#endif
	if(IVTEntries[ivtNumb]!=0)
		myEvent->signal();
	asm popf
}

