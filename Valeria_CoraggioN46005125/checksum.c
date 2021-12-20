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

void checksum(int queue_filter_checksum, int queue_checksum_visual){

        int ret, i, j, checksum;
        message mess;
        checksum=0;

        for (j=0; j<NUM_MESSAGES; j++){

                printf("[checksum] Ricevo dal processo Filter...\n");

                ret = msgrcv(queue_filter_checksum,(void*)&mess,sizeof(message)-sizeof(long),MSG_TYPE,IPC_NOWAIT); /* TODO: ricevere il messaggio dal processo filter */
            
                if(ret<0) {
                        if (errno == ENOMSG){
                                printf("Non ci sono più messaggi da ricevere dal processo filter...exit!\n");
                                break;
                        }
                        else{
                                perror("ERROR!!!");
                                exit(-1);
                        }
                }

                /* TODO: Calcolare la checksum e inviarla al visualizzatore  */

                for(int j=0;j<STRING_MAX_DIM;j++){
                        checksum = checksum + (int)mess.stringa[j];
                }
                for(int j=0;j<2;j++){
                        checksum = checksum + mess.array[j];
                }
                mess.var = checksum;
 
                
                printf("[checksum] Invio messaggio di CHECKSUM al Visualizzatore...\n");
                msgsnd(queue_checksum_visual,(void*)&mess,sizeof(message)-sizeof(long),IPC_NOWAIT);
        }
        
        exit(0);
}

