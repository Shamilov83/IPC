#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
 
sem_t sem;              	
 
void* read_books(void* arg)
{
    char* reader = (char*) arg; // идентификатор читателя
    int count = 2;				// счетчик чтения
    while (count > 0)
    {
        sem_wait(&sem); 	 // ожидаем, когда освободиться место
  
        printf("%s enters the library \n", reader);
 
        printf("%s reads \n", reader);
        sleep(1);
  
        printf("%s leaves the library \n", reader);
  
        sem_post(&sem);  	// освобождаем место
  
        count--;
        sleep(1);
    }
    return NULL;
}
 
int main(void) 
{
    sem_init(&sem, 0, 3);       // инициализируем семафор
    pthread_t readers[5];
    pthread_create(&readers[0], NULL, read_books, "Reader 1");
    pthread_create(&readers[1], NULL, read_books, "Reader 2");
    pthread_create(&readers[2], NULL, read_books, "Reader 3");
    pthread_create(&readers[3], NULL, read_books, "Reader 4");
    pthread_create(&readers[4], NULL, read_books, "Reader 5");
 
    sem_destroy(&sem);      // удаляем семафор
     
    pthread_exit(NULL); // ждем завершения всех потоков и завершаем текущий поток
 
    return 0;
}