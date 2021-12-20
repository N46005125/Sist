#include "header.h"

/*Funzione che, per 10 volte,incrementa di uno la posizione molo, ovvero la posizione della nave, e tramite scrivi_molo effettua la modifica poi attende 3 secondi*/
void * gestoreMolo (void * p){
	struct monitor* m = (struct monitor*) p;
	int i,s;
	s=m->molo;
	for(i=0; i<10; i++){
		s=s+1;
		scrivi_molo(m,s,i);
		printf("[C: Posizione della nave %d modificata. La nuova posizione Ã¨: %d]\n",m->id_nave,s);
		sleep(3);
	}
	pthread_exit(NULL);
}

//Funzione che controlla la posizione di un nave per tre volte
void * Viaggiatori (void * p){
	struct monitor* m = (struct monitor*) p;
	int i;
	int ris;
	for(i=0;i<3;i++){
		sleep(rand()%6+1);
		ris=leggi_molo(m);
		printf("[V]~La nave n.ro %d Ã¨ nel molo %d\n", m->id_nave, ris);
	}
	pthread_exit(NULL);
}

int main() {
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	srand(time(NULL));

	struct monitor* m[5];//l'array di monitor per gestire 5 navi

	pthread_t gestore_molo[5];//5 gestori molo
	pthread_t viagg[10];//10 viaggiatori	
	
	int i;

    /* TBD: Allocare 5 istanze di monitor, e attivarle con inizializza() */

    for(int i=0;i<5;i++){
        m[i] = malloc(sizeof(struct monitor));
    }
    
    for(int i=0;i<5;i++){
        inizializza(m[i]);
    }


	//assegno un id ad ogni nave
	m[0]->id_nave=1;
	m[1]->id_nave=2;
	m[2]->id_nave=3;
	m[3]->id_nave=4;
    m[4]->id_nave=5;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


    int k;
     for (k=0;k<NUM_GESTORI; k++) {

        printf("Sono il thread Gestore molo (%d)\n",k);
	    pthread_create(&gestore_molo[k], &attr, gestoreMolo, (void *) m);
	    
	}


    for (k=0;k<NUM_VIAGGIATORI; k++) {
        printf("Sono il thread Viaggiatore (%d)\n",k);
        srand(getpid()*time(NULL));
        int temp=rand()%5;
	    pthread_create(&viagg[k], &attr, Viaggiatori, (void *) m);
    }

    
    for (k=0; k<NUM_GESTORI;k++){
       pthread_join(gestore_molo[k],NULL);
       printf ("Thread n.ro %d terminato\n ",k);
     }
    
    for (k=0; k<NUM_VIAGGIATORI;k++){
       pthread_join(viagg[k],NULL);
       printf ("Thread n.ro %d terminato\n ",k);
     }




    /* TBD: Avviare 5 thread, facendogli eseguire la funzione gestoreMolo(),
     *     e passando ad ognuno una istanza di monitor diversa m[i]
     */
    
    
    /* TBD: Avviare 10 thread, facendogli eseguire la funzione Viaggiatori(),
     *      e passando ad ognuno una istanza di monitor diversa, da scegliere
     *      a caso con "rand() % 5"
     */
    
    
    /* TBD: Effettuare la join con i thread "gestoreMolo" */
    
    /* TBD: Effettuare la join con i thread "Viaggiatori" */
    
    /* TBD: Disattivazione delle 5 istanze di monitor con rimuovi() */

    /* TBD: Deallocazione delle 5 istanze di monitor con free() */
    pthread_attr_destroy(&attr);
   
    
    for(int i=0;i<5;i++)
        rimuovi(m[i]);
        free(m[i]);

    pthread_exit(0);
	
    
	return 0;
}	


