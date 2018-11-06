/*
 * Event.cpp
 *
 *  Created on: May 20, 2018
 *      Author: OS1
 */

#include "Event.h"
#include "KernelEv.h"
#include "Global.h"
#include "EvList.h"
#include "dos.h"

unsigned cx2;
unsigned dx2;

Event::Event(IVTNo ivtNo) {
	SysData d;
	d.work=SysData::CONSTR_EVENT;
	d.ivtNo=ivtNo;
	d.event=this;
#ifndef BCC_BLOCK_IGNORE
	cx2=FP_SEG(&d);
	dx2=FP_OFF(&d);
	asm{
		push cx
		push dx
		mov cx,cx2
		mov dx,dx2
		int 61h
	}
	asm{
		pop dx
		pop cx
	}
#endif
}

Event::~Event() {
	SysData d;
	d.work=SysData::DESTR_EVENT;
	d.id=myImpl;
#ifndef BCC_BLOCK_IGNORE
		cx2=FP_SEG(&d);
		dx2=FP_OFF(&d);
		asm{
			push cx
			push dx
			mov cx,cx2
			mov dx,dx2
			int 61h
		}
		asm{
			pop dx
			pop cx
		}
#endif
}

void Event::signal(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf
		cli
	}
#endif
	Global::EVENTlist->getByID(myImpl)->signal();
	asm popf
}

void Event::wait(){
	SysData d;
	d.work=SysData::WAIT_EVENT;
	d.id=myImpl;
#ifndef BCC_BLOCK_IGNORE
		cx2=FP_SEG(&d);
		dx2=FP_OFF(&d);
		asm{
			push cx
			push dx
			mov cx,cx2
			mov dx,dx2
			int 61h
		}
		asm{
			pop dx
			pop cx
		}
#endif
}
