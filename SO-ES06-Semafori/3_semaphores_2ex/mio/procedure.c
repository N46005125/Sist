#include "header.h"
#include "semafori.h"

#include <sys/wait.h>
#include <limits.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

void Scrivi(Buffer* buf,int minimo,int id_sem){

    Wait_Sem(id_sem,0);
    if(minimo<buf->val){
        buf->val=minimo;
    }
    
    Signal_Sem(id_sem,0);   
    exit(1);

}

void Figlio(Buffer* buf,int id_sem,int* v, int elemento_iniziale,int elemento_finale){
    printf("Inzio\n");

     for(int i=0;i<DIM;i++){
        printf("%d ",v[i]);        
    }
    printf("\n");
    
    printf("Elemento iniziale e finale %d %d sono %d %d\n", elemento_iniziale,elemento_finale, v[elemento_iniziale],v[elemento_finale-1]);
    int minimo = INT_MAX;
    for (int i = elemento_iniziale; i < elemento_finale; i++){
        if (v[i] < minimo){
            minimo = v[i];
        }
    }
    printf("Il minimo è: %d\n",minimo);
    printf("Fine\n");
    Scrivi(buf,minimo,id_sem);
      
    
}

