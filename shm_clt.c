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

if((semid = semget(SEM_ID,1,0)) < 0)
sys_err("can't get semafore");
else
printf("get semafore OK\n");

if((shmid = shmget(SHM_ID, sizeof(message_t),0)) < 0)
sys_err("can't get shared memory segment");
else 
printf("get shared memory segment OK\n");

if((msg_p = (message_t*)shmat(shmid,0,0)) == NULL)
sys_err("shared memmory attach error");
else
printf("shared memmory attach OK\n");


while(1){
	scanf("%s",s);
	while(semctl(semid,0,GETVAL,0) || msg_p -> type != MSG_TYPE_EMPTY);
	
	semctl(semid,0,GETVAL,0);
	
	if(strlen(s) != 1){
		msg_p -> type = MSG_TYPE_STRING;
		strncpy(msg_p -> string, s, MAX_STRING);
	} else {
		msg_p -> type = MSG_TYPE_FINISH;
	}	
	
	semctl(semid, 0, SETVAL, 0);
	if(strlen(s) == 1)
	break;
	}
	
	shmdt (msg_p);
	exit(0);
}
