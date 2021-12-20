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
    int id_shm = shmget(key,sizeof(Posti), 0);
    Posti* p= (Posti*) shmat(id_shm,0,0);
 
        
    pid_t pid=fork();
    if(pid==0){
        srand(time(NULL));
        while((p->disponibilita)>0){          
            Visualizzatore(p);
            sleep(1);
        }        
        exit(1);
    }        

    if(pid>0){        
        wait(NULL);
    }

    shmctl(id_shm,IPC_RMID,0);
    

    

    return 0;
}
