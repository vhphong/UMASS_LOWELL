/*******************************************************                        
  Name: Hung Q Nguyen                                                           
  Student ID: 01583193                                                          
  Email: Hung_Nguyen3@student.uml.edu                                           
  Date: 4/18/2017                                                                
  Assignment 5                         
*******************************************************/
#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

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
} req_array[NUMBER_ENTRIES];

struct free_list{
  struct free_list *next;
  struct free_list *previous;
  int block_size;
  int block_adr;
  int adjacent_adr;
} list_head, *top;

int total_free_space;
int free_list_length = 0, total_free;

#define BEST_FIT_CALL "bestfit"
#define FIRST_FIT_CALL "firstfit"
#define BUDDY_SYS_CALL "buddysys"

bool isFirst = TRUE;
int mem_size = 0;
int mem_left = 0;
int i, req_seq = 0, req_size = 0;
struct free_list* temp_list;
struct free_list* tailList;
char* os;
char* req_type;


// Custom functions
int allocMemFirst(struct request *);
int allocMemBestOrBuddy(struct request *);

int getBestFit(int, char*);
int getFirstFit(int, char*);
int getSysBuddy(int, char*);

int allocate_memory(struct request *);
int update_list(int);
struct free_list* getNewList(int size);

void initMemRequest(struct request *, struct free_list* );
void initFreeSize(int);
void initBestRequest();
void freeRequest();
void initBuddyRequest();
void initFirstRequest();
void switchNode(struct free_list*, struct free_list*);
void print(char*, int, struct request*);

#endif