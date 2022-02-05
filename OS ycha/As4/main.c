#include "project_header.h"

struct donut_ring shared_ring;
pthread_mutex_t prod[NUMFLAVORS];
pthread_mutex_t cons[NUMFLAVORS];
pthread_cond_t prod_cond[NUMFLAVORS];
pthread_cond_t cons_cond[NUMFLAVORS];
pthread_t thread_id[NUMCONSUMERS + 1], sig_wait_id;

int main(int argc, char *argv[]) {
    int i, j, k, nsigs;
    struct timeval randtime, first_time, last_time;
    struct sigaction new_act;
    int arg_array[NUMCONSUMERS];
    sigset_t all_signals;
    int sigs[] = { SIGBUS, SIGSEGV, SIGFPE };

    pthread_attr_t thread_attr;
    struct sched_param sched_struct;

    gettimeofday(&first_time, (struct timezone *) 0);
    for (i = 0; i < NUMCONSUMERS + 1; i++) {
        arg_array[i] = i; 
    }

    for (i = 0; i < NUMFLAVORS; i++) {
        pthread_mutex_init(&prod[i], NULL);
        pthread_mutex_init(&cons[i], NULL);
        pthread_cond_init(&prod_cond[i], NULL);
        pthread_cond_init(&cons_cond[i], NULL);
        shared_ring.outptr[i] = 0;
        shared_ring.in_ptr[i] = 0;
        shared_ring.serial[i] = 0;
        shared_ring.spaces[i] = NUMSLOTS;
        shared_ring.donuts[i] = 0;
    }

    sigfillset(&all_signals);
    nsigs = sizeof(sigs) / sizeof(int);
    for (i = 0; i < nsigs; i++)
        sigdelset(&all_signals, sigs[i]);
    sigprocmask(SIG_BLOCK, &all_signals, NULL);
    sigfillset(&all_signals);
    for (i = 0; i < nsigs; i++) {
        new_act.sa_handler = sig_handler;
        new_act.sa_mask = all_signals;
        new_act.sa_flags = 0;
        if (sigaction(sigs[i], &new_act, NULL) == -1) {
            perror("Sigaction error: ");
            exit(1);
        }
    }

    if (pthread_create(&sig_wait_id, NULL, sig_waiter, NULL) != 0) {

        printf("pthread_create failed: ");
        exit(3);
    }

    pthread_attr_init(&thread_attr);
    pthread_attr_setinheritsched(&thread_attr, PTHREAD_INHERIT_SCHED);

#ifdef  GLOBAL
    sched_struct.sched_priority = sched_get_priority_max(SCHED_OTHER);
    pthread_attr_setinheritsched ( &thread_attr,
            PTHREAD_EXPLICIT_SCHED );
    pthread_attr_setschedpolicy ( &thread_attr, SCHED_OTHER );
    pthread_attr_setschedparam ( &thread_attr, &sched_struct );
    pthread_attr_setscope ( &thread_attr,
            PTHREAD_SCOPE_SYSTEM );
#endif

    if (pthread_create(&thread_id[0], &thread_attr, producer, NULL) != 0) {
        printf("pthread_create failed ");
        exit(3);
    }
    for (i = 1; i < NUMCONSUMERS + 1; i++) {
        if (pthread_create(&thread_id[i], &thread_attr, consumer,
                (void *) &arg_array[i]) != 0) {
            printf("pthread_create failed");
            exit(3);
        }
    }

    /*********************************************************************/
    /* WAIT FOR ALL CONSUMERS TO FINISH, SIGNAL WAITER WILL              */
    /* NOT FINISH UNLESS A SIGTERM ARRIVES AND WILL THEN EXIT            */
    /* THE ENTIRE PROCESS....OTHERWISE MAIN THREAD WILL EXIT             */
    /* THE PROCESS WHEN ALL CONSUMERS ARE FINISHED                       */
    /*********************************************************************/

    for (i = 1; i < NUMCONSUMERS + 1; i++)
        pthread_join(thread_id[i], NULL);

    /*****************************************************************/
    /* GET FINAL TIMESTAMP, CALCULATE ELAPSED SEC AND USEC           */
    /*****************************************************************/

    gettimeofday(&last_time, (struct timezone *) 0);
    if ((i = last_time.tv_sec - first_time.tv_sec) == 0)
        j = last_time.tv_usec - first_time.tv_usec;
    else {
        if (last_time.tv_usec - first_time.tv_usec < 0) {
            i--;
            j = 1000000 + (last_time.tv_usec - first_time.tv_usec);
        } else {
            j = last_time.tv_usec - first_time.tv_usec;
        }
    }
    printf("\nElapsed consumer time is %d sec and %d usec\n", i, j);

    printf("\n\n ALL CONSUMERS FINISHED, KILLING  PROCESS\n\n");
    exit(0);
}

/*********************************************/
/* INITIAL PART OF PRODUCER.....             */
/*********************************************/
