#define PROD 0
#define CONS 1

struct{
	Monitor m;
	int buffer[DIM];
	int stato[DIM];
	int nliberi;
	int noccupati;
}



void Prod(){

	int indice=0;
	enter_monitor(m);
	
	
	if(nliberi==0){
		wait_Condition(PROD);
	}
	
	while(indice<DIM && stato[indice]!=LIBERO){
	indice++;
	}
	
	nliberi--;
	stato[indice]=INUSO;
	
	
	leave_monitor(m);
	
	//SCRIVI
	
	
	enter_monitor(m);
	
	
	noccupati--;
	stato[indice]=OCCUPATO;
	signal(CONS);
	
	
	
	leave_monitor(m);

}




void Cons(){

	int indice=0;
	enter_monitor(m);
	
	
	if(noccupati==0){
		wait_Condition(CONS);
	}
	
	while(indice<DIM && stato[indice]!=OCCUPATO){
	indice++;
	}
	
	noccupati--;
	stato[indice]=INUSO;
	
	
	leave_monitor(m);
	
	//SCRIVI
	
	
	enter_monitor(m);
	
	
	nliberi--;
	stato[indice]=libero;
	signal(PROD);
	
	
	
	leave_monitor(m);




}
