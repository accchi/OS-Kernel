/*
 * KernelEv.h
 *
 *  Created on: May 20, 2018
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
class PCB;
#include "Event.h"
typedef int ID;
class EvList;
class Event;

class KernelEv{
public:
	friend class EvList;
	KernelEv(IVTNo,Event*);
	virtual ~KernelEv();
	void wait ();
	void signal();
private:
	PCB* myPCB;
	int val;
	ID id; // change to ID type
	static int generator;
};

#endif /* KERNELEV_H_ */
