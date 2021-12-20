#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"


void generatore_produttore(struct ProdConsGen *pc){

    message m1;
        
    /* TODO: utilizzare il costrutto monitor per la produzione del messaggio */
    enter_monitor(&(pc->m));

    while(pc->cont==DIM_QUEUE) {

		//printf("Sospensione - produzione\n");
		wait_condition( &(pc->m), VARCOND_GEN_PRODUTTORI );
		//printf("Riattivazione - produzione\n");
	}


    int dim1 = 1 + rand() %10;
    for(int i=0;i<(dim1);i++)
        m1.stringa[i]= 'a' + (rand()%26);
    m1.stringa[dim1+1]='\0';

    for(int i=0;i<2;i++){
    m1.array[i]=rand()%10;
    }
    m1.var=0;
    m1.type=MSG_TYPE;

        pc->msg[pc->testa]=m1;
    pc->testa=(pc->testa+1)%DIM_QUEUE;

    
    printf("[generatore_produttore] Messaggio generato!\n");
    printf("[generatore_produttore] ...............msg.stringa: %s\n", m1.stringa/* TODO */);
    printf("[generatore_produttore] ...............msg.array[0]: %d\n", m1.array[0]/* TODO */);
    printf("[generatore_produttore] ...............msg.array[1]: %d\n",m1.array[1] /* TODO */);
    printf("[generatore_produttore] ...............msg.var: %d\n", m1.var/* TODO */);



    (pc->cont)++;
    printf("contatore %d\n",pc->cont);


    signal_condition(&(pc->m),VARCOND_GEN_CONSUMATORI);

    leave_monitor(&(pc->m));
 
    /* TODO: ... */
}

void generatore_consumatore(struct ProdConsGen *pc, int ds_queue_gen_filter){

    /* TODO: utilizzare il costrutto monitor per la consumazione del messaggio e l'invio verso il processo filter */
    enter_monitor(&(pc->m));

    while( pc->cont == 0) {

		//printf("Sospensione - consumazione\n");
		wait_condition( &(pc->m), VARCOND_GEN_CONSUMATORI );
		//printf("Riattivazione - consumazione\n");
	}
  
    
    printf("[generatore_consumatore] Messaggio CONSUMATO!\n");
    printf("[generatore_consumatore] ...............msg.stringa: %s\n", pc->msg[pc->coda].stringa);
    printf("[generatore_consumatore] ...............msg.array[0]: %d\n", pc->msg[pc->coda].array[0]);
    printf("[generatore_consumatore] ...............msg.array[1]: %d\n", pc->msg[pc->coda].array[1]);
    printf("[generatore_consumatore] ...............msg.var: %d\n", pc->msg[pc->coda].var);
    
    
    pc->coda=(pc->coda+1)%DIM_QUEUE;
    (pc->cont)--;
    printf("contatore %d\n",pc->cont);

    int ret = msgsnd(ds_queue_gen_filter,(void*)&(pc->msg[pc->coda]),sizeof(message)-sizeof(long),IPC_NOWAIT); /* TODO: invio del messaggio consumato al processo filter */
    
    if (ret<0){
            perror("msgsnd del messaggio on ds_queue_gen_filter FALLITA!");
            exit(-1);
    }
    printf("[generatore_consumatore] Messaggio INVIATO!\n");

    signal_condition( &(pc->m), VARCOND_GEN_PRODUTTORI );
    leave_monitor(&(pc->m));
    
    /* TODO: ... */
}

