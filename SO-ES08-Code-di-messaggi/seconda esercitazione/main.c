
#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include "header.h"


int main(){

    int queue=msgget(IPC_PRIVATE,IPC_CREAT|0664);

    pid_t pid;
    //GENERATORE
    for(int i=0;i<3;i++){
        pid=fork();
        if (pid==0){
            Generatore(queue);
            exit(1);
        }
    }

    //FILTRO
    pid=fork();
	if (pid==0){
        for(int i=0;i<6;i++){
            sleep(2);
            Filtro(queue);
        }
    exit(1);
    }	

    //CHECKSUM
    pid=fork();
	if (pid==0){
        sleep(3);
        Checksum(queue);
    exit(1);
    }	

    //VISUALIZZATORE
    pid=fork();
	if (pid==0){
        sleep(5);
    Visualizzatore(queue);
    exit(1);
    }		
    
    for(int i=0;i<6;i++)
        wait(NULL);
    


    msgctl(queue,IPC_RMID,0);


    return 0;
}