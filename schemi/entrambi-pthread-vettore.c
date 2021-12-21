#define LIBERO 0
#define OCCUPATO 1
#define INUSO 2

struct b{

	int buffer[DIM];
	int stato[DIM];
	pthread_mutex_t mutex;
	pthread_cond_t lett_cv;
	pthread_cond_t scritt_cv;
	int nlettori;
	int nscrittori;
	int nlettoriwait;
	int nscrittoriwait;

};

void Lettura(){
	
	int indice=0;
	pthread_mutex_lock(&m->mutex);
	
	while(nscrittori>0){
		lettoriwait++;
		pthread_wait_condition(lett_cv,mutex);
		lettoriwait--;
	}
	
	while(indice<DIM && stato[indice]!=OCCUPATO){
		indice++;
	}
	
	nlettori++;
	stato[indice]=INUSO;	
	
	pthread_mutex_unlock(&m->mutex);
	
	valore=buffer[indice];
	
	
	pthread_mutex_lock(&m->mutex);
	
	nlettori--;
	stato[indice]=LIBERO;
	if(nlettori==0)	
		pthread_signal_condition(scritt_cv,mutex);
		
	pthread_mutex_unlock(&m->mutex);


}


void Scrittura(){

	int indice=0;
	pthread_mutex_lock(&m->mutex);
	
	while(nscrittori>0 || nlettori>0){
		scrittoriwait++;
		pthread_wait_condition(scritt_cv,mutex);
		scrittoriwait--;
	}
	
	while(indice<DIM && stato[indice]!=LIBERO){
		indice++;
	}
	
	nscrittori++;
	stato[indice]=INUSO;	
	
	pthread_mutex_unlock(&m->mutex);
	
	buffer[indice]=valore;
	
	
	pthread_mutex_lock(&m->mutex);
	
	nscrittori--;
	stato[indice]=OCCUPATO;
	if(scrittori_wait>0){
		pthread_signal_condition(scritt_cv,mutex);
	}else if(lettoriwait>0){
		pthread_broadcast_condition(lettori_cv,mutex);
	}
	
	pthread_mutex_unlock(&m->mutex);



}
