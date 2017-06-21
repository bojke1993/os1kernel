/*
 * locker.h
 *
 *  Created on: Jul 3, 2016
 *      Author: OS1
 */

#ifndef LOCKER_H_
#define LOCKER_H_
#include <iostream.h>

#include "thread.h"
extern volatile int zahtevana_promena_konteksta;
extern volatile int lockFlag;

#define lock lockFlag--;

#define unlock lockFlag++;\
	if(lockFlag==1 && zahtevana_promena_konteksta) dispatch()






#endif /* LOCKER_H_ */
