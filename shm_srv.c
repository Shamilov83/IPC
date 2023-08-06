#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"


void sys_err(char *msg){
puts(msg);
exit(1);
}


int main(){

int semid;
int shmid;

message_t *msg_p;

char s[MAX_STRING];

if((semid = semget(SEM_ID, 1, PERMS | IPC_CREAT)) < 0)
sys_err("can,t creat semafore");
else
printf("get semafore OK\n");

if((shmid = shmget(SHM_ID, sizeof(message_t), PERMS | IPC_CREAT)) < 0)
sys_err("can,t create shared system memory segment");
else 
printf("get shared memory segment OK\n");

if((msg_p = (message_t*)shmat(shmid,0,0)) == NULL)
sys_err("shared memmory attach error");
else
printf("shared memmory attach OK\n");

semctl(semid, 0, SETVAL, 0);

msg_p -> type = MSG_TYPE_EMPTY;

while(1){
	if(msg_p -> type != MSG_TYPE_EMPTY){
	
	
	if(semid, 0, SETVAL, 0) continue;
	
	semctl(semid, 0, SETVAL, 1);
	
	if(msg_p -> type == MSG_TYPE_STRING)
	printf("%s\n", msg_p -> string);
	
	if(msg_p -> type == MSG_TYPE_FINISH)
	break;
	
	msg_p -> type = MSG_TYPE_EMPTY;
	semctl(semid, 0, SETVAL, 0);
	}
}

if(semctl(semid,0,IPC_RMID,(struct semid_ds*) 0) < 0)
sys_err("semafore remove error");

shmdt(msg_p);
if(shmctl(shmid, IPC_RMID, (struct shmid_ds*) 0) < 0)
sys_err("shared memmory remove error");

exit(0);
}	
	
	
	

