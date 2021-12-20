#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"

void filtro(int ds_queue_gen_filter, int ds_queue_filter_checksum){

        int ret, i;
        message mess;

        for (i=0; i<NUM_MESSAGES; i++){

                ret = msgrcv(ds_queue_gen_filter,(void*)&mess,sizeof(message)-sizeof(long),MSG_TYPE,0);/* TODO: ricevere il messaggio dai processi generatori consumatori */

                if(ret<0) {
                        perror("msgrcv on ds_queue_gen_filter FALLITA!");
                        exit(-1);
                }

                printf("[filtro] Ricevuto #%d messaggio dal generatore...\n", i);
                //ricerca del carattere 'x'

              


                printf("[filtro] Ricerca carattere 'x' sulla stringa: %s...\n", mess.stringa);

                char* ptr1=strchr(mess.stringa,'x');
                if(ptr1 != NULL){
                        printf("Ho trovato una x nel messaggio . Il messaggio viene ignorato.\n");
                }else{
                        msgsnd(ds_queue_filter_checksum,(void*)&mess,sizeof(message)-sizeof(long),IPC_NOWAIT);
                }
            
                /* TODO: effettuare la ricerca del caratter 'x' e inviare il messaggio al processo checksum nel caso di carattere non trovato */
                
        }
    
        exit(0);
}

