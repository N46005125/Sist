#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include<time.h>

#include "header.h"

int main(){

    int id_shm = shmget(IPC_PRIVATE, sizeof(Buffer),IPC_CREAT | 0664);
    Buffer* p = (Buffer*)shmat(id_shm,0,0);
    p->NUM_LETTORI=0;
    p->NUM_SCRITTORI=0;
    p->mess=0;
   
    int id_sem = semget(IPC_PRIVATE,4,IPC_CREAT|0664);

    semctl(id_sem,MUTEX_L,SETVAL,1);
    semctl(id_sem,SYNC,SETVAL,1);
    semctl(id_sem,MUTEX_S,SETVAL,1);
    semctl(id_sem,MUTEX,SETVAL,1);

    pid_t pid; 

 
    for(int i=0;i<NUM_PROD;i++){
        pid=fork();
        if(pid==0){
            srand(getpid()*time(NULL));
            sleep(2);
            Scrittore(p,id_sem,i);
            exit(1);
        }
    }

       for(int i=0;i<NUM_CONS;i++){
        pid=fork();
        if(pid==0){
            srand(getpid()*time(NULL));
            sleep(2);
            Lettore(p,id_sem,i);
            exit(1);
        }
    }


  


    for(int i=0;i<NUM_CONS+NUM_PROD;i++){
        wait(NULL);
    }

    semctl(id_sem,0,IPC_RMID);
    shmctl(id_shm,IPC_RMID,0);


    return 0;
}