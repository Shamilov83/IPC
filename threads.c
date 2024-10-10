#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct str{
    int pnum;
    int val;
}pr;

int value = 0;                  // общий ресурс
unsigned long flags = 0;

pthread_mutex_t m;              // мьютекс

void* do_work(void* arg);
//int child_func(void* arg);
int do_work2(void* arg);


int main (void){

    void* (*ptr_fn) (void *);

    ptr_fn = do_work;

    pr param1;
    pr param2;
    pr param3;

    pthread_t tid1;
    pthread_t tid2;

    param1.pnum = 1;
    param2.pnum = 2;
    param3.pnum = 3;

    pthread_mutex_init(&m, NULL);               //  инициализация мьютекса

    const int STACK_SIZE = 65536;
    char* stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("malloc");
        exit(1);
    }


    pthread_create(&tid1, NULL, &do_work, &param1);
    pthread_create(&tid2, NULL, &do_work, &param2);

    flags |= CLONE_VM;

    if (clone(do_work2, stack + STACK_SIZE, flags | SIGCHLD, &param3) == -1)
    {
        perror("clone");
        printf("Error_clone\n");
        exit(1);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&m);                  // удаление мьютекса

    return 0;
}

int do_work2(void* arg)
{
    do_work(arg);
    return 0;
}

void* do_work(void* arg)
{
    //int id = *(int*)thread_id;
   pr param = *(pr*) arg; 

    pthread_mutex_lock( &m );                   // поток блокирует мьютекс
    value = 1;  
                                                // начало работы с обшим ресурсом
    for (int n = 0; n < 5; n++) 
    {
        printf("Thread %d: %d\n", param.pnum, value );
        value += 1;
        //sleep(1);
    }
    pthread_mutex_unlock( &m );                 // поток освобождает мьютекс
    return NULL;
}
/*
int child_func(void* arg) {
    char* buffer = (char*)arg;
    strcpy(buffer, "Привет от дочернего потока");
    printf("Буфер в дочернем потоке = \"%s\"\n", buffer);
    return 0;
}
*/