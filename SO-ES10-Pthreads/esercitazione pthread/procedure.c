#include "header.h"



void inizializza(struct monitor* m){

	m->molo=0;
	m->id_nave=0;

    m->num_lettori=0;
    m->num_scrittori=0;
    m->num_lettori_wait=0;
    m->num_scrittori_wait=0;

    pthread_mutex_init(&m->mutex,NULL);
    pthread_cond_init(&m->ok_lett_cv,NULL);
    pthread_cond_init(&m->ok_scritt_cv,NULL);

    /* TBD: Inizializzare le variabili dell'algoritmo, il mutex, e le variabili condition */

}

void rimuovi (struct monitor* m){
    /* TBD: Disattivare mutex e variabili condition */
   // for(int i=0;i<5;i++){
        pthread_mutex_destroy(&m->mutex);
        pthread_cond_destroy(&m->ok_lett_cv);
        pthread_cond_destroy(&m->ok_scritt_cv);
         
}


void InizioLettura(struct monitor* m){

    pthread_mutex_lock(&m->mutex);
    while (m->num_scrittori>0) {
		m->num_lettori_wait++;
		pthread_cond_wait(&m->ok_lett_cv, &m->mutex);
		m->num_lettori_wait--;
	}
    m->num_lettori++;
    pthread_mutex_unlock(&m->mutex);

}

void FineLettura(struct monitor* m){

    pthread_mutex_lock(&m->mutex);

	m->num_lettori--;

	if(m->num_lettori == 0)
		pthread_cond_signal(&m->ok_scritt_cv);

	pthread_mutex_unlock(&m->mutex);


}


void InizioScrittura(struct  monitor* m){
 
    
    pthread_mutex_lock(&(m->mutex));
    printf("entro in inizio scrittura\n");

	while (m->num_lettori > 0 || m->num_scrittori > 0) {
		m->num_scrittori_wait++;
		pthread_cond_wait(&m->ok_scritt_cv, &m->mutex);
		m->num_scrittori_wait--;
	}

	m->num_scrittori++;


}

void FineScrittura(struct  monitor* m){

    pthread_mutex_lock(&m->mutex);

    printf("entro in fine scrittura");
	m->num_scrittori--;

	if(m->num_scrittori_wait > 0) {

		/* se ci sono scrittori in attesa, si dà loro
		 * la priorità */

		pthread_cond_signal(&m->ok_scritt_cv);

	} else {

		/* risveglia tutti i lettori in attesa */

		pthread_cond_broadcast(&m->ok_lett_cv);
	}

	pthread_mutex_unlock(&m->mutex);

}
//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_molo(struct monitor* m, int molo){
    printf("entro in scrivi molo\n");

    InizioScrittura(m);

    m->molo=molo;



    FineScrittura(m);



    /* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della SCRITTURA
     */
}


//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_molo(struct monitor* m){

    InizioLettura(m);

    int ris= m->molo;
    /* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della LETTURA
     */
    FineLettura(m);

    return ris;
}


