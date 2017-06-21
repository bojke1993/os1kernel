/*
 * KernelSem.h
 *
 *  Created on: Jun 13, 2016
 *      Author: OS1
 */

#ifndef KRNLSEM_H_
#define KRNLSEM_H_
//class Queue;
#include "SleepLst.h"

class KernelSem {
public:
	KernelSem(int init);
	virtual ~KernelSem();
	virtual int wait (Time maxTimeToWait);
	virtual void signal();
	int val () const; // Returns the current value of the semaphore
	void removeFromBlocked(PCB* p);


	static SleepList allTimeOuts;
private:
	int value;
	Queue blocked;
};

#endif /* KRNLSEM_H_ */
