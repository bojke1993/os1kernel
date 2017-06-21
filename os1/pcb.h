/*
 * pcb.h
 *
 *  Created on: Apr 21, 2016
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

typedef unsigned int Time;
typedef int ID;
enum State{ACTIVE = 0, BLOCKED, READY, NOT_STARTED};
class Thread;
class KernelSem;

class PCB{
public:
	PCB(unsigned stackSize, Time kvant, void (*body)(Thread *), Thread *t);
	void setState(State s);
	State getState();
	Time getKvant();
	int isOver();

	unsigned getSP();
	void setSP(unsigned sp);

	unsigned getSS();
	void setSS(unsigned ss);

	unsigned getBP();
	void setBP(unsigned bp);

	unsigned getZAVRSIO();
	void setZAVRSIO(unsigned zavrsio);

	void PCB::setTimeOut(unsigned int t);
	unsigned int PCB::getTimeOut();

	KernelSem* getSEM();
	void setSEM(KernelSem* sem);

	void setAwaken(unsigned aw){
		awaken = aw;
	}

	unsigned getAwaken(){
		return awaken;
	}

	ID getID();



private:
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned zavrsio;
	int kvant;
	State myState;
	unsigned *stack;
	ID id;
	static ID posID;
	unsigned int timeOut;
	unsigned awaken;
	KernelSem* sem;
};




#endif /* PCB_H_ */
