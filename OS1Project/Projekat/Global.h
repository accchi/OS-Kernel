/*
 * Global.h
 *
 *  Created on: May 13, 2018
 *      Author: OS1
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_
class List;
#include "Thread.h"
class SemList;
class EvList;
class Idle;
class KernelTh;
class Semaphore;
class Event;
typedef void interrupt(*IntFun)(...); // pointer to interrupt functio used for setvect i getvect

struct SysData{ // struct for saving all data needed for system call
	enum Job { CONSTR_THREAD,DESTR_THREAD, SLEEP_THREAD, WAIT_TO_COMPLETE_THREAD,START_THREAD, CONSTR_EVENT, DESTR_EVENT, WAIT_EVENT,
		CONSTR_SEM, DESTR_SEM, WAIT_SEM, SIGNAL_SEM,DISPATCH,VAL_SEM
	};
	Job work;
	Time time;
	StackSize stacksize;
	int id;
	Thread* thread;
	Semaphore* sem;
	Event* event;
	int ret;
	int val;
	int parametar;
	unsigned char ivtNo;
};

class Global {
public:
	static KernelTh* runningKernelTh;
	static SysData* data;
	static List* PCBlist; // Global list of all PCB
	static EvList* EVENTlist; // global list of all EVENTS
	static SemList* SEMlist; // global list of all Semaphores
	static volatile int requested_dispatch; // requested context switch
	static volatile Time counter;
	static void interrupt timer(...);
	static void interrupt syscall(...); // change context to kernel thread
	static void interrupt backtouser(...); // change context to user thread
	void static init();
	void static restore();
	static Idle* idle;
	static volatile int locked; // flag for lock
	static int change; // need change?
	static IntFun oldTimer;
};



#endif /* GLOBAL_H_ */
