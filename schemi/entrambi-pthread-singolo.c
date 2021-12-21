
struct LettScritt {

	pthread_mutex_t mutex;
	pthread_cond_t ok_lett_cv;
	pthread_cond_t ok_scritt_cv;
	int num_lettori;	
	int num_scrittori;
	int num_lettori_wait;	
	int num_scrittori_wait;	
	msg mess;
};



msg Leggi(struct LettScritt * ls) {

		msg m;

		InizioLettura(ls);
		FineLettura(ls);
		return m;
}

void Scrivi(struct LettScritt * ls, msg m) {

		InizioScrittura(ls);
		FineScrittura(ls);
}



void InizioLettura(struct LettScritt * ls){
	pthread_mutex_lock(&ls->mutex);

	while (ls->num_scrittori>0) {
		ls->num_lettori_wait++;
		pthread_cond_wait(&ls->ok_lett_cv, &ls->mutex);
		ls->num_lettori_wait--;
	}

	ls->num_lettori++;

	pthread_mutex_unlock(&ls->mutex);
}

void FineLettura(struct LettScritt * ls){

	pthread_mutex_lock(&ls->mutex);

	ls->num_lettori--;

	if(ls->num_lettori == 0)
		pthread_cond_signal(&ls->ok_scritt_cv);

	pthread_mutex_unlock(&ls->mutex);
}


void InizioScrittura(struct LettScritt * ls){

	pthread_mutex_lock(&ls->mutex);

	while (ls->num_lettori > 0 || ls->num_scrittori > 0) {
		ls->num_scrittori_wait++;
		pthread_cond_wait(&ls->ok_scritt_cv, &ls->mutex);
		ls->num_scrittori_wait--;
	}

	ls->num_scrittori++;

	pthread_mutex_unlock(&ls->mutex);
}

void FineScrittura (struct LettScritt * ls){

	pthread_mutex_lock(&ls->mutex);

	ls->num_scrittori--;

	if(ls->num_scrittori_wait > 0) {
		pthread_cond_signal(&ls->ok_scritt_cv);

	} else {

		pthread_cond_broadcast(&ls->ok_lett_cv);
	}

	pthread_mutex_unlock(&ls->mutex);
}


