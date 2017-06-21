/*
 * KernelEv.h
 *
 *  Created on: Jul 3, 2016
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

typedef unsigned char IVTNo;
class PCB;

class KernelEv {
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void wait();
	void signal(); // can call KernelEv


private:
	int flag;
	PCB* p;
	IVTNo numberOfInterrupt;
};

#endif /* KERNELEV_H_ */
