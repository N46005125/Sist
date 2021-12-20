#ifndef H_H
#define H_H

#define NUM_CLIENTI 16
#define DIM_VETTORE 20

#define LIBERO 0
#define OCCUPATO 1
#define IN_AGGIORNAMENTO 2

#define MUTEX_P 0


typedef struct{
    unsigned int id_cliente;
    unsigned int stato;
}posto;

typedef struct{
    int disponibilita;
    posto pos[15];
}Posti;


void Cliente(Posti*,int,int,int);
void Visualizzatore(Posti*);



#endif