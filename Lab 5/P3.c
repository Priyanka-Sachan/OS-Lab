#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <string.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int locked = 0;
int l;                                                   // litres of petrol in tanker;
int m;                                                   // number of vending machines (maximum 10)
int n[10], current[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // number of people in queues & current position of each vending machine
int p[10][10];                                           // petrol required by each person

void *dispensePetrolVM(void *args)
{
    int *id = (int *)args;
    while (current[*id] < n[*id])
    {
        while (locked == 1)
            pthread_cond_wait(&cond, &lock);
        pthread_mutex_lock(&lock);
        locked = 1;
        if (l >= p[*id][current[*id]])
        {
            l -= p[*id][current[*id]];
            printf("%d L of petrol dispensed by vending machine %d...Remaining %d\n", p[*id][current[*id]], (*id) + 1, l);
        }
        current[*id]++;
        locked = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_t threads[10];
    int threadId[10];
    printf("Number of L of petrol in petrol tanker:");
    scanf("%d", &l);
    printf("Number of vending machines (max 10):");
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        printf("Number in people in queue for vending machine %d :", i + 1);
        scanf("%d", &n[i]);
        printf("Petrol required for people in queue for vending machine %d :", i + 1);
        for (int j = 0; j < n[i]; j++)
            scanf("%d", &p[i][j]);
    }
    for (int i = 0; i < m; i++)
        threadId[i] = pthread_create(&threads[i], NULL, &dispensePetrolVM, (void *)&i);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    exit(0);
}