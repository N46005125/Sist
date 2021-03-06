#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define NUM_GESTORI 5
#define NUM_VIAGGIATORI 10

struct monitor{

	int molo;
	int id_nave;

    pthread_mutex_t mutex;

    pthread_cond_t ok_lett_cv;
	pthread_cond_t ok_scritt_cv;

    int num_scrittori;
    int num_lettori;
    int num_scrittori_wait;
    int num_lettori_wait;

	/* TBD: Aggiungere variabili per la sincronizzazione */
    
};

void inizializza(struct monitor * m);
void rimuovi (struct monitor * m);
void scrivi_molo(struct monitor * m, int molo,int i);
int leggi_molo(struct monitor * m);



#endif
