#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int readcount = 0;    // Number of current readers
sem_t rsem;           // rsem: Semaphore for updating readCount in critical section
sem_t wsem;           // wsem: Semaphore to check if file avilable for write
pthread_t r[5], w[2]; // Reader and Writer threads

// Function for reader thread
void *reader(void *i)
{
    // Increment readCount and wait on wsem semaphore if file unavailable for read
    sem_wait(&rsem);
    readcount++;
    if (readcount == 1)
        sem_wait(&wsem);
    printf("\nReader-%d  is reading", *(int *)i);
    sem_post(&rsem);

    // Reading
    for (int i = 0; i < 10000; i++)
        ;
    // Decrement readCount and signal wsem semaphore if first reader
    sem_wait(&rsem);
    printf("\nReader-%d  completes reading", *(int *)i);
    readcount--;
    if (readcount == 0)
        sem_post(&wsem);
    sem_post(&rsem);
}

void *writer(void *i)
{
    // Wait for wsem semaphore
    sem_wait(&wsem);
    printf("\nWriter-%d  is writing", *(int *)i);
    // Writing
    for (int i = 0; i < 10000; i++)
        ;
    printf("\nWriter-%d  completes writing", *(int *)i);
    sem_post(&wsem);
}

int main()
{
    // Initialising semaphores
    sem_init(&wsem, 0, 1);
    sem_init(&rsem, 0, 1);

    // Creating reader and writer threads in a random sequence
    pthread_create(&r[0], NULL, reader, (void *)0);
    pthread_create(&w[0], NULL, writer, (void *)0);
    pthread_create(&r[1], NULL, reader, (void *)1);
    pthread_create(&r[2], NULL, reader, (void *)2);
    pthread_create(&w[1], NULL, reader, (void *)1);
    pthread_create(&r[3], NULL, writer, (void *)3);
    pthread_create(&r[4], NULL, reader, (void *)4);

    // Waiting for all threads
    pthread_join(r[0], NULL);
    pthread_join(w[0], NULL);
    pthread_join(r[1], NULL);
    pthread_join(r[2], NULL);
    pthread_join(w[1], NULL);
    pthread_join(r[3], NULL);
    pthread_join(r[4], NULL);

    return (0);
}