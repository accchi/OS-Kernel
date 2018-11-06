/*
 * IVTEntry.h
 *
 *  Created on: May 20, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
//#include "Event.h"
typedef void interrupt (*IntFun)(...);
const int numOfEntries=256;
typedef unsigned char IVTNo;
class KernelEv;

class IVTEntry {
public:
	IVTEntry(IVTNo,IntFun);
	virtual ~IVTEntry();
	IntFun oldRoutine;
	IVTNo ivtNumb;
	void signal();
	static IVTEntry* IVTEntries[numOfEntries]; // array of all entries
	KernelEv* myEvent;
	void setEvent(KernelEv*);
	void callOldRoutine();
};

#endif /* IVTENTRY_H_ */
