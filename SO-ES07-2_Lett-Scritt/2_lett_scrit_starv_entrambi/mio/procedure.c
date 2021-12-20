#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"
#include "semafori.h"

void InizioLettura(Buffer* p,int id_sem){
    Wait_Sem(id_sem,MUTEX_L);
    p->NUM_LETTORI=p->NUM_LETTORI+1;

    if(p->NUM_LETTORI==1){
        Wait_Sem(id_sem,SYNC);
    }

    Signal_Sem(id_sem,MUTEX_L);

}

void FineLettura(Buffer* p,int id_sem){
    Wait_Sem(id_sem,MUTEX_L);
    p->NUM_LETTORI=p->NUM_LETTORI-1;

    if(p->NUM_LETTORI==0){
        Signal_Sem(id_sem,SYNC);
    }

    Signal_Sem(id_sem,MUTEX_L);
}


void InizioScrittura(Buffer* p,int id_sem){
   
    Wait_Sem(id_sem,MUTEX_S);
    p->NUM_SCRITTORI=p->NUM_SCRITTORI+1;
    if(p->NUM_SCRITTORI==1){
        Wait_Sem(id_sem,SYNC);
    }
    Signal_Sem(id_sem,MUTEX_S);
    Wait_Sem(id_sem,MUTEX);
}


void FineScrittura(Buffer* p,int id_sem){
    Signal_Sem(id_sem,MUTEX);  
    Wait_Sem(id_sem,MUTEX_S);
    p->NUM_SCRITTORI=p->NUM_SCRITTORI-1;
    if(p->NUM_SCRITTORI==0){
        Signal_Sem(id_sem,SYNC);
    }
    Signal_Sem(id_sem,MUTEX_S);
    

}


void Lettore(Buffer* p,int id_sem ,int i){

    InizioLettura(p,id_sem);

    sleep(1);
    printf("Processo %d, valore letto=<%ld>, numero lettori=%d \n",i, p->mess, p->NUM_LETTORI);
    

    FineLettura(p,id_sem);
}

void Scrittore(Buffer* p,int id_sem,int i){

    InizioScrittura(p,id_sem);
    sleep(1);
    p->mess=rand()%30+1;
    sleep(1); // per simulare un ritardo di lettura
    printf("Processo %d, valore scritto: <%ld> \n", i,p->mess);
    

    FineScrittura(p,id_sem);
}