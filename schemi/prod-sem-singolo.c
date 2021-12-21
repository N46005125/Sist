#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1

void produttore(int * p, int ds_sem) {

	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);


	printf("Il valore prodotto = %d\n", *p);


	Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(int * p, int ds_sem) {


	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);


	printf("Il valore consumato = %d\n", *p);


	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}
