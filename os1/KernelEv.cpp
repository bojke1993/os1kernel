/*
 * KernelEv.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: OS1
 */

#include "KernelEv.h"
#include "thread.h"
#include "SCHEDULE.H"
#include "pcb.h"
#include "locker.h"

#include <iostream.h>

#include "IVTEntry.h"

extern PCB* running;
#include <iostream.h>

KernelEv::KernelEv(IVTNo ivtNo) {
	lock;
	this->numberOfInterrupt=ivtNo;
	p=running;
	flag=0;
	IVTEntry::entries[ivtNo]->addEvent(this);
	unlock;
}

KernelEv::~KernelEv() {
	// TODO Auto-generated destructor stub
}

void KernelEv::wait(){
	lock;
	if(running==p){
		flag=1;
		p->setState(BLOCKED);
		unlock;
		dispatch();
	}else{
		unlock;
	}

}

void KernelEv::signal(){
	lock;
	if(flag==1){
		flag=0;
		p->setState(READY);
		Scheduler::put(p);
	}
	unlock;
}
