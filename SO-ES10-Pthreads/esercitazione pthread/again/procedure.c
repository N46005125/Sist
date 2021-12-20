#include "header.h"



void inizializza(struct monitor* m){

	m->molo=0;
	m->id_nave=0;

    /* TBD: Inizializzare le variabili dell'algoritmo, il mutex, e le variabili condition */
    pthread_mutex_init(&m->mutex,NULL);
    pthread_cond_init(&m->scrittori,NULL);
    pthread_cond_init(&m->lettori,NULL);
    m->numlettori=0;
    m->numscritt=0;
    m->lettoriwait=0;
    m->scrittoriwait=0;

}

void rimuovi (struct monitor* m){
    /* TBD: Disattivare mutex e variabili condition */
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->scrittori);
    pthread_cond_destroy(&m->lettori);
}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_molo(struct monitor* m, int molo){

    pthread_mutex_lock(&m->mutex);

    while(m->numlettori>0 || m->numscritt>0){
        (m->scrittoriwait)++;
        pthread_cond_wait(&m->scrittori,&m->mutex);
        (m->scrittoriwait)--;
    }

    (m->numscritt)++;

    pthread_mutex_unlock(&m->mutex);

    //scrittura
    m->molo=molo;
    //printf("Ho aggiornato il molo a %d\n",m->molo);

    sleep(2);

    pthread_mutex_lock(&m->mutex);

    (m->numscritt)--;

    if(m->scrittoriwait>0){
        pthread_cond_signal(&m->scrittori);
    }else{
        pthread_cond_broadcast(&m->lettori);
    }


    pthread_mutex_unlock(&m->mutex);

}


//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_molo(struct monitor* m){

    /* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della LETTURA
     */

    pthread_mutex_lock(&m->mutex);

    while(m->numscritt>0){
        (m->lettoriwait)++;
        pthread_cond_wait(&m->lettori,&m->mutex);
        (m->lettoriwait)--;
    }

    (m->numlettori)++;

    pthread_mutex_unlock(&m->mutex);

    //legge
    int ret = m->molo;
    //printf("Legge molo %d\n",m->molo);
    sleep(2);

    pthread_mutex_lock(&m->mutex);

    (m->numlettori)--;

    if(m->numlettori==0)
        pthread_cond_signal(&m->scrittori);

    pthread_mutex_unlock(&m->mutex);
    return ret;

}
