//Source from Bill Assignment5_struct

#ifndef _ULT_H
#define _ULT_H


#include<stdio.h>
#include<math.h>
#include<stdlib.h>
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
        struct lel *this_req;
}req_array[NUMBER_ENTRIES];

struct free_list{
        struct free_list *next;
        struct free_list *previous;
        int block_size;
        int block_adr;
        int adjacent_adr;
}list_head, *top;


int allocate_memory_bestfit(struct request *);
int allocate_memory_firstfit(struct request *);
struct lel *find_el(int bit);
int update_list_bf_ff(int index);
int update_list_bs(struct lel *el);
int mal_cnt = 0;
struct lh lst_ary[21];
int total_free_space, total_free;
void printout(char* policy, int Size, struct request *array);
int update_list(int index);
void print_results(char* policy, int memorySize, struct request* req);
int update_lists(struct lel *el);



#endif
