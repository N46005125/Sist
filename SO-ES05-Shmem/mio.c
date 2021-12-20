#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <string.h>



int main(){

   	key_t shm_key = ftok(".", 'k');
	int ds_shm = shmget(shm_key, 100, IPC_CREAT | IPC_EXCL | 0664);
    char * p;
     if(ds_shm <0){
         d
     }


}