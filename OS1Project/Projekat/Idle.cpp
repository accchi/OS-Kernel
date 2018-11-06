/*
 * Idle.cpp
 *
 *  Created on: May 13, 2018
 *      Author: OS1
 */

#include "Idle.h"
#include "Global.h"
#include "List.h"

Idle::Idle():Thread(defaultStackSize,defaultTimeSlice) {

}

Idle::~Idle() {
}

void Idle::run(){
	while(1){ }
}

PCB* Idle::getMyPCB(){
	return Global::PCBlist->getByID(myPCB);
}

