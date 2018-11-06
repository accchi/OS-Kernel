/*
 * KernelTh.h
 *
 *  Created on: May 23, 2018
 *      Author: OS1
 */

#ifndef KERNELTH_H_
#define KERNELTH_H_

class KernelTh { // KERNEL THREAD
public:
	KernelTh();
	virtual ~KernelTh();
	unsigned ss; // stack segment
	unsigned sp; // stack pointer
	unsigned bp; // base pointer
	unsigned *stack; // array that represents stack
	void run();
	static void wrapper();
};

#endif /* KERNELTH_H_ */
