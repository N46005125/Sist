struct b{
	int buffer[DIM];
	Monitor m;
	int coda;
	int testa;
	int cont;
	int nlettori;
	int nscrittori;
}





void Lettori(){

	enter_monitor(m);
	
	if(cont==0){
		wait_condition(m,LETT);
	}
	
	nlettori++;
	
	if(nscrittori>0){
		wait_condition(m,LETT);
	}
	
	signal_condition(m,LETT);
	
	leave_monitor(m);
	
	//leggi
	//aggiorna coda e cont
	
	enter_monitor(m);
	
	nlettori--;
	
	if(nlettori==0){
		signal_condition(m,SCRITT);	
	
	leave_monitor(m);

}


void Scrittori(){

	enter_monitor(m);
	
	if(cont==DIM){
		wait_condition(m,SCRITT);
	}
		
	
	if(nlettori>0 || nscrittori>0){
		wait_condition(m,SCRITT);
	}
	nscrittori++;
	
	leave_monitor(m);
	
	//leggi
	//aggiorna coda e cont
	
	
	enter_monitor(m);
	nscrittori--;
	
	if(queuecondition(m,SCRITT){
		signal_condition(m,SCRITT);
	}else if(queuecondition(m,LETT){
		signal_condition(m,LETT);
	}
		
	
	
	leave_monitor(m);

}



void Scrittori(){



}
