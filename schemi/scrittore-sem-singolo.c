
#define MUTEXL 0
#define SYNCH 1


typedef long  msg;

typedef struct {

        int numlettori;
        msg messaggio;
    
} Buffer;


void InizioLettura(int sem, Buffer* buf){
    
    Wait_Sem(sem, MUTEXL); 
    buf->numlettori++
    
    if (buf->numlettori == 1) 
        Wait_Sem(sem, SYNCH);
    
    Signal_Sem(sem, MUTEXL);
}

void FineLettura(int sem, Buffer* buf){
    
    Wait_Sem(sem, MUTEXL); 
    buf->numlettori--;
    
    if (buf->numlettori == 0) 
        Signal_Sem(sem, SYNCH);
    
    Signal_Sem(sem, MUTEXL); 
}


void InizioScrittura(int sem){
	Wait_Sem(sem, SYNCH);
}


void FineScrittura (int sem){
	Signal_Sem(sem, SYNCH);
}


void Scrittore(int sem, Buffer* buf) {

        InizioScrittura(sem);

        sleep(1);

        FineScrittura(sem);
}


void Lettore (int sem, Buffer* buf) {

        InizioLettura(sem, buf);

        sleep(1); 

        FineLettura(sem, buf);
}

