/*
 * Queue.h
 *
 *  Created on: May 12, 2016
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "pcb.h"

class Queue {
protected:
	struct Elem{
		PCB *pcb;
		Elem* next;
		Elem(PCB *p, Elem* sl=0){pcb=p;next=sl;}
	};
protected:
	Elem *head;
	Elem *tail;
	Elem *iter;
public:
	Queue();
	virtual ~Queue();
	void insertQ(PCB* data);
	PCB* getFromQ();
	PCB* remove(PCB *data);	//todo implementirati remove
	int isEmpty();
	void resetIterator();
	PCB* iterator();
	int iteratorEnd();
};

#endif /* QUEUE_H_ */
