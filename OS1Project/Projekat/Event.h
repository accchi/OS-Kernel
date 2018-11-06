/*
 * Event.h
 *
 *  Created on: May 20, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "Thread.h"
#include "IVTEntry.h"
#include "Global.h"
typedef int ID;

#define PREPAREENTRY(numEntry, callOld)\
void interrupt inter##numEntry(...); \
IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
void interrupt inter##numEntry(...) {\
newEntry##numEntry.signal();\
if (callOld == 1)\
newEntry##numEntry.callOldRoutine();\
if(Global::locked==0)\
dispatch();\
}

typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
	Event (IVTNo ivtNo);
	~Event();
	void wait();
protected:
	friend class KernelEv;
	void signal(); // can call KernelEv
private:
	ID myImpl;
};

#endif /* EVENT_H_ */
