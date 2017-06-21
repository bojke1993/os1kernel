/*
 * thread.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: OS1
 */
#include "thread.h"
#include "schedule.h"
#include "pcb.h"
#include "Queue.h"
#include "List.h"
#include "locker.h"


List* allThreads=new List();
PCB* running;

Thread::Thread(StackSize stackSize , Time timeSlice ){
	lock;
	myPCB=new PCB(stackSize, timeSlice, runWrapper, this);
	blocked=new Queue();
	allThreads->insertL(this);
	unlock;

}

Thread::~Thread(){
	lock;
	delete myPCB;
	myPCB = 0;
	unlock;
}

void Thread::start(){
	lock;
	if(myPCB != 0) {
		myPCB->setState(READY);
		Scheduler::put(myPCB);
	}
	unlock;
}


void Thread::runWrapper(Thread *t){
	t->run();
	lock;
	t->myPCB->setZAVRSIO(1);
	while(!(t->blocked->isEmpty())){
		PCB* p=t->blocked->getFromQ();
		t->blocked->iterator();
		p->setState(READY);
		Scheduler::put(p);
	}
	unlock;
	dispatch();

}

void Thread::waitToComplete(){
	lock;
	if (myPCB->getZAVRSIO()!=1){
		running->setState(BLOCKED);
		this->blocked->insertQ(running);
		unlock;
		dispatch();
	}else {
		unlock;
	}

}

ID Thread::getId(){
	return myPCB->getID();
}

ID Thread::getRunningId(){
	return running->getID();
}

Thread* Thread::getThreadById(ID id){
	lock;
	Thread* t = allThreads->getThreadID(id);
	unlock;
	return t;
}





