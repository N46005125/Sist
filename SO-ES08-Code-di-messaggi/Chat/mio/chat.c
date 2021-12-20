#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"


int main(int argc, char* argv[]){

    // Controllo gli argomenti passati
	if(argc<2){
		printf("Errore: Fornire come parametri di ingresso 2 caratteri separati da spazio\n");
        exit(1);
	}

    char firstChar = *argv[1];
	char secondChar = *argv[2];

    key_t chiave_s = ftok(".",firstChar);
    key_t chiave_r = ftok(".",secondChar);
    
    int id_queue_s = msgget(chiave_s,IPC_CREAT | 0664);
    if(id_queue_s < 0) {
		perror("Msgget fallita");
		exit(1);
	}

    int id_queue_r = msgget(chiave_r,IPC_CREAT | 0664);
    if(id_queue_r < 0) {
		perror("Msgget fallita");
		exit(1);
	}

    pid_t pid=fork();
    if(pid==0){
        //mittente
        Sender(id_queue_r,id_queue_s);
        exit(1);
    }

    pid=fork();
    if(pid==0){
        //ricevitore
        Receiver(id_queue_r);
        exit(1);
    }

    for(int i=0;i<2;i++){
        wait(NULL);
    }

    msgctl(id_queue_r,IPC_RMID,0);
    msgctl(id_queue_s,IPC_RMID,0);
    return 0;
}