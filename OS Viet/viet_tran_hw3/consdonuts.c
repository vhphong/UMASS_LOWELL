//Viet Tran
//viet_tran1@student.uml.edu
//Assignment 3
//Operating System
#include <stdio.h>
#include <stdlib.h>

#include "donuts.h"

int main(int argc, char *argv[]){

  int i, j, k, a, b, c, x;
  int count_1, count_2, count_3, count_4;
  int _shmID, _semID[3];
  struct donut_ring *_ring;
  struct timeval randtime;
  int _temp[4][12];
  FILE *fin;
  struct tm* temp_time;
  char time_string[40];
  long mil_sec;

  for(a = 0; a < 4; a++){
      for(b = 0; b < 12; b++){
	_temp[a][b] = 0;
      }
  }

  
  if((_shmID = shmget (MEMKEY, 0, 0)) == -1){
	  perror("consumer shared get failed: ");
	  exit(1);
  }

  if((_ring = (struct donut_ring *)
				shmat (_shmID, NULL, 0)) == -1){
	  perror("consumer shared attach failed: ");
          exit(1);
  }

  for(i = 0; i < NUMSEMIDS; i++)
  if ((_semID[i] = semget (SEMKEY+i, NUMFLAVORS, 
			   IPC_CREAT | 0600)) == -1){
       perror("semaphore attach failed: ");
       exit(1);
  }

  for(i = 0; i < 10; i++){
    count_1 = 0;
    count_2 = 0;
    count_3 = 0;
    count_4 = 0;
    for( j = 0; j < 12; j++){      

      //producing random number for donut. yum
      gettimeofday (&randtime, (struct timezone *)0);
      unsigned short xsub1[3];
      xsub1[0] = (ushort) randtime.tv_usec;
      xsub1[1] = (ushort)(randtime.tv_usec >> 16);
      xsub1[2] = (ushort)(getpid());
      k = nrand48(xsub1) & 3;
            
      p(_semID[OUTPTR], k);
      p(_semID[CONSUMER], k);

      x = _ring->flavor[k][_ring->outptr[k]];     
      
      switch(k){
      case 0:
	{
	  _temp[k][count_1] = x;
	  count_1 = count_1 + 1;
	  break;
	}
      case 1:
        {
	  _temp[k][count_2] = x;
	  count_2 = count_2 + 1;
	  break;
	}
      case 2:
        {
	  _temp[k][count_3] = x;
	  count_3 = count_3 + 1;
	  break;
	}
      case 3:
        {
	  _temp[k][count_4] = x;
	  count_4 = count_4 + 1;
	  break;
	}      
      } 

      if(_ring->outptr[k] >= NUMSLOTS)
	_ring->outptr[k] = 0;
      else
	_ring->outptr[k] = _ring->outptr[k] + 1;      

      v(_semID[PROD], k);
      v(_semID[OUTPTR], k);     
      
    }

    
    temp_time = localtime (&randtime.tv_sec);
    strftime (time_string, sizeof (time_string), "%H:%M:%S", temp_time);
    mil_sec = randtime.tv_usec / 1000;

    printf("\n\nProcess PID: %d     ", getpid());
    printf("time: %s.%03ld     ", time_string, mil_sec);                
    printf("dozen#: %d\n", i+1);

    printf("%s\t%s\t%s\t%s\n", pcdonuts[0], pcdonuts[1], pcdonuts[2], pcdonuts[3]);
    for (c = 0; c < 12; c++){
      printf("%d\t\t%d\t\t%d \t\t%d\n", 
              _temp[0][c], 
              _temp[1][c], 
              _temp[2][c], 
              _temp[3][c]);
    }
    
    for(a = 0; a < 4; a++){
      for(b = 0; b < 12; b++){
	_temp[a][b] = 0;
      }
    }

  } 

  return 0;

}
