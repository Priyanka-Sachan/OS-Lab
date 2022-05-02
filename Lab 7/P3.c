#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define slice_in_pizza 5;
#define total_students 8;

int slices = 0;                          // Number of curent pizza slices
int first = 1;                           // To check which student is first to notice empty pizza
pthread_mutex_t entry;                   // Mutex for critical section
pthread_cond_t orderPizza, deliverPizza; // Condition for ordering or delivering pizza

// Function for Student Thread
void *student(void *i)
{
    // Count for maximum pizza by one student used to avaoid infinite loop
    int count = 3;
    printf("\nStudent-%d - up and running", *(int *)i);
    while (count--)
    {
        pthread_mutex_lock(&entry);
        // If pizza available, eat
        if (slices > 0)
        {
            slices--;
            printf("\nStudent-%d ate a slice of pizza.", *(int *)i);
        }
        else
        {
            // If not available and first to discover, order a pizza
            if (first)
            {
                first = 0;
                printf("\nStudent-%d ordered pizza.", *(int *)i);
                pthread_cond_signal(&orderPizza);
            }
            // Wait for delivery
            pthread_cond_wait(&deliverPizza, &entry);
            printf("\nPizza is delivered.");
        }
        pthread_mutex_unlock(&entry);
        // Study
    }
}

// Function for pizza delivery service
void *deliveryService(void *i)
{
    printf("\nPizza services - up and running.");
    while (1)
    {
        pthread_mutex_lock(&entry);
        // Wait for pizza order
        pthread_cond_wait(&orderPizza, &entry);
        // Making Pizza
        for (int i = 0; i < 10000; i++)
            ;
        printf("\nPizza made.");
        slices = slice_in_pizza;
        first = 1;
        // Broadcast pizza delivery
        pthread_cond_broadcast(&deliverPizza);
        pthread_mutex_unlock(&entry);
    }
}

int main()
{
    // Initialising mutex and conditions
    pthread_mutex_init(&entry, NULL);
    pthread_cond_init(&orderPizza, NULL);
    pthread_cond_init(&deliverPizza, NULL);

    // Creating delivery service thread
    pthread_t service;
    pthread_create(&service, NULL, deliveryService, NULL);

    // Creating student's thread
    pthread_t students[8];
    for (int i = 0; i < 8; ++i)
    {
        int id = i;
        int x = pthread_create(&students[i], NULL, student, (void *)&id);
    }
    for (int i = 0; i < 8; ++i)
        pthread_join(students[i], NULL);

    // Destroying mutex and conditions
    pthread_mutex_destroy(&entry);
    pthread_cond_destroy(&orderPizza);
    pthread_cond_destroy(&deliverPizza);

    return 0;
}