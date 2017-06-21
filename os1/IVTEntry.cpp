/*
 * IVTEntry.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: OS1
 */

#include "IVTEntry.h"
#include <DOS.H>
#include <IOSTREAM.H>
#include "locker.h"

unsigned funcOffset, funcSegment;
IVTEntry *IVTEntry::entries[256];

IVTEntry::IVTEntry(unsigned num, intrFunction func, int callOld) {
	lock;
	IVTEntry::entries[num] = this;
	intNumber = num;
	this->callOld = callOld;
	asm {
		push es
		push ax
		push di

		mov ax, 0
		mov es, ax

		mov ax, 4h
		mul word ptr [bp + 10]
		mov di, ax
		mov ax, word ptr es:di
		mov word ptr funcOffset, ax

		mov ax, di
		add ax, 2h
		mov di, ax
		mov ax, word ptr es:di
		mov word ptr funcSegment, ax

		pop di
		pop ax
		pop es
	}

	FP_SEG(oldFunction) = funcSegment;
	FP_OFF(oldFunction) = funcOffset;

	funcSegment = FP_SEG(func);
	funcOffset = FP_OFF(func);

	asm{
		push es
		push ax
		push di

		mov ax, 0
		mov es, ax

		mov ax, 4h
		mul word ptr [bp + 10]
		mov di, ax

		mov ax, funcOffset
		mov word ptr es:di, ax

		mov ax, di
		add ax, 2h
		mov di, ax
		mov ax, funcSegment
		mov word ptr es:di, ax

		pop di
		pop ax
		pop es
	}
	unlock;
}

IVTEntry::~IVTEntry() {
// TODO Auto-generated destructor stub
}


void IVTEntry::addEvent(KernelEv *e){
	this->e = e;
}

KernelEv* IVTEntry::getEvent(){
	return e;
}

