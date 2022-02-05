#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_ENTRIES 1001
#define FALSE 0
#define TRUE 1
#define DONE 2
#define FIRSTFIT 3
#define BESTFIT 4
#define BUDDY 5
#define ALLOC 6
#define FREE 7

typedef struct request{
  int failed;
  int serial_number;
  int request_type;
  int sizeof_request;
  int allocation_address;
  int total_free;
  int largest_available;
  int true_size;
} MY_ARRAY[NUMBER_ENTRIES];

typedef struct list{
  struct list *prev;
  struct list*next;
  int seq_num;
  int start_addr;
  int adj_addr;
  int size;
  int total_free;
  int free_space;
} MY_LIST;

MY_LIST *allocate_node( void );
int free_node( int seq_num, int free_seq_num);
int allocate_memory( int seq_num );
void coalesce( void );
char *print_num( int num );
void print_req_array( void );
int buddy_system ( int seq_num );

int total_free_space;
int policy;
int largest_available;
int total_allocations = 0;

MY_LIST *used_list;
MY_ARRAY req_array;

