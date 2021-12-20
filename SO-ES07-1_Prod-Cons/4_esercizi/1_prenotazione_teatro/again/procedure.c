#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"


void Cliente(Posti* p,int id_sem,int i,int pid){
   
    int index=0;

    Wait_Sem(id_sem,MUTEX_P);    

    int t=rand()%6;
    sleep(t);

    int num_posti=rand()%4+1;

    
    if(num_posti<=(p->disponibilita)){
       
        while(index<=DIM_VETTORE && p->pos[index].stato!= LIBERO){
            index++;
        }
        p->pos[index].stato=IN_AGGIORNAMENTO;
    }else{
        printf("Disponibilità esaurita, non puoi prenotare.\n");
        Signal_Sem(id_sem,MUTEX_P);
        exit(3);
    }
    Signal_Sem(id_sem,MUTEX_P);

    sleep(1);
    for(int i=0;i<num_posti;i++){
        p->pos[index+i].id_cliente=pid;
        p->pos[index+i].stato=OCCUPATO;
    }
    p->disponibilita=(p->disponibilita)-num_posti;
    printf("Cliente %d prenota %d posti. Disponibilità: %d\n",pid,num_posti,p->disponibilita);

    
}

void Visualizzatore(Posti* p){
    printf("\nSituazione teatro:\n");
    for(int i=0;i<DIM_VETTORE;i++){
        printf("-Numero posto: %d -Stato: %d -Cliente: %d\n",i+1,p->pos[i].stato,p->pos[i].id_cliente);
    }
}

