#define MESSAGGIO_DISP
#define SPAZIO_DISPONIBILE
#define MUTEX_P
#define MUTEX_C



struct{
	int testa;
	int coda;
	int buffer[DIM];

}



void Prod(){
	
	wait_sem(spazio_disponibile)
	wait_sem(MUTEX_P)
	
	//PRODUCI E AGGIORNA
	
	signal_sem(MUTEX_P)
	signalsem(messaggio_disponibile);


}


void cons(){

	wait_sem(messaggio_disponibile)
	wait_sem(MUTEX_c);
	
	
	//conuma E AGGIORNA
	
	signal_sem(MUTEX_c);
	signalsem(spazio);



}
