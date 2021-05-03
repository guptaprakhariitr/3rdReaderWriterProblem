LINK TO GITHUB REPO : https://github.com/guptaprakhariitr/3rdReaderWriterProblem

# Operating Systems

- Assignment 6
- **Prakhar Gupta**
- **19112056**

# **Starve-Free Readers Writers Problem**

**The Semaphores**

1. r_and_w_order_queue : It will be used to maintain the order in which readers and writers arrive.
2. resource_var : It will be used to prevent multiple writers or readers and writers to be present in critical section at the same time.
3. r_mutex_mutual : It will be used to provide mutual exclusion to reader_counter variable that is responsible for counting the number of readers present in the critical section at any particular instance.

**The Shared variables**

1. data : It is the part of program that is shared among various threads. It holds the data or the value of the resource read/write by the readers/writers
2. reader_counter : It will be used to count number of readers present in critical section at any particular instance of time.

**The funtions for Reader:**

1. Entry section : This section acquires required semaphores to enter critical section.

- Reader tries to acquires r_and_w_order_queue Semaphore initially, if it is unavailable, reader is added to queue for the given Semaphore.
- After aquiring r_and_w_order_queue, it then tries to aquire r_mutex_mutual Semaphore to modify reader_counter.
- If it is the first reader, it tries to aquire resource_var Semaphore to confirm there are no writers in the critical section.
- It releases r_and_w_order_queue and r_mutex_mutual before entering critical section.

2. Critical section : Reader reads the shared data in this section.
3. Exit section : This section releases the aquired semaphores.

- Reader tries to aquire r_mutex_mutual to modify reader_counter.
- If it is the last reader, it releases resource_var Semaphore.
- It releases r_mutex_mutual at the end.

**The funtion of Writer**

1. Entry section : This section acquires required semaphores to enter critical section.

- Writer tries to acquires r_and_w_order_queue Semaphore initially, if it is unavailable, writer is added to queue for the given Semaphore.
- After aquiring r_and_w_order_queue, it tries to aquire resource_var Semaphore and enter critical section.
- It releases r_and_w_order_queue before entering critical section.

2. Critical section : Writer modifies the shared data in this section.
3. Exit section : This section releases the aquired semaphores.

- Writer releases the resource_var Semaphore.

**Main function**

1. It initialises reader threads with reader function and writer threads with writer function.
2. It takes number of readers and writers as input from the user.
3. It creates required number of threads followed by initialisation of semaphores.
4. All threads are joined back to the parent thread.
5. At the end of the execution, all initialized semaphores are destroyed.

**On Linux(Ubuntu 18.04.5 LTS) System:**

1. gcc -pthread main.cpp
2. ./a.out
