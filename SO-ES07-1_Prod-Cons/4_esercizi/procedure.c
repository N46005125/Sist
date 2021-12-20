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

void produttore(struct posti * p, int ds_sem, int pid){

    int indice=0;
    srand(pid);

    int i= rand() % 5+1;
    sleep(i);   
    Wait_Sem(ds_sem, MUTEX_P); 
    int num_posti = rand() % 4+1; 
     
    if(num_posti<=p->posti_disponibili){
         printf("posti disponibili(%d) %d\n", num_posti,pid);  
        p->posti_disponibili=p->posti_disponibili-num_posti;
       // printf("posti disponibili dopo aver decrementato di %d: %d\n", num_posti,p->posti_disponibili);  
               
        Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
    
        for(int j=0;j<num_posti;j++){          

            while(indice<= DIM_BUFFER && p->buffer[indice].stato!= BUFFER_LIBERO){
                indice++;
                }
           
            p->buffer[indice].stato = BUFFER_INAGGIORNAMENTO; 
        }          

        printf("posti acquisiti(%d) %d\n", num_posti,pid); 
        printf("%d\n", p->posti_disponibili); 
        Signal_Sem(ds_sem,MUTEX_P);
        sleep(1);
        for(int j=0;j<num_posti;j++){
            p->buffer[indice-j].id_cliente=pid;
            p->buffer[indice].stato = BUFFER_OCCUPATO;
         //   sleep(3); 
           
        }
        printf("posti acquistati(%d) %d\n", num_posti,pid);  
       
       
        Signal_Sem(ds_sem,MESSAGGIO_DISPONIBILE);
        exit(0);

    }
    else{
    sleep(7);
     printf("posti esauriti(%d) %d\n", num_posti,pid); 
    Signal_Sem(ds_sem,MUTEX_P);
    exit(0);
    }
}
