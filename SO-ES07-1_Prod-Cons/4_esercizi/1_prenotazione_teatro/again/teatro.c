#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"


int main(){
    key_t key = ftok(".",'k');
    int id_shm = shmget(key,sizeof(Posti), IPC_CREAT | 0664);
    Posti* p= (Posti*) shmat(id_shm,0,0);

    p->disponibilita=DIM_VETTORE;
    for(int i=0;i<DIM_VETTORE;i++){
        p->pos[i].id_cliente=0;
        p->pos[i].stato=LIBERO;
    }

    key_t keys = ftok(".",'s');
    int id_sem = semget(keys,1, IPC_CREAT | 0664);
    semctl(id_sem,0,SETVAL,1);

       
    pid_t pid;

 
    for(int i=0;i<NUM_CLIENTI;i++){
        pid=fork();
        if(pid==0){
            srand(getpid()*time(NULL));
            if((p->disponibilita)>0)  
                sleep(1);
                Cliente(p,id_sem,i,getpid());
                
            exit(10);
        }           
    }

    pid=fork();
    if(pid==0){
        execl("./visualizzatore","./visualizzatore", NULL);
    }

        
   

    
    for(int i=0;i<NUM_CLIENTI+1;i++){
        if(pid>0){        
            wait(NULL);
        }
    }

  
    shmctl(id_shm,IPC_RMID,0);

 
    return 0;
}