#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include"semafori.h"

int main(){

    key_t shm_key =  ftok("/home/vale", 'f');
    int ds_shm = shmget(shm_key, sizeof(int), IPC_CREAT | IPC_EXCL | 0664 );
    if(ds_shm <0){
        perror("errore shmget!");
        exit(1);
    }

    int *p = (int *) shmat(ds_shm, NULL,0);
    if(p==(void*)-1){
        perror("errore shmget!");
        exit(1);
    }

    *p = 0;
   

    //creazione semaforo
    key_t sem_key = ftok("/home/vale", 'v');
    int mutex_id = semget(sem_key, 1, IPC_CREAT | 0664);

	if( mutex_id < 0) {
		perror("Errore SHMGET");
		exit(1);
    }

    semctl(mutex_id, 0, SETVAL, 1);

   
    pid_t pid; 
    
        pid=fork();
        if(pid < 0) {
			perror("Errore FORK");
			exit(1);
		}
        if(pid == 0){
            
            printf("Sono il FIGLIO con PID: %d\n", getpid());
            //i=2; non serve perchè sta la exit

             
            for(int j=0;j<100;j++){
            Wait_Sem(mutex_id,0);
          
           
            *p+=1;
      ;
            Signal_Sem(mutex_id,0);
            }
            exit(1);
        }else  if(pid>0){
            wait(NULL);
           
        }      
       



    printf("Contenuto SHM: %d\n", *p);


    shmctl(ds_shm, IPC_RMID, NULL);
    semctl(mutex_id, 0, IPC_RMID);

     return 0;

}


//se togliamo wait e signal è come se nn usassimo il semaforo
//se togliam signal il processo si sospende. non arriva neanche a ctl ,infatti se fai icps trovi ancora semafori in memoria
//se togliamo wait calcola ancora p=200, solo che non si sospenderanno mai i processi, probabilmente vengono schedulati dallo scheduler
