#define PROD 0
#define CONS 1

typedef struct{
	Monitor m;
	int buffer;
	int libero;
	int occupato;
}b:



void Produttore(){

	enter_monitor(m);
	if(occupato=1)
	wait_condition(m,PROD);
	
	//SCRIVI
	libero=0;
	occupato=1;
	
	
	signal_condition(m,CONS);
	leave_monitor(m);

}



void Consumatore(){

	enter_monitor(m);
	if(libero=1)
	wait_condition(m,CONS);
	
	//CONSUMA
	libero=1;
	occupato=0;
	
	
	signal_condition(m,PROD);
	leave_monitor(m);

}
