struct{
	int testa;
	int coda;
	int cont;
	int buffer[DIM]
	Monitor m;
}


void produci(){

	enter_monitor(m);
	
	if(cont==DIM){
		wait_condition(prod);
	}
	
	aggiorna testa
	
	signal(cons)
	

	leave_monitor(m);

}


void consuma(){

	enter_monitor(m);
	
	if(cont==0){
		wait_condition(cons);
	}
	
	aggiorna coda
	
	signal(prod)
	

	leave_monitor(m);

}
