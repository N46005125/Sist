#include "procedure.h"

#include <unistd.h>
#include <stdio.h>

void Produci(struct ProdCons * pc, int valore) {

	// 1. entro nel monitor
	// 2. controllo che ci siano num_liberi !0 (se no wait_cond)
	// 3. check sul vettore di stato
	// 4. update vettore di stato IN USO, update numero_liberi
	// 4.1 lascio il monitor
	// 5. produco
	// 5.1 entro nel monitor
	// 6. update vett di stato occupato, update numero occupati
	// 7. signal_cond sui cons
	// 8. lascio il monitor

	enter_monitor( &(pc->m) );  //attenzione: usi il riferimento

	printf("Ingresso monitor - produzione\n");

	while( pc->numero_liberi == 0 ) {

		printf("Sospensione - produzione\n");
		wait_condition( &(pc->m), VARCOND_PRODUTTORI );
		printf("Riattivazione - produzione\n");
	}


	int i = 0;
	while( i<DIM && pc->stato[i] != LIBERO ) {
		i++;
	}


	pc->stato[i] = IN_USO;
	pc->numero_liberi--;

	leave_monitor( &(pc->m) );


	// ...operazione lenta...
	sleep(2);

	pc->buffer[i] = valore;

	printf("Produzione - posizione %d, valore %d\n", i, valore);


	enter_monitor( &(pc->m) );

	pc->stato[i] = OCCUPATO;
	pc->numero_occupati++;

	signal_condition( &(pc->m), VARCOND_CONSUMATORI );

	leave_monitor( &(pc->m) );

	printf("Uscita monitor - produzione\n");
}

int Consuma(struct ProdCons * pc) {

	int valore;

	enter_monitor( &(pc->m) );

	printf("Ingresso monitor - consumazione\n");

	while( pc->numero_occupati == 0 ) {

		printf("Sospensione - consumazione\n");
		wait_condition( &(pc->m), VARCOND_CONSUMATORI );
		printf("Riattivazione - consumazione\n");
	}



	int i = 0;
	while( i<DIM && pc->stato[i] != OCCUPATO ) {
		i++;
	}


	pc->stato[i] = IN_USO;
	

	leave_monitor( &(pc->m) );


	// ...operazione lenta...
	sleep(2);

	valore = pc->buffer[i];

	printf("Consumazione - posizione %d, valore %d\n", i, valore);


	enter_monitor( &(pc->m) );

	pc->stato[i] = LIBERO;
	pc->numero_liberi++;

	signal_condition( &(pc->m), VARCOND_PRODUTTORI );

	leave_monitor( &(pc->m) );

	printf("Uscita monitor - consumazione\n");

	return valore;

}

