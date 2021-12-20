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

    srand(time(NULL));
    key_t chiave = ftok(".teatro", 'k');

	int ds_shm = shmget(chiave, sizeof(struct posti), IPC_CREAT|0664);

	if(ds_shm<0) { perror("SHM errore"); exit(1); }

    struct posti * p;

	p = (struct posti *) shmat(ds_shm, NULL, 0);


	for(int i=0; i<DIM_BUFFER; i++) {
		p->buffer[i].stato = BUFFER_LIBERO;
	}
    
  
    p->posti_disponibili=DIM_BUFFER;

    key_t chiavesem = ftok;

	int ds_sem = semget(chiavesem, 3, IPC_CREAT|0664);

	if(ds_sem<0) { perror("SEM errore"); exit(1); }


    //SEMAFORI COOPERAZIONE tra i prod e i cons
	semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM_BUFFER);
	semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);

    //SEMAFORI COMPETIZIONE tra i prod e i cons
	semctl(ds_sem, MUTEX_P, SETVAL, 1);
	 printf("posti disponibili prima di decrementare %d\n", p->posti_disponibili);

    for(int i=0;i<NUM_CLIENTI;i++){
        int pid = fork();
		//printf("pid: %d", getpid());
		

		if(pid==0) {

			//figlio produttore

		//	printf("Inizio visualizzatore\n");

			// NOTA: il generatore di numeri pseudo-casuali
			// viene inizializzato in modo diverso per ogni
			// processo (usando il valore del PID e il tempo)
			srand(getpid()*time(NULL));

			produttore(p, ds_sem, getpid());
			printf("error\n");
			exit(1);
		}
		
    }



    
    for(int i=0; i<NUM_CLIENTI; i++) {
		wait(NULL);
		//printf("Figlio produttore terminato\n");
	}

	
        
        shmctl(ds_shm, IPC_RMID, NULL);
        semctl(ds_sem, 0, IPC_RMID);

        return 0;

   
}