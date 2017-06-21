/*
 * IVTEntry.h
 *
 *  Created on: Jul 3, 2016
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "KernelEv.h"

#define MAX_ENTRIES 256

typedef void interrupt (*intrFunction)();

class IVTEntry {
public:
	IVTEntry(unsigned num, intrFunction func, int callOld);
	virtual ~IVTEntry();

	void callOldInterrupt(){
		if(callOld){
			(*oldFunction)();
		}
	}
	void addEvent(KernelEv *e);
	KernelEv* getEvent();
	static IVTEntry *entries[MAX_ENTRIES];
	static IVTEntry *getEntry(int num){
		return entries[num];
	}
private:
	intrFunction oldFunction;
	int callOld;
	unsigned intNumber;
	KernelEv *e;
};

#define PREPAREENTRY(intNo, callOld)\
	void interrupt int##intNo(){\
		IVTEntry::getEntry(intNo)->getEvent()->signal();\
		IVTEntry::getEntry(intNo)->callOldInterrupt();}\
		IVTEntry entry##intNo(intNo, int##intNo, callOld);


#endif /* IVTENTRY_H_ */
