/*
 * List.cpp
 *
 *  Created on: May 15, 2016
 *      Author: OS1
 */

#include "List.h"

List::List() {
	head=tail=0;
}

List::~List() {
	Elem* temp=head;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
}

void List::insertL(Thread* t){
	Elem *novi=new Elem(t);
	if(head==0){
		tail=head=novi;
		}
	else{
		tail->next=novi;
		tail=novi;
	}

}

Thread* List::getThreadID(ID id){
	Elem* temp=head;
	while(temp){
		if(temp->t->getId()==id){
			break;
		}
		temp = temp->next;
	}

	return temp->t;
}


