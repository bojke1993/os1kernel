/*
 * Semaphore.cpp
 *
 *  Created on: May 12, 2016
 *      Author: OS1
 */

#include "KrnlSem.h"
#include "Sem.h"

Semaphore::Semaphore(int init){
	myImpl = new KernelSem(init);
}

Semaphore::~Semaphore (){
	delete myImpl;
}

/*void Semaphore::block() {
	if(setjmp(Thread::runningThread->context)==0{
		blocked->insertQ(Thread::runningThread);
		Thread::runningThread=Scheduler::get();
		longjump(Thread::runningThread->context,1);
	}else return;
}

void Semaphore::deblock(){
	Thread *t=blocked->getFromQ();
	Scheduler::put(t);
}*/

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
	/*lock(lck);
	if(--val<0)
		block();
	unlock(lck);*/
}

void Semaphore::signal(){
	myImpl->signal();
	/*lock(lck);
	if(val++<0)
		deblock();
	unlock(lck);*/
}

int Semaphore::val () const{
	return myImpl->val();
}
