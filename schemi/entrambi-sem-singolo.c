#define MUTEX_L
#define MUTEX_S
#define SYNCH
#define MUTEX

struct{
	int buffer;
	nlettori;
	nscrittori;
}


void Lettura(){

	
	waitsem(MUTEX_L);
	nlettori++;
	if(nlettori==1){
		wait(synch);
	}
	signalsem(mutex_l);
	
	
	
	//leggi

	
	waitsem(MUTEX_L);
	nlettori--;
	if(nlettori==0){
		signal(synch);
	}
	signalsem(mutex_l);
	
	

}



void Scrittura(){

	
	waitsem(mutex_s);

	nscrittori++;
	if(nscrittori==1)
		wait(synch)
	signalsem(mutex_s);
	
	wait(mutex);
	//scrivi
	signal(mutex);
	waitsem(mutex_s);
	nscrittori--;
	if(nscrittori==0)
		signal(synch);
	signalsem(mutex_s);


}
