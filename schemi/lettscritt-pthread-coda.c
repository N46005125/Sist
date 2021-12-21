struct{
	int buffer[DIM]
	int coda;
	int cont;
	int testa;
	pthread_mutex_t mutex;
	pthread_cond_t lett;
	pthread_cond_t scritt;
	int lettori;
	int scrittori;
	int scrittoriwait;
	int lettoriwait;
}


void Lettura(){

	pthread_mutex_lock(m);
	
	while(scrittori>0 || cont==0){
		lettwait++;
		pthread_cond_wait(LETT,m);
		letttwait--;
	}
	
	lettori++;	
	pthread_mutex_unlock(m);
	//LEGGI
	pthread_mutex_lock(m);
	
	lettori--;
	if(lettori=0){
		signal(SCRITT);
	}	
	
	pthread_mutex_unlock(m);
	
	
	
}



void Scrittura(){

	pthread_mutex_lock(m);
	
	while(scrittori>0 || cont==0 || lettori>0){
		scrittwait++;
		pthread_cond_wait(scritt,m);
		scrittwait--;
	}
	
	scrittori++;	
	pthread_mutex_unlock(m);
	//scrivi
	pthread_mutex_lock(m);
	
	scrittori--;
	if(scrittoriwait>0)
		signal(SCRITT);
	}else if(lettoriwait>0){
		broadcast(lettori);
	}
	
	pthread_mutex_unlock(m);

}

