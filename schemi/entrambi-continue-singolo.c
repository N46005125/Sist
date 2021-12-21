struct LettScritt {
	int buffer;

	int numero_lettori;
	int numero_scrittori;

	Monitor m;
};

#define VARCOND_LETTORI 0
#define VARCOND_SCRITTORI 1

int Leggi(struct LettScritt * ls) {

	int valore;

	enter_monitor( &(ls->m) );
	while( ls->numero_scrittori > 0 ) {
		wait_condition( &(ls->m), VARCOND_LETTORI )
	}

	ls->numero_lettori++;

	sleep(2);


	enter_monitor( &(ls->m) );

	ls->numero_lettori--;

	if( ls->numero_lettori == 0 ) {

		signal_condition( &(ls->m), VARCOND_SCRITTORI );
	}

	leave_monitor( &(ls->m) );

	return valore;

}


void Scrivi(struct LettScritt * ls, int valore) {

	enter_monitor( &(ls->m) );

	while (ls->numero_lettori > 0 || ls->numero_scrittori > 0) {
		wait_condition( &(ls->m), VARCOND_SCRITTORI );
	}

	ls->numero_scrittori++;
	leave_monitor( &(ls->m) );

	sleep(1);
	ls->buffer = valore;

	enter_monitor( &(ls->m) );

	ls->numero_scrittori--;

	if( queue_condition( &(ls->m), VARCOND_SCRITTORI ) ) {

		signal_condition( &(ls->m), VARCOND_SCRITTORI );

	} else {
		
		signal_all( &(ls->m), VARCOND_LETTORI );
	 }
	

	leave_monitor( &(ls->m) );

}


