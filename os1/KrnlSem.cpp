/*
 * KernelSem.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: OS1
 */

#include "KrnlSem.h"
#include "thread.h"
#include "Queue.h"
#include "SCHEDULE.H"
#include "SleepLst.h"
#include "locker.h"


extern PCB* running;
SleepList KernelSem::allTimeOuts;

KernelSem::KernelSem(int init) {
	value=init;
}

KernelSem::~KernelSem() {
}

int KernelSem::wait (Time maxTimeToWait){
	lock;

	if(--value<0){
		if(maxTimeToWait > 0){
			running->setTimeOut(maxTimeToWait);
			allTimeOuts.insertInOrder(running);
		}
		running->setState(BLOCKED);
		running->setSEM(this);
		blocked.insertQ(running);
		unlock;
		dispatch();
	}else {
		unlock;
	}

	return running->getAwaken();
}
void KernelSem::signal(){
	lock;
	if(++value<=0){
		PCB* pl=blocked.getFromQ();
		allTimeOuts.removeFromOrder(pl);
		pl->setState(READY);
		pl->setAwaken(1);
		Scheduler::put(pl);
	}
	unlock;
}

int KernelSem::val () const{

	return value; // Returns the current value of the semaphore

}

void KernelSem::removeFromBlocked(PCB* p){
	lock;
	p->setAwaken(0);
	value++;
	blocked.remove(p);
	unlock;
}
