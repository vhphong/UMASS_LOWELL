/**********************************************************************/
/* Viet Tran														  */
/* 																	  */
/* Example code from ~bill/cs308/call_help_assign4.txt				  */
/**********************************************************************/

/****************************/
/*      GLOBAL VARIABLES    */
/****************************/

#include <stdlib.h>
#include <stdio.h>

#include "pc_threads.h"

struct DONUT_SHOP shared_ring;
pthread_mutex_t prod [NUMFLAVORS];
pthread_mutex_t cons [NUMFLAVORS];
pthread_cond_t prod_cond [NUMFLAVORS];
pthread_cond_t cons_cond [NUMFLAVORS];
pthread_t thread_id [NUMCONSUMERS + NUMPRODUCERS], sig_wait_id;



int main(int argc, char *argv[]) {

	int i, j, k, nsigs;
	struct timeval randtime, first_time, last_time;
	struct sigaction new_act;
	int arg_array[NUMCONSUMERS];
	sigset_t all_signals;
	int sigs[] = {SIGBUS, SIGSEGV, SIGFPE};

	pthread_attr_t thread_attr;
	struct sched_param sched_struct;




	/**********************************************************************/
	/* INITIAL TIMESTAMP VALUE FOR PERFORMANCE MEASURE                    */
	/**********************************************************************/

	gettimeofday(&first_time, (struct timezone *) 0);
	for (i = 0; i < NUMCONSUMERS + 1; i++) 
	{
		arg_array [i] = i; /** SET ARRAY OF ARGUMENT VALUES **/
	}

  /**********************************************************************/
  /* GENERAL PTHREAD MUTEX AND CONDITION INIT AND GLOBAL INIT           */
  /**********************************************************************/

	for (i = 0; i < NUMFLAVORS; i++) 
	{
		pthread_mutex_init(&prod [i], NULL);
		pthread_mutex_init(&cons [i], NULL);
		pthread_cond_init(&prod_cond [i], NULL);
		pthread_cond_init(&cons_cond [i], NULL);
		shared_ring.outptr [i] = 0;
		shared_ring.in_ptr [i] = 0;
		shared_ring.serial [i] = 0;
		shared_ring.spaces [i] = NUMSLOTS;
		shared_ring.donuts [i] = 0;
	}



	/**********************************************************************/
	/* SETUP FOR MANAGING THE SIGTERM SIGNAL, BLOCK ALL SIGNALS           */
	/**********************************************************************/
	/*
	sigfillset(&all_signals);
	nsigs = sizeof ( sigs) / sizeof ( int);
    for (i = 0; i < nsigs; i++)
      sigdelset(&all_signals, sigs [i]);

	sigprocmask(SIG_BLOCK, &all_signals, NULL);
	sigfillset(&all_signals);
	for (i = 0; i < nsigs; i++) 
	{
		new_act.sa_handler = sig_handler;
		new_act.sa_mask = all_signals;
		new_act.sa_flags = 0;
		if (sigaction(sigs[i], &new_act, NULL) == -1) {
			perror("can't set signals: ");
			exit(1);
		}
	}
	*/
  
	printf("just before threads created\n");


	for (i = 1; i < NUMCONSUMERS + 1; i++) {
		if (pthread_create(&thread_id [i], &thread_attr,
			   consumer, (void *) &arg_array [i]) != 0) {
			printf("pthread_create failed");
			exit(3);
		}
	}

	for(; i < NUMPRODUCERS + NUMCONSUMERS; i++)
	{
		if( pthread_create (&thread_id[i], &thread_attr, 
				producer, NULL) !=0){
			printf("pthread_create failed");
			exit( 3 );
		}
	}
	printf("just after threads created\n");

	/*********************************************************************/
	/* WAIT FOR ALL CONSUMERS TO FINISH, SIGNAL WAITER WILL              */
	/* NOT FINISH UNLESS A SIGTERM ARRIVES AND WILL THEN EXIT            */
	/* THE ENTIRE PROCESS....OTHERWISE MAIN THREAD WILL EXIT             */
	/* THE PROCESS WHEN ALL CONSUMERS ARE FINISHED                       */
	/*********************************************************************/

	for (i = 1; i < NUMCONSUMERS + 1; i++)
		pthread_join(thread_id [i], NULL);

	/*****************************************************************/
	/* GET FINAL TIMESTAMP, CALCULATE ELAPSED SEC AND USEC           */
	/*****************************************************************/


	gettimeofday(&last_time, (struct timezone *) 0);
	if ((i = last_time.tv_sec - first_time.tv_sec) == 0)
		j = last_time.tv_usec - first_time.tv_usec;
	else 
	{
		if (last_time.tv_usec - first_time.tv_usec < 0) {
			i--;
			j = 1000000 + (last_time.tv_usec - first_time.tv_usec);
		} 
		else 
		{
		  j = last_time.tv_usec - first_time.tv_usec;
		}
	}
	printf("Elapsed consumer time is %d sec and %d usec\n", i, j);

	printf("\n\n ALL CONSUMERS FINISHED, KILLING  PROCESS\n\n");
	exit(0);
}



/*********************************************/
/* INITIAL PART OF PRODUCER.....             */

/*********************************************/

void *producer(void *arg) {
  int i, j, k;
  unsigned short xsub [3];
  struct timeval randtime;

  gettimeofday(&randtime, (struct timezone *) 0);
  xsub [0] = (ushort) randtime.tv_usec;
  xsub [1] = (ushort) (randtime.tv_usec >> 16);
  xsub [2] = (ushort) (pthread_self());

  /*october 23 http://echoess.uml.edu:8080/ess/echo/presentation/d564b970-d599-474c-ac57-510399c8f1d4?ec=true*/
  while (1) {
    j = nrand48(xsub) & 3;
    pthread_mutex_lock(&prod [j]);
    while (shared_ring.spaces [j] == 0) {
      pthread_cond_wait(&prod_cond [j], &prod [j]);
    }
    
    /*put donut in queue*/
    shared_ring.flavor[j][shared_ring.in_ptr[j]] = shared_ring.serial[j];
    
    shared_ring.spaces[j]--; /*decreament space counter*/
    shared_ring.in_ptr[j] = (shared_ring.in_ptr[j]+1)%NUMSLOTS;
    shared_ring.serial[j]++; /*increament serial number*/
    pthread_mutex_unlock(&prod [j]); /*unclock prod mutex*/

    pthread_mutex_lock(&cons[j]); /*get cons mutex*/
    
    shared_ring.donuts[j]++; /*incr donut count*/
    pthread_mutex_unlock(&cons[j]); /*unlock cons mutex*/

    pthread_cond_signal(&cons_cond[j]); /*signal cons_condx_var*/
  }
  return NULL;
}

  /*********************************************/
  /* ON YOUR OWN FOR THE CONSUMER.........     */

  /*********************************************/

void *consumer(void *arg) {
 
	/*Homework 3*/ 
	struct tm* temp_time;
	char time_string[40];
	long mil_sec;

	int i, j, k, m, id, x;

	int output_array[NUMFLAVORS][12];
	FILE *fp;

	char file_name[10];

	int count[4];
	unsigned short xsub [3];
	struct timeval randtime;  

  id = *(int *) arg;

  sprintf(file_name, "Consumer_%d", id );	
  fp = fopen(file_name, "w");    
  fclose(fp);
	
  fp = fopen(file_name, "a");



 
  gettimeofday(&randtime, (struct timezone *) 0);
  xsub [0] = (ushort) randtime.tv_usec;
  xsub [1] = (ushort) (randtime.tv_usec >> 16);
  xsub [2] = (ushort) (pthread_self());

  for (i = 0; i < NUMDOZENS ; i++) {
	
    for ( x = 0; x < 4; x++){
        count[x] = 0;
    }
    for ( x = 0; x < 4; x++){
      for( k = 0; k < 12; k++){
          output_array[x][k] = -1;    
      } 
    }

    for (m = 0; m < 12; m++) {
      
      j = nrand48(xsub) & 3;
      
      pthread_mutex_lock(&cons[j]);
      while(shared_ring.donuts[j] == 0){
	pthread_cond_wait(&cons_cond[j], &cons[j]);
      }

      /*taking donut from queue*/
      output_array[j][m] = shared_ring.flavor[j][shared_ring.outptr[j]];
      
      /*increment the out pointer*/
      shared_ring.outptr[j] = (shared_ring.outptr[j]+1) % NUMSLOTS;

      shared_ring.donuts[j]--; /*decrement donut counter*/
      
      pthread_mutex_unlock(&cons[j]); /*unlock cons mutex*/
      pthread_mutex_lock(&prod[j]);  /*get prod mutex*/
      
      shared_ring.spaces[j]++; /*increment space count*/
      
      pthread_mutex_unlock(&prod[j]); /*unlock prod mutex*/
      pthread_cond_signal(&prod_cond[j]); /*signal prod_condx_var*/
      
    }
    
    /*****************************************************************/
    /* USING A MICRO-SLEEP AFTER EACH DOZEN WILL ALLOW ANOTHER       */
    /* CONSUMER TO START RUNNING, PROVIDING DESIRED RANDOM BEHVIOR   */
    /*****************************************************************/
    
    usleep(1000); /* sleep 1 ms */
    
    temp_time = localtime (&randtime.tv_sec);
    strftime (time_string, sizeof (time_string), "%H:%M:%S", temp_time);
    mil_sec = randtime.tv_usec / 1000;

    fprintf(fp,"\n\nProcess PID: %d     ", getpid());
    fprintf(fp,"time: %s.%03ld     ", time_string, mil_sec);                
    fprintf(fp,"dozen#: %d\n", i+1);

    fprintf(fp,"Plain\tglaze\tcoconut\tChocolate\n");
    
    for( x = 0; x<12; x++){
       for(k =0; k < 4; k++){
       
       if(output_array[k][x] == -1){
     
       fprintf(fp, "\t\t");
       
       }else{
          
         fprintf(fp, "%d\t\t", output_array[k][x]);
        } 
       }
	fprintf(fp, "\n");
    } 

    
    
   
  }
  fclose(fp);	
  return NULL;
}              

/***********************************************************/
/* PTHREAD ASYNCH SIGNAL HANDLER ROUTINE...                */
/***********************************************************/

void    *sig_waiter ( void *arg ) {
	sigset_t sigterm_signal;
	int signo;

	sigemptyset ( &sigterm_signal );
	sigaddset ( &sigterm_signal, SIGTERM );
	sigaddset ( &sigterm_signal, SIGINT );


	if (sigwait ( &sigterm_signal, & signo)  != 0 ) {
		printf ( "\n  sigwait ( ) failed, exiting \n");
		exit(2);
	}

	printf ( "process going down on SIGNAL (number %d)\n\n", signo );
	exit ( 1 );
	return NULL;

}


/**********************************************************/
/* PTHREAD SYNCH SIGNAL HANDLER ROUTINE...                */
/**********************************************************/

voidsig_handler ( int sig ){
	pthread_t signaled_thread_id;
	int i, thread_index;

	signaled_thread_id = pthread_self ( );
	for ( i = 0; i < (NUMCONSUMERS + 1 ); i++) 
	{
		if ( signaled_thread_id == thread_id [i] ) 
		{
			thread_index = i;
			break;
		}
	}

	printf ( "\nThread %d took signal # %d, PROCESS HALT\n",
	thread_index, sig );
	exit ( 1 );

}
  






