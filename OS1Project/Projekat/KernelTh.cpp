/*
 * KernelTh.cpp
 *
 *  Created on: May 23, 2018
 *      Author: OS1
 */

#include "KernelTh.h"
#include "dos.h"
#include "Thread.h"
#include "Global.h"
#include "List.h"
#include "KernSem.h"
#include "SemList.h"
#include "KernelEv.h"
#include "EvList.h"

void KernelTh::wrapper(){
	Global::runningKernelTh->run();
}

void KernelTh::run(){
	while(1){
		Global::locked=1;
#ifndef BCC_BLOCK_IGNORE
		asm sti
#endif
		switch(Global::data->work){
		case SysData::START_THREAD:
			Global::PCBlist->getByID(Global::data->id)->start();
			break;
		case SysData::WAIT_TO_COMPLETE_THREAD:
			Global::PCBlist->getByID(Global::data->id)->waitToComplete();
			break;
		case SysData::CONSTR_THREAD:
			new PCB(Global::data->stacksize,Global::data->time,Global::data->thread);
			break;
		case SysData::SLEEP_THREAD:
			PCB::sleep(Global::data->time);
			break;
		case SysData::DISPATCH:
			Global::requested_dispatch=1;
			break;
		case SysData::DESTR_THREAD:
			delete Global::PCBlist->takeByID(Global::data->id); // takeByID because we need to delete it from Global list
			break;
		case SysData::CONSTR_EVENT:
			new KernelEv(Global::data->ivtNo,Global::data->event);
			break;
		case SysData::DESTR_EVENT:
			delete Global::EVENTlist->getByID(Global::data->id);
			break;
		case SysData::WAIT_EVENT:
			Global::EVENTlist->getByID(Global::data->id)->wait();
			break;
		case SysData::CONSTR_SEM:
			new KernelSem(Global::data->val,Global::data->sem);
			break;
		case SysData::DESTR_SEM:
			delete Global::SEMlist->getByID(Global::data->id);
			break;
		case SysData::SIGNAL_SEM:
			Global::SEMlist->getByID(Global::data->id)->signal();
			break;
		case SysData::WAIT_SEM:
			Global::data->ret=Global::SEMlist->getByID(Global::data->id)->wait(Global::data->parametar); // parametar==toBlock
			break;
		case SysData::VAL_SEM:
			Global::data->ret=Global::SEMlist->getByID(Global::data->id)->getVal();
			break;
		}
#ifndef BCC_BLOCK_IGNORE
		asm cli
#endif
		Global::locked=0;
		asm int 63h
	}
}

KernelTh::KernelTh() {
	stack=new unsigned[defaultStackSize/sizeof(unsigned)]; // creating kernel stack
	stack[defaultStackSize/sizeof(unsigned)-3]=0x000; // PSW-> I flag = 1 0x200
#ifndef BCC_BLOCK_IGNORE
	stack[defaultStackSize/sizeof(unsigned)-4]=FP_SEG(KernelTh::wrapper); // PC
	stack[defaultStackSize/sizeof(unsigned)-5]=FP_OFF(KernelTh::wrapper); // later we need to put here parametar Thread*
	ss=FP_SEG(stack+defaultStackSize/sizeof(unsigned)-14); // stack pointer need to points to the -14 location
	sp=FP_OFF(stack+defaultStackSize/sizeof(unsigned)-14);
#endif
	bp=sp;

}

KernelTh::~KernelTh() {
	delete[] stack;
	stack=0;
}

