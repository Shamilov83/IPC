#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>

#define SEMAPHORE_NAME "/my_named_semaphore"

int main(int argc, char ** argv) {
    sem_t *sem;

    if ( argc == 2 ) {
        printf("Dropping semaphore...\n");
        if ( (sem = sem_open(SEMAPHORE_NAME, 0)) == SEM_FAILED )    //инициализирует и открывает именованный семафор 
        {  
            perror("sem_open");
            return 1;
        }
        sem_post(sem);                                              //разблокирование семафора
        perror("sem_post");
        printf("Semaphore dropped.\n"); 
        return 0;
    }

    if ( (sem = sem_open(SEMAPHORE_NAME, O_CREAT, 0777, 0)) == SEM_FAILED ) {
        perror("sem_open");
        return 1;
    }

    printf("Semaphore is taken.\n Waiting for it to be dropped.\n");
    printf("%s %d %s","Semaphore sem = ", sem,"\n");

    if (sem_wait(sem) < 0 )
        perror("sem_wait");

    if ( sem_close(sem) < 0 )
        perror("sem_close");

    return 0;
}