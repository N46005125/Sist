struct ProdCons {

	pthread_mutex_t mutex;
	pthread_cond_t ok_prod_cv;
	pthread_cond_t ok_cons_cv;

	int ok_produzione;
	int ok_consumo;

	msg mess;
};


void Produci(struct ProdCons * pc, msg m) {

		InizioProduzione(pc);

		FineProduzione(pc);


}

msg Consuma(struct ProdCons * pc) {

		msg m;

		InizioConsumo(pc);

		FineConsumo(pc);


		return m;
}


void InizioConsumo(struct ProdCons * pc){

	pthread_mutex_lock(&pc->mutex);

	while (pc->ok_consumo==0)
		pthread_cond_wait(&pc->ok_cons_cv, &pc->mutex);
}

void FineConsumo(struct ProdCons * pc){

        pc->ok_produzione = 1;
	pc->ok_consumo = 0;

	pthread_cond_signal(&pc->ok_prod_cv);

	pthread_mutex_unlock(&pc->mutex);
}


void InizioProduzione(struct ProdCons * pc){

	pthread_mutex_lock(&pc->mutex);

	while (pc->ok_produzione==0)
		pthread_cond_wait(&pc->ok_prod_cv, &pc->mutex);

}

void FineProduzione (struct ProdCons * pc){

	pc->ok_consumo = 1;
	pc->ok_produzione = 0;

	pthread_cond_signal(&pc->ok_cons_cv);

	pthread_mutex_unlock(&pc->mutex);
}



