/*
 * Queue.cpp
 *
 *  Created on: May 12, 2016
 *      Author: OS1
 */

#include "Queue.h"
#include "schedule.h"
#include <iostream.h>


Queue::Queue() {
	head=tail=0;
}

Queue::~Queue(){
	while(head){
		Elem* temp = head;
		head = head->next;
		delete temp;
	}
}




void Queue::insertQ(PCB* data){
	Elem *novi=new Elem(data);
	if(head==0){
		tail=head=novi;
	}
	else{
		tail->next=novi;
		tail=novi;
	}
}


PCB* Queue::getFromQ(){
	if(head==0){
		cout<<"Red je prazan!!\n";
		return 0;
	}
	else{
		PCB* ret=head->pcb;
		Elem* temp = head;
		head=head->next;
		if(head == 0) tail = 0;
		delete temp;
		return ret;
	}
}

int Queue::isEmpty(){
	return head==0;
}

PCB* Queue::iterator(){
	PCB* retData = iter->pcb;
	iter = iter->next;
	return retData;
}

int Queue::iteratorEnd(){
	if(iter == 0){
		return 1;
	}else return 0;
}

void Queue::resetIterator(){
	iter = head;
}

PCB* Queue::remove(PCB* data){
	if(head == 0) return 0;

	if(head->pcb==data){
		PCB* retPCB=head->pcb;
		Elem* tmp = head;
		head=head->next;
		delete tmp;
		return retPCB;
	}
	Elem*temp=head;
	while(temp->next && (temp->next->pcb!=data)){
		temp=temp->next;
	}
	if(temp==tail){
		return 0;
	}

	PCB* retPCB=temp->next->pcb;//head->pcb;
	Elem* del = temp->next;//
	if(del == tail){
		tail = temp;
	}
	temp->next = del->next;
	delete del;
	return retPCB;
}

