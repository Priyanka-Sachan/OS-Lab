#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <string.h>

pthread_mutex_t lock;
pthread_cond_t cond;
FILE *file;
int counter = 1;
int charCount = 0;

// prime=odd
int isPrime(int num)
{
    if (num <= 1)
        return 0;
    for (int i = 2; i <= num / 2; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

void *printPrime(void *args)
{
    int *forPrime = (int *)args;
    while (counter <= 100)
    {
        pthread_mutex_lock(&lock);
        while ((*forPrime == 1 && isPrime(counter) == 0) || (*forPrime == 0 && isPrime(counter) == 1))
            pthread_cond_wait(&cond, &lock);
        if (counter <= 100)
        {
            if (*forPrime)
            {
                printf("%d is a prime\n", counter);
                fprintf(file, "%d is a prime\n", counter);
            }
            else
            {
                printf("%d is not a prime\n", counter);
                fprintf(file, "%d is not a prime\n", counter);
            }
        }
        counter++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
}

void *countCharcters()
{
    while (counter <= 100)
        pthread_cond_wait(&cond, &lock);
    char line[1000];
    while (fgets(line, 1000, file) != NULL)
    {
        charCount += strlen(line);
        printf("%ld\n", strlen(line));
    }
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    file = fopen("demo.txt", "w");
    int notForPrime = 0, forPrime = 1;
    if (file == NULL)
    {
        printf("Error in opening the file.");
        exit(1);
    }
    int rc1, rc2, rc3;
    pthread_t thread1, thread2, thread3;

    /* Create independent threads each of which will execute functionC */
    // Except prime
    if ((rc1 = pthread_create(&thread1, NULL, &printPrime, (void *)&notForPrime)))
    {
        printf("Thread creation failed: %d\n", rc1);
    }
    // Prime
    if ((rc2 = pthread_create(&thread2, NULL, &printPrime, (void *)&forPrime)))
    {
        printf("Thread creation failed: %d\n", rc2);
    }
    // Count number of characters in each line
    if ((rc3 = pthread_create(&thread3, NULL, &countCharcters, NULL)))
    {
        printf("Thread creation failed: %d\n", rc3);
    }

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    fclose(file);
    exit(0);
}