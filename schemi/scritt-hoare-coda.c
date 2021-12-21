#define MUTEXL 0
#define SYNCH 1

struct buffer{

	int buffer[DIM];
	int testa;
	int coda;
	int count;
	int nlettori;
	Monitor m;

}



void Lettura(){

	enter_monitor(&b->m);
		
	if(b->count==0){
		wait_condition(&b->m,LETT);
	}
	
	b->nlettori++;
	
	signal_condition(&b->m,LETT);
	
	leave_monitor(&b->m);
	
	valore=buffer[coda];
	coda=(coda+1)%DIM;
	cont--;
	
	enter_monitor(&b->m);
	b->nlettori--;
	
	if(nlettori==0)
		signal_condition(&b->m,SCRITT);

	leave_monitor(&b->m);

}




void Scrittura(){

	enter_monitor(&b->m);
	
	if(b->cont==DIM || nlettori==0){
		wait_condition(&b->m,SCRITT);
	}

	
	buffer[testa]=valore;
	testa=(testa+1)%DIM;
	connt++;
	
		
	signal_condition(&b->m,LETT);

	leave_monitor(&b->m);

}
