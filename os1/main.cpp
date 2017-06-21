/*
 * swc.cpp
 *
 *  Created on: Apr 10, 2016
 *      Author: OS1
 */
#include <iostream.h>
#include <dos.h>
#include "pcb.h"
#include "schedule.h"
#include "thread.h"
#include "Queue.h"
#include "SleepLst.h"
#include "KrnlSem.h"
#include "IVTEntry.h"
#include "locker.h"

unsigned tsp;
unsigned tss;
unsigned tbp;





volatile int brojac=20;
//extern int zahtevana_promena_konteksta;


/*class A: public Thread{
public:
	A():sem(0){

	}

	KernelSem sem;

	void run(){
		for (int i =0; i < 30; ++i) {
				lock;						//zabrana promene konteksta
				cout<<"u a() i = "<<i<<endl;
				unlock;						//setujemo fleg za dozvolu promene konteksta i
				if(zahtevana_promena_konteksta){	//pitamo da li je eksplicitno trazena
					dispatch();						//ako jeste menjamo kontekst
				}

				sem.wait(36);
				for (int k = 0; k<10000; ++k)
					for (int j = 0; j <30000; ++j);
			}
	}
};

class B: public Thread{
public:
	B():sem(0){

	}
	KernelSem sem;
	void run(){
		for(int i=0; i<30; ++i){
				lock;
				cout<<"u b() i= "<<i<<endl;
				unlock;
				if(zahtevana_promena_konteksta){
					dispatch();
				}
				for(int j=0; j<10000; ++j)
					for(int k=0; k<30000; ++k);
				sem.wait(18);
			}
	}
};*/

extern PCB* running;
extern void tick();
PCB* idle;

void interrupt timer(){	// prekidna rutina
	if (!zahtevana_promena_konteksta) brojac--;
	if (brojac == 0 || zahtevana_promena_konteksta) {


		if(lockFlag == 1){
		asm {
			// cuva sp
			mov tsp, sp
			mov tss, ss
			mov tbp, bp

		}

		running->setSP(tsp);
		running->setSS(tss);
		running->setBP(tbp);

		/*lock;


		cout<<"Promena konteksta!!! Brojac="<<brojac<<", "<<running->getID()<<endl;
		asm cli;

		unlock;*/

		if(!(running->getZAVRSIO())&&(running->getState()==ACTIVE)) {
			running->setState(READY);
			Scheduler::put(running);
		}
		running= Scheduler::get();	// Scheduler
		if(running == 0){
			running = idle;
		}

		running->setState(ACTIVE);
		tsp = running->getSP();
		tss = running->getSS();
		tbp = running->getBP();

		brojac = running->getKvant();

		asm {
			mov sp, tsp   // restore sp
			mov ss, tss
			mov bp,tbp
		}
		}
		else zahtevana_promena_konteksta=1;
	}

	// poziv stare prekidne rutine koja se
     // nalazila na 08h, a sad je na 60h
     // poziva se samo kada nije zahtevana promena
     // konteksta – tako se da se stara
     // rutina poziva samo kada je stvarno doslo do prekida

	//todo obrada timeout liste (head umanjujem za  1 i ako je nula uklanjam sve nule sa pocetka i stavljam state READY) i stavljam u scheduler

	if(!zahtevana_promena_konteksta) {
		KernelSem::allTimeOuts.TimeOutProcess();
		tick();
		asm int 60h;
	}

	zahtevana_promena_konteksta = 0;
}


void dispatch(){
	asm cli;
	zahtevana_promena_konteksta=1;
	timer();
	asm sti;
}

unsigned oldTimerOff, oldTimerSeg;

void inic(){

	asm{
		cli
		push es
		push ax
		mov ax, 0
		mov es, ax

		mov ax, word ptr es:0022h
		mov word ptr oldTimerSeg, ax

		mov ax, word ptr es:0020h
		mov word ptr oldTimerOff, ax

		mov word ptr es:0022h, seg timer
		mov word ptr es:0020h, offset timer

		mov ax, oldTimerSeg
		mov word ptr es:0182h, ax

		mov ax, oldTimerOff
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
}

void restore(){
	asm{
		cli
				push es
				push ax
				mov ax, 0
				mov es, ax

				mov ax, word ptr oldTimerSeg
				mov word ptr es:0022h, ax

				mov ax, word ptr oldTimerOff
				mov word ptr es:0020h, ax

				pop ax
				pop es
				sti
	}
}



void exitThread(){
	running->setZAVRSIO(1);
	dispatch();
}


void doSomething(){
	/*lock
	A a;
	cout<<"napravio a"<<endl;
	a.start();
	cout<<"startovao a"<<endl;
	B b;
	cout<<"napravio b"<<endl;
	b.start();
	cout<<"startovao b"<<endl;

	PCB* mainPCB = new PCB(1024, 20, 0, 0);//msm da umesto 1024 moze 0

	mainPCB -> setState(ACTIVE);
	running = mainPCB;
	unlock

	for (int i = 0; i < 30; ++i) {
  	lock
  	cout<<"main "<<i<<endl;
  	unlock

	for (int j = 0; j< 30000; ++j)
		for (int k = 0; k < 30000; ++k);
	}
	cout<<"Happy End"<<endl;

	while(1){

	}*/
}

extern int userMain (int argc, char* argv[]);

void idleFunc(Thread *t){
	while(1){
		dispatch();
	}
}

int main(int argc, char* argv[]){
	asm cli;
	inic();
	PCB* mainPCB = new PCB(1024, 20, 0, 0);//msm da umesto 1024 moze 0
	mainPCB -> setState(ACTIVE);
	running = mainPCB;
	idle = new PCB(256, 5, idleFunc, 0);
	asm sti;
	int res = userMain(argc, argv);

	restore();
	return res;
}








