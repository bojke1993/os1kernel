/*
 * List.h
 *
 *  Created on: May 15, 2016
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_
#include "thread.h"

class List {
private:
	struct Elem{
		Thread* t;
		Elem* next;
		Elem(Thread *tt, Elem* el=0){t=tt; next=el;}
	};

	Elem* head;
	Elem* tail;
public:
	List();
	~List();
	void insertL(Thread* t);
	Thread* getThreadID(ID id);

};

#endif /* LIST_H_ */
