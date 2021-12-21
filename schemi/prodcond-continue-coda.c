#define PROD 0
#define CONS 1

struct buffer{
	int coda;
	int testa;
	int cont;
	
	int buffer[dim];
	Monitor m;


}



void produci(){
	
	enter_monitor(&b->m);

	while(b->cont==dim){
		wait_condition(m,PROD);
	}

	buffer[testa]=valore;
	testa=(testa+1)%DIM;
	cont++;
	
	signal_condition(m,CONS);
	
	leave_monitor(&b->m);

}



void consuma(){
	
	enter_monitor(&b->m);

	while(b->cont==dim){
		wait_condition(m,CONS);
	}

	valore=buffer[coda];
	coda=(coda+1)%DIM;
	cont++;
	
	signal_condition(m,PROD);
	
	leave_monitor(&b->m);

}
