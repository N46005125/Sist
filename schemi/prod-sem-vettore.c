#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1
#define MUTEX_P 2
#define MUTEX_C 3

#define BUFFER_VUOTO 0
#define BUFFER_INUSO 1
#define BUFFER_PIENO 2


struct prodcons {
    int buffer[DIM_BUFFER];
    int stato[DIM_BUFFER];
};


void produttore(struct prodcons * p, int ds_sem) {
    
    int indice = 0;
    
    
    Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
    
    
    Wait_Sem(ds_sem, MUTEX_P);
    
    while(indice <= DIM_BUFFER && p->stato[indice] != BUFFER_VUOTO) {
        indice++;
    }
    
    p->stato[indice] = BUFFER_INUSO;
    
    Signal_Sem(ds_sem, MUTEX_P);
    
    
    sleep(2);
    
   
    
    p->stato[indice] = BUFFER_PIENO;
    
    Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(struct prodcons * p, int ds_sem) {
    
    int indice = 0;
    
    
    Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    
    
    Wait_Sem(ds_sem, MUTEX_C);
    
    while(indice <= DIM_BUFFER && p->stato[indice] != BUFFER_PIENO) {
        indice++;
    }
    
    p->stato[indice] = BUFFER_INUSO;
    
    Signal_Sem(ds_sem, MUTEX_C);
    
    
    sleep(2);
        
    
    p->stato[indice] = BUFFER_VUOTO;
    
    Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}
