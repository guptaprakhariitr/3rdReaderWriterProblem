#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

int data = 1;                                            // critical data to be shared
int reader_counter = 0;                                  // readers counter
sem_t r_and_w_order_queue, resource_var, r_mutex_mutual; // semaphore declarations

/*
 * this function have logic to read shared data
 */
void *reader(void *rid)
{
    // ENTRY section
    sem_wait(&r_and_w_order_queue);
    sem_wait(&r_mutex_mutual);
    reader_counter++;
    if (reader_counter == 1)
    {
        sem_wait(&resource_var);
    }
    sem_post(&r_and_w_order_queue);
    sem_post(&r_mutex_mutual);
    // ENTRY section end

    // CRITICAL section
    printf("Reader %d: read the data as %d\n", *((int *)rid), data);
    // CRITICAL section end

    // EXIT section
    sem_wait(&r_mutex_mutual);
    reader_counter--;
    if (reader_counter == 0)
    {
        sem_post(&resource_var);
    }
    sem_post(&r_mutex_mutual);
    // EXIT section end
}

/*
 * this function have logic to write shared data
 */
void *writer(void *wid)
{
    // ENTRY section
    sem_wait(&r_and_w_order_queue);
    sem_wait(&resource_var);
    sem_post(&r_and_w_order_queue);
    // ENTRY section end

    // CRITICAL section
    data = data * 2;
    printf("Writer %d updated the data to %d\n", (*((int *)wid)), data);
    // CRITICAL section end

    // EXIT section
    sem_post(&resource_var);
    // EXIT section end
}

int main()
{
    int count_of_readers, count_of_Writers, MAX_ID;
    int loop_variable;
    printf("Input the number of Readers: \n");
    scanf("%d", &count_of_readers);

    printf("Input the number of Writers: \n");
    scanf("%d", &count_of_Writers);

    MAX_ID = count_of_readers >= count_of_Writers ? count_of_readers : count_of_Writers;

    int id_for_pr[MAX_ID];
    for (loop_variable = 0; loop_variable < MAX_ID; loop_variable++)
        id_for_pr[loop_variable] = loop_variable + 1;

    pthread_t thread_read[count_of_readers], thread_write[count_of_Writers]; // tread creation

    // semaphore initialisation
    sem_init(&r_and_w_order_queue, 0, 1);
    sem_init(&r_mutex_mutual, 0, 1);
    sem_init(&resource_var, 0, 1);

    for (loop_variable = 0; loop_variable < count_of_readers; loop_variable++)
    {
        pthread_create(&thread_read[loop_variable], NULL, reader, (void *)&id_for_pr[loop_variable]);
    }
    for (loop_variable = 0; loop_variable < count_of_Writers; loop_variable++)
    {
        pthread_create(&thread_write[loop_variable], NULL, writer, (void *)&id_for_pr[loop_variable]);
    }

    for (loop_variable = 0; loop_variable < count_of_readers; loop_variable++)
    {
        pthread_join(thread_read[loop_variable], NULL);
    }
    for (loop_variable = 0; loop_variable < count_of_Writers; loop_variable++)
    {
        pthread_join(thread_write[loop_variable], NULL);
    }

    //destroying threads at the end of execution
    sem_destroy(&r_mutex_mutual);
    sem_destroy(&resource_var);
    sem_destroy(&r_and_w_order_queue);

    return 0;
}