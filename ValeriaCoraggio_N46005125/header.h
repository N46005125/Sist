#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>



struct monitor {

	int molo;
	int id_nave;

	/* TODO: Aggiungere variabili per la sincronizzazione */
    pthread_mutex_t mutex;

    pthread_cond_t lettori;
    pthread_cond_t scrittori;

    int numscritt;
    int numlettori;
    int lettoriwait;
    int scrittoriwait; 
    
};

void inizializza(struct monitor * m);
void rimuovi (struct monitor * m);
void scrivi_molo(struct monitor * m, int molo);
int leggi_molo(struct monitor * m);



#endif