#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#include "header.h"

int main(){
    
    int id_shm=shmget(IPC_PRIVATE,sizeof(Buffer)+ sizeof(vector),IPC_CREAT|0664);
 
    int* v=shmat(id_shm,0,0);
    Buffer* buf=(Buffer*) shmat(id_shm,0,0);

    

   
    int id_sem=semget(IPC_PRIVATE,1,IPC_CREAT|0664);
    semctl(id_sem,0,SETVAL,1);

    buf->val=0;
    int sx=0;
    int dx=2;

   sleep(2);

    pid_t pid;   
    srand(time(NULL));
    for(int i=0;i<DIM;i++){
        v[i]=rand()%30 +1;
        printf("%d ",v[i]);        
    }
    printf("\n"); 

    
    for(int i=0;i<10;i++){
        pid=fork();
        if(pid==0){
         
            Figlio(buf,id_sem,v,sx,dx);                    
            exit(1);
        }
        sleep(1);
        sx=sx+2;
        dx=dx+2;   
        
    }
    for(int i=0;i<10;i++){
        if(pid>0){
            wait(NULL);
        }
    }

    printf("\nIl valore prelevato è %d\n",buf->val);

    return 0;
}