#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void Sender(int id_queue_r,int id_queue_s){
    Messaggio m;
    int ret;
    
    while(1){
        printf("Inserisci il messaggio da inviare\n");
        scanf("%s", m.testo);

        m.type=TYPE;

        if(strcmp(m.testo,"exit")==0){
            ret=msgsnd(id_queue_r,&m,sizeof(Messaggio)-sizeof(long),0);
            if(ret<0){
                printf("Msgsnd fallita"),
                exit(1);
            }

            printf("(Sender) Inviato: %s\n",m.testo);
            exit(1);
        }else{
            ret=msgsnd(id_queue_s,&m,sizeof(Messaggio)-sizeof(long),0);
            if(ret<0){
                printf("Msgsnd fallita"),
                exit(1);
            }

            printf("(Sender) Inviato: %s\n", m.testo);
        }
    }
}

void Receiver(int id_queue_r){
    Messaggio m;
    int ret;

    while(1){
        ret= msgrcv(id_queue_r,&m,sizeof(Messaggio)-sizeof(long),TYPE,0);

        if(ret<0){
            perror("Msgrcv fallita");
			exit(1);
        }
        printf("[RECEIVER] ricevuto: %s\n",m.testo);

        if(strcmp(m.testo,"exit")==0)
			exit(1);
    }
}