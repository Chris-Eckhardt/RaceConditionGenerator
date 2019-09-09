#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
/**
 * THESE DEFINE VALUES CANNOT BE CHANGED.
 * DOING SO WILL CAUSE POINTS TO BE DEDUCTED
 * FROM YOUR GRADE
 */
 /** BEGIN VALUES THAT CANNOT BE CHANGED */
#define MAX_THREADS 36
#define MAX_ITERATIONS 22
/** END VALUES THAT CANNOT BE CHANGED */


/**
 * use this struct as a parameter for the
 * nanosleep function.
 * For exmaple : nanosleep(&ts, NULL);
 */
struct timespec ts = {0, 40000000};

/*********** GLOBAL VARIABLE ***********/
int g_var = 0;

/************ THREAD INFO **************/
struct thread_info {
    int id;
    pthread_t tid;
};

/************ ADDER THREAD **************/
void *
adder_thread(void * arg)
{
    int temp;
    int id = *((int*) arg);
    //nanosleep(&ts, NULL);
    for(int i = 0; i < MAX_ITERATIONS; i++) {
        
        //nanosleep(&ts, NULL);
        temp = g_var;
        temp+=10;
        nanosleep(&ts, NULL);
        g_var = temp;
        printf("Current Value written to Global Variables by ADDER thread id: %d is %d \n", id, temp);


    }
    
}

/********** SUBTRACTOR THREAD ***********/
void *
subtractor_thread(void * arg)
{
    int temp;
    int id = *((int*) arg);
    //nanosleep(&ts, NULL);
    for(int i = 0; i < MAX_ITERATIONS; i++) {

        //nanosleep(&ts, NULL);
        temp = g_var;
        temp-=10;
        nanosleep(&ts, NULL);
        g_var = temp;
        printf("Current Value written to Global Variables by SUBTRACTOR thread id: %d is %d \n", id, temp);

    }
}

/************** MAIN ***************/
int
main(int argc, char** argv)
{
    struct thread_info * thread_args = malloc(MAX_THREADS*sizeof(struct thread_info));
    int evens = 1;
    int i;

    // Spawn threads
    for(i = 0; i < MAX_THREADS; i++)
    {
        //nanosleep(&ts, NULL);
        thread_args[i].id = i+1;
        if(evens) {
            
            //nanosleep(&ts, NULL);
            pthread_create( &thread_args[i].tid, NULL, adder_thread, &thread_args[i] );
            evens = 0;
            //nanosleep(&ts, NULL);

        } 
        else {

            //nanosleep(&ts, NULL);
            pthread_create( &thread_args[i].tid, NULL, subtractor_thread, &thread_args[i] );
            evens = 1;
            //nanosleep(&ts, NULL);

        }
    }

    for(i = 0; i < MAX_THREADS; i++)
    {
        //nanosleep(&ts, NULL);
        pthread_join(thread_args[i].tid, NULL);
    }





    /***** FINAL VALUE *****/
    printf("Final Value is: %d \n", g_var);

    return 0;
}
