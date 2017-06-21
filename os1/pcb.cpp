/*
 * pcb.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: OS1
 */

#include "pcb.h"
#include "KrnlSem.h"
#include <dos.h>
#include <iostream.h>

ID PCB::posID=0;

PCB::PCB(unsigned stackSize, Time kvant, void (*body)(Thread *), Thread *t){
	stack = new unsigned[stackSize];
	stack[stackSize - 1] = FP_SEG(t);
	stack[stackSize - 2] = FP_OFF(t);
	stack[stackSize - 3] = 0;
	stack[stackSize - 4] = 0;

	stack[stackSize - 5] = 0x200;//I bit set

	stack[stackSize - 6] = FP_SEG(body);
	stack[stackSize - 7] = FP_OFF(body);
	stack[stackSize - 8] = 1;
	stack[stackSize - 9] = 2;
	stack[stackSize - 10] = 3;
	stack[stackSize - 11] = 4;

	this -> sp=FP_OFF(stack+stackSize - 16);
	cout << "SP:" <<this -> sp << endl;
	this -> ss=FP_SEG(stack+stackSize - 16);
	this -> bp = FP_OFF(stack + stackSize - 16);
	this -> kvant = kvant;
	this -> zavrsio=0;
	this -> myState = NOT_STARTED;
	this->id=++posID;
}

void PCB::setState(State s){
	myState = s;
}

State PCB::getState(){
	return myState;
}

Time PCB::getKvant(){
	return kvant;
}

int PCB::isOver(){
	return (zavrsio == 1);
}

unsigned PCB::getSP(){
	return sp;
}

void PCB::setSP(unsigned sp){
	this->sp=sp;
}

unsigned PCB::getSS(){
	return ss;
}

void PCB::setSS(unsigned ss){
	this->ss=ss;
}

unsigned PCB::getBP(){
	return bp;
}

void PCB::setBP(unsigned bp){
	this->bp=bp;
}

unsigned PCB::getZAVRSIO(){
	return zavrsio;
}

void PCB::setZAVRSIO(unsigned zavrsio){
	this->zavrsio=zavrsio;
}

ID PCB::getID(){
	return id;
}

void PCB::setTimeOut(unsigned int t){
	this->timeOut=t;
}

unsigned int PCB::getTimeOut(){
	return timeOut;
}

KernelSem* PCB::getSEM(){
	return sem;
}
void PCB::setSEM(KernelSem* sem){
	this->sem=sem;
}
