#include <stdio.h>
#include <stdlib.h>

#define NUMBER_ENTRIES  (1001)
#define FALSE           (0)
#define TRUE            (1)
#define DONE            (2)

struct request{
	int is_req;
	int is_allocated;
	int size;
	int base_adr;
	int next_boundary_adr;
	int memory_left;
	int largest_chunk;
	int elements_on_free_list;
}req_array[NUMBER_ENTRIES];

struct free_list{
	struct free_list *next;
	struct free_list *previous;
	int block_size;
	int block_adr;
	int adjacent_adr;
}list_head, *top;

struct buddy_request{
	int is_req;
	int is_allocated;
	int size;
	int act_size;
	int base_adr;
	int next_boundary_adr;
	int memory_left;
	int largest_chunk;
	int elements_on_free_list;
}buddy_req_array[NUMBER_ENTRIES];

struct buddy_free_list{
	struct buddy_free_list *next;
	struct buddy_free_list *previous;
	int block_size;
	int block_adr;
	int adjacent_adr;
}list_head_buddy, *top_buddy;

int best_fit (int,char *);
int buddy_system (int, char *);
int first_fit(int , char *);
