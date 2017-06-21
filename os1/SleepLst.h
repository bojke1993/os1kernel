/*
 * SleepLst.h
 *
 *  Created on: Jun 30, 2016
 *      Author: OS1
 */

#ifndef SLEEPLST_H_
#define SLEEPLST_H_
#include "Queue.h"

class SleepList: public Queue{
public:
	SleepList();
	virtual ~SleepList();

	void insertInOrder(PCB* p);
	PCB* removeFromOrder(PCB* p);
	void TimeOutProcess();
};

#endif /* SLEEPLST_H_ */
