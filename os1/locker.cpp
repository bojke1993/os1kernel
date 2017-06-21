/*
 * locker.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: OS1
 */
#include "locker.h"

volatile int zahtevana_promena_konteksta = 0;
volatile int lockFlag = 1;



