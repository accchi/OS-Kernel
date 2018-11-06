/*
 * Semaphor.cpp
 *
 *  Created on: May 19, 2018
 *      Author: OS1
 */

#include "Semaphor.h"
#include "KernSem.h"
#include "dos.h"
#include "SemList.h"
#include "Global.h"

unsigned cx1;
unsigned dx1;

Semaphore::Semaphore(int val) {
	SysData d;
	d.work=SysData::CONSTR_SEM;
	d.val=val;
	d.sem=this;
#ifndef BCC_BLOCK_IGNORE
	cx1=FP_SEG(&d);
	dx1=FP_OFF(&d);
	asm{
		push cx
		push dx
		mov cx,cx1
		mov dx,dx1
		int 61h
	}
#endif
	asm{
		pop dx
		pop cx
	}
}

Semaphore::~Semaphore() {
	SysData d;
	d.work=SysData::DESTR_SEM;
	d.id=myImpl;
#ifndef BCC_BLOCK_IGNORE
	cx1=FP_SEG(&d);
	dx1=FP_OFF(&d);
	asm{
		push cx
		push dx
		mov cx,cx1
		mov dx,dx1
		int 61h
	}
#endif
	asm{
		pop dx
		pop cx
	}
}

void Semaphore::signal(){
	SysData d;
	d.work=SysData::SIGNAL_SEM;
	d.id=myImpl;
#ifndef BCC_BLOCK_IGNORE
	cx1=FP_SEG(&d);
	dx1=FP_OFF(&d);
	asm{
		push cx
		push dx
		mov cx,cx1
		mov dx,dx1
		int 61h
	}
#endif
	asm{
		pop dx
		pop cx
	}
}

int Semaphore::wait(int toBlock){
	SysData d;
	d.work=SysData::WAIT_SEM;
	d.id=myImpl;
	d.parametar=toBlock;
	#ifndef BCC_BLOCK_IGNORE
		cx1=FP_SEG(&d);
		dx1=FP_OFF(&d);
		asm{
			push cx
			push dx
			mov cx,cx1
			mov dx,dx1
			int 61h
		}
	#endif
#ifndef BCC_BLOCK_IGNORE
		asm{
			pop dx
			pop cx
		}
#endif
	return d.ret;
}

int Semaphore::val()const{
	SysData d;
	d.work=SysData::VAL_SEM;
	d.id=myImpl;
#ifndef BCC_BLOCK_IGNORE
		cx1=FP_SEG(&d);
		dx1=FP_OFF(&d);
		asm{
			push cx
			push dx
			mov cx,cx1
			mov dx,dx1
			int 61h
		}
#endif
#ifndef BCC_BLOCK_IGNORE
		asm{
			pop dx
			pop cx
		}
#endif
	return d.ret;
}
