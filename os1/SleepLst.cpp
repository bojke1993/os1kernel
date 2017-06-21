/*
 * SleepLst.cpp
 *
 *  Created on: Jun 30, 2016
 *      Author: OS1
 */

#include "SleepLst.h"
#include "SCHEDULE.H"
#include "KrnlSem.h"
#include "locker.h"
#include <IOSTREAM.H>

SleepList::SleepList() {
	head = tail = 0;
}

SleepList::~SleepList() {
}

void SleepList::insertInOrder(PCB* p) {
	Elem* temp = head;
	if (head == 0) {
		Elem *novi = new Elem(p);
		head = tail = novi;
		return;
	}

	if (p->getTimeOut() < head->pcb->getTimeOut()) {
		head->pcb->setTimeOut(head->pcb->getTimeOut() - p->getTimeOut());
		Elem* novi = new Elem(p);
		novi->next = head;
		head = novi;
		return;
	}

	p->setTimeOut(p->getTimeOut() - head->pcb->getTimeOut());
	while (temp->next && (p->getTimeOut() >= temp->next->pcb->getTimeOut())) {
		p->setTimeOut(p->getTimeOut() - temp->next->pcb->getTimeOut());
		temp = temp->next;
	}

	Elem* novi = new Elem(p);
	novi->next = temp->next;
	temp->next = novi;
	if (novi->next != 0) {
		novi->next->pcb->setTimeOut(
				novi->next->pcb->getTimeOut() - novi->pcb->getTimeOut());
	} else
		tail = novi;
}

PCB* SleepList::removeFromOrder(PCB* data) {
	if (head == 0)
		return 0;

	if (head->pcb == data) {
		PCB* retPCB = head->pcb;
		Elem* tmp = head;
		head = head->next;
		if(head != 0){
			head->pcb->setTimeOut(head->pcb->getTimeOut() + tmp->pcb->getTimeOut());
		}else tail = head;
		delete tmp;
		return retPCB;
	}

	Elem*temp = head;
	while (temp->next && (temp->next->pcb != data)) {
		temp = temp->next;
	}
	if (temp == tail) {
		return 0;
	}

	PCB* retPCB = temp->next->pcb; //head->pcb;
	Elem* del = temp->next; //
	if (del == tail) {
		tail = temp;
	}
	temp->next = del->next;
	if(temp->next != 0){
		temp->next->pcb->setTimeOut(temp->next->pcb->getTimeOut() + del->pcb->getTimeOut());
	}
	delete del;
	return retPCB;
}

void SleepList::TimeOutProcess() {
	if(head != 0){
		head->pcb->setTimeOut(head->pcb->getTimeOut()-1);
		while(head && head->pcb->getTimeOut()==0){
			PCB *p = getFromQ();
			p->setState(READY);
			p->getSEM()->removeFromBlocked(p);
			Scheduler::put(p);
		}
	}
}

