/*
 * Idle.h
 *
 *  Created on: May 13, 2018
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_
#include "Thread.h"

class Idle: public Thread {
public:
	Idle();
	virtual ~Idle();
	void run();
	PCB* getMyPCB();
};

#endif /* IDLE_H_ */
