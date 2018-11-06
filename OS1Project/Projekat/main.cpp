/*
 * main.cpp
 *
 *  Created on: May 10, 2018
 *      Author: OS1
 */
#include <IOSTREAM.h>
#include "List.h"
#include "PCB.h"
#include "SrtdList.h"
#include "Thread.h"
#include "Global.h"
#include "Semaphor.h"

int userMain(int,char**);

int main(int argc, char** argv){

	Global::init();

	userMain(argc,argv);

	Global::restore();

	return 0;
}



