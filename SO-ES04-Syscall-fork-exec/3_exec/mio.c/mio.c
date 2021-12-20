/*L’interprete dei comandi (*shell*) implementa le seguenti funzionalità:

- Legge la linea di comando;
- Estrae la prima parola, assumendo che sia il nome di un programma;
- Cerca il programma in questione e lo lancia in esecuzione (mediante fork ed exec), passandogli come argomenti le altre parole presenti sulla linea di comando;
- Attende che il figlio termini, prima di presentare nuovamente il prompt d’utente.

Utilizzare le system call viste fin'ora per implementare una Unix shell di base.

*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char * argv[]){

    int pid;
    pid=fork();
    if( pid == -1 ) {
                perror("fork fallita");
                exit(1);
    }

    if(pid==0){
        printf("Sono il processo figlio, con PID %d\n", getpid());
        printf("Command line passata al main():\n");
        printf("argv[0]: %s\n", argv[0]);
        printf("argv[1]: %s\n", argv[1]);
        printf("argv[2]: %s\n", argv[2]);

        const char *b = argv[1];

        const char *a[argc-1];
        for(int i=2;i<argc;i++){
            a[i-2]=argv[i];
        }
        execvp(*b,*a);
        perror("Se arrivo in questo punto, qualcosa è andato storto...\n");
        exit(1);

    }else {

                printf("Sono il processo padre, con PID %d\n", getpid());

                wait(NULL);

                printf("Copia effettuata con successo!\n");
                printf("Il processo padre termina\n");

                exit(0);
    }

    return 0;



}

