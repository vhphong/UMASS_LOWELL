/*
	The following data structures used for the first fit 
  and best fit implementations for assignment 5
	Take this from http://www.cs.uml.edu/~bill/cs308/Assignment_5_data_structs.txt
*/

#ifndef _MAIN_H
#define _MAIN_H

#include<stdio.h>
#include<math.h>

#define NUMBER_ENTRIES  (1001)
#define FALSE           (0)
#define TRUE            (1)
#define DONE            (2)

struct lel{
        struct lel *next;
        struct lel *prev;
        int adr;
        int bud_adr;
        int bit;
};

struct lh{
        struct lel *head;
        int cnt;
};

struct request{
        int is_req;
        int is_allocated;
        int size;
		int act_size;
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
int total_free_space;
int total_free;

int allocateMemoryBest(struct request *);
int allocateMemoryFirst(struct request *);
int allocateMemoryBuddySys(struct request *);

int update_list(int);

struct lh lst_ary[21];
int total_free_space, total_free;

struct lel *find_el(int bit);
int update_lists(struct lel *el);



#endif

