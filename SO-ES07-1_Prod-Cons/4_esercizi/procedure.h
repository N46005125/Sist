#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1
#define MUTEX_P 1

#define DIM_BUFFER 80

#define NUM_CLIENTI 50

#define BUFFER_LIBERO 0
#define BUFFER_INAGGIORNAMENTO 1
#define BUFFER_OCCUPATO 2

typedef struct {
    unsigned int id_cliente;
    unsigned int stato; 
} posto;

struct posti {
    posto buffer[DIM_BUFFER];
    int posti_disponibili;
};


void produttore(struct posti *, int, int);
void consumatore(struct posti *, int);
