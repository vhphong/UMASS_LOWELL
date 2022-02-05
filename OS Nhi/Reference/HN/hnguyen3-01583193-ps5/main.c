/*******************************************************                        
  Name: Hung Q Nguyen                                                           
  Student ID: 01583193                                                          
  Email: Hung_Nguyen3@student.uml.edu                                           
  Date: 4/18/2017                                                                
  Assignment 5                         
*******************************************************/
#include "main.h"

int main(int argc, char *argv[]){
	// Needed more than 3 arguments to be able to execute
	// Show message and then exit without giving error
	if (argc < 3) {
		printf("**** ATTENTION! Wrong executable command!\n");
		printf("To Execute: ./main [Function Type] [Alloc Num] [Input Data]> [Output File]\n");
		return 0;
	}

	req_type = malloc(100* sizeof(char));
	os = malloc(100*sizeof(char));

	if (strcmp (argv[1], BEST_FIT_CALL) == 0) {
		getBestFit(atoi(argv[2]), argv[3]);
	} else if (strcmp (argv[1], FIRST_FIT_CALL) == 0) {
		getFirstFit(atoi(argv[2]), argv[3]);
	} else {
		getSysBuddy(atoi(argv[2]), argv[3]);
	}

	return 0;
}

int allocMemFirst(struct request *req) {
	// Initialize free list
	struct free_list* fList = malloc(sizeof(struct free_list));
	fList = list_head.next;

	while (fList != NULL) {
		if (req->size <= fList->block_size) {
			initMemRequest(req,fList);
  		fList->block_size -= req->size;
			if (fList->block_size == 0) {
				//jump and free when block size is 0
				fList->previous->next = fList->next;
				fList->next->previous = fList->previous;
				free(fList);
				return 0;
			}
			fList->block_adr += req->size; 
      return 0; 
		}
		fList = fList->next;
	}
	return 0;
}

int allocMemBestOrBuddy(struct request *req) {
	struct free_list* fList = list_head.next;
	temp_list = malloc(sizeof(struct free_list));

	while(fList != NULL) {
		if (isFirst) {
			if (req->size <= fList->block_size) {
				mem_size = fList->block_size - req->size;
				mem_left = mem_size;
				if (mem_size <= mem_left) {
					mem_left = mem_size;
					temp_list = fList;
				}
			}
			isFirst = false;
		} else {
			if (req->size <= fList->block_size) {
				mem_size = fList->block_size - req->size;
				if (mem_size <= mem_left) {
					mem_left = mem_size;
					temp_list = fList;
				}
			}
		}
		fList = fList->next;
	}

	if (temp_list == NULL) {
		printf("failed to allocate memory for best fit\n");
		req->memory_left = total_free;
		mem_size = 0;
		mem_left = 0;
		free(temp_list);
  	return 0;
	} else {
		initMemRequest(req,temp_list);
		if (temp_list->block_size -= req->size == 0) {
			//jump and free when block size is 0
			temp_list->previous->next = temp_list->next;
			temp_list->next->previous = temp_list->previous;

			free(temp_list);
			mem_size = 0;
			mem_left = 0;
			return 0;
		}
		temp_list->block_adr += req->size;
		mem_size = 0;
		mem_left = 0;
		free(temp_list);
		return 0;
	}
}

int getBestFit(int memSize, char* file_name) {
	// Open file to read
	FILE* fop = fopen(file_name, "r");

	// Init Freesize
	initFreeSize(memSize);
	char req_type[50];
	struct free_list* fList = malloc(sizeof(struct free_list));

	// Read each line of the input
	while(fscanf(fop, "%d %s %d", &req_seq, &req_type, &req_size) != EOF) {
		if(strcmp(req_type, "alloc") == 0 ){
			// init request
	    initBestRequest();

	    fList = list_head.next;
	    while (fList != NULL) {
				++req_array[req_seq].elements_on_free_list;
				if(fList -> block_size > req_array[req_seq].largest_chunk){
				  req_array[req_seq].largest_chunk = fList -> block_size;
				}
				fList = fList->next;
	    }
		} else {
			freeRequest();

			fList = list_head.next;
			while (fList != NULL) {
				++req_array[req_seq].elements_on_free_list;
        if(fList->block_size > req_array[req_seq].largest_chunk){
          req_array[req_seq].largest_chunk = fList->block_size;
        }
        fList = fList->next;
			}
		}
	}

	print(BEST_FIT_CALL, memSize, req_array);
	fclose(fop);
	req_seq = 0; req_size = 0;

	return 0;
}

int getFirstFit(int memSize, char* file_name) {
	// Open file to read
	FILE* fop = fopen(file_name, "r");

	// Init Freesize
	initFreeSize(memSize);
	char req_type[50];

	// Read each line of the input
	while(fscanf(fop, "%d %s %d", &req_seq, &req_type, &req_size) != EOF) {
		if(strcmp(req_type, "alloc") == 0 ){
			// init request
	    initFirstRequest();
	    struct free_list* fList = list_head.next;
	    
	    while (fList != NULL) {
				++req_array[req_seq].elements_on_free_list;
				if(fList -> block_size > req_array[req_seq].largest_chunk){
				  req_array[req_seq].largest_chunk = fList -> block_size;
				}
				fList = fList->next;
	    }
		} else {
			struct free_list* fList = list_head.next;
			freeRequest();
			while (fList != NULL) {
				++req_array[req_seq].elements_on_free_list;
        if(fList->block_size > req_array[req_seq].largest_chunk){
          req_array[req_seq].largest_chunk = fList->block_size;
        }
        fList = fList->next;
			}
		}
	}

	print(FIRST_FIT_CALL, memSize, req_array);
	fclose(fop);
	req_seq = 0; req_size = 0;
	return 0;
}

int getSysBuddy(int memSize, char* file_name) {
	// Open file to read
	FILE* fop = fopen(file_name, "r");

	// Init Freesize
	initFreeSize(memSize);

	char req_type[50];

	struct free_list* fList = malloc(sizeof(struct free_list));

	// Read each line of the input
	while(fscanf(fop, "%d %s %d", &req_seq, &req_type, &req_size) != EOF) {
		if(strcmp(req_type, "alloc") == 0 ){
			// init request
	    initBuddyRequest();

	    fList = list_head.next;
	    while (fList != NULL) {
				++req_array[req_seq].elements_on_free_list;
				if(fList -> block_size > req_array[req_seq].largest_chunk){
				  req_array[req_seq].largest_chunk = fList -> block_size;
				}
				fList = fList->next;
	    }
		} else {
			freeRequest();

			fList = list_head.next;
			while (fList != NULL) {
				++req_array[req_seq].elements_on_free_list;
        if(fList->block_size > req_array[req_seq].largest_chunk){
          req_array[req_seq].largest_chunk = fList->block_size;
        }
        fList = fList->next;
			}
		}
	}

	print(BUDDY_SYS_CALL, memSize, req_array);
	fclose(fop);
	req_seq = 0; req_size = 0;

	return 0;
}

void freeRequest() {
  req_array[req_seq].size = req_array[req_size].size;
  req_array[req_seq].is_allocated = req_array[req_size].is_allocated;
  update_list(req_size);
  req_array[req_seq].memory_left = total_free; 
  req_array[req_seq].elements_on_free_list = 0;
  req_array[req_seq].largest_chunk = 0;
}

void initMemRequest(struct request* req, struct free_list* list) {
	req->is_allocated = TRUE;
  req->base_adr = list->block_adr;
  req->next_boundary_adr = req->base_adr + req->size;
  total_free -= req -> size;
  req->memory_left = total_free;
}

void initFirstRequest() {
	// init request
  req_array[req_seq].is_req = TRUE;
  req_array[req_seq].size = req_size;
  allocMemFirst(&req_array[req_seq]);
  req_array[req_seq].elements_on_free_list = 0;
  req_array[req_seq].largest_chunk = 0;
}

void initBestRequest() {
	// init request
  req_array[req_seq].is_req = TRUE;
  req_array[req_seq].size = req_size;
  allocMemBestOrBuddy(&req_array[req_seq]);
  req_array[req_seq].elements_on_free_list = 0;
  req_array[req_seq].largest_chunk = 0;
}

void initBuddyRequest() {
	// init request
  req_array[req_seq].is_req = TRUE;
  req_array[req_seq].size = req_size;
  allocMemBestOrBuddy(&req_array[req_seq]);
  req_array[req_seq].elements_on_free_list = 0;
  req_array[req_seq].largest_chunk = 0;
}

void initFreeSize(int memsize) {
	total_free_space = mem_size * 1024;
	total_free = memsize * 1024;

	for(i = 0; i < NUMBER_ENTRIES; i++){
    req_array[i].is_req = FALSE;
    req_array[i].is_allocated = FALSE;
  }

  top = malloc(sizeof(struct free_list));
  top->next = NULL;
  top->block_size = total_free_space;
  top->previous = &list_head;
  top->adjacent_adr = total_free_space;
  top->block_adr = 0;

  list_head.next = top;
  list_head.previous = NULL;
  list_head.block_size = -1;
}

int update_list(int list) {
	// not allocated -- return
	if(req_array[list].is_allocated == FALSE) {
    return 0;
  } else {
  	req_array[list].is_allocated = DONE;
  	total_free += req_array[list].size;
  }

  struct free_list* fList = malloc(sizeof(struct free_list));
  struct free_list* tempList;
  
  fList = list_head.next;

  while (fList != NULL) {
  	if (req_array[list].base_adr > fList->block_adr) {
  		fList = fList->next;
  		continue;
  	}

  	tempList = malloc(sizeof(struct free_list));
  	tempList = getNewList(list);
  	switchNode(tempList, fList);
  	tailList = malloc(sizeof(struct free_list));

  	if (tempList->adjacent_adr == tempList->next->block_adr) {
  		tailList = tempList->next;
  		tempList->block_size += tempList->next->block_size;
      tempList->adjacent_adr = tempList->next->adjacent_adr;
      tempList->next = tempList->next->next;
      tempList->next->previous = tempList;
      free(tailList);
  	}

  	if (tempList->previous != NULL) {
  		tempList = tempList->previous;
	  	if (tempList->adjacent_adr != 0 && tempList->adjacent_adr == tempList->next->block_adr) {
	  		tailList = tempList->next;
	  		tempList->block_size += tempList->next->block_size;
	      tempList->adjacent_adr = tempList->next->adjacent_adr;
	      tempList->next = tempList->next->next;
	      free(tailList);
	  	}
	  }

  	return 0;
  }
}

struct free_list* getNewList(int size) {
	struct free_list* list = malloc(sizeof(struct free_list));
	list->block_size = req_array[size].size;
  list->block_adr = req_array[size].base_adr;
  list->adjacent_adr = list->block_adr + list->block_size;
  return list;
}

void switchNode(struct free_list* first, struct free_list* second) {
	first->next = second;
	second->previous->next = first;
	first->previous = second->previous;
	second->previous = first;
}

void print(char* type, int size, struct request* req) {
	char* title = malloc(100*sizeof(char));
	int count = 0;

	if (strcmp(type, BEST_FIT_CALL) == 0) {
		printf("POLICY: %s\tMEMORY SIZE: %d\n\n", "BEST FIT", size);
	} else if (strcmp(type, FIRST_FIT_CALL) == 0) {
		printf("POLICY: %s\tMEMORY SIZE: %d\n\n", "FIRST FIT", size);
	} else {
		printf("POLICY: %s\tMEMORY SIZE: %d\n\n", "BUDDY SYSTEM", size);
	}
	
  printf("\nNUMBER \tSEQUENCE \tSIZE \tADR \tMEMORY LEFT \tLARGEST CHUNK\n");

  for(i = 0; i < NUMBER_ENTRIES - 1; i++){
    if(req[i + 1].is_allocated == FALSE){
      req[i + 1].base_adr = -1;
      count++;
    }

    if(req[i+1].is_req == 1){
      sprintf(os, "%s", "alloc");
    } else {
      sprintf(os, "%s", "free");
    }

    printf("%d \t%s \t\t%d \t%d \t\t%d \t\t%d\n", i + 1, os, req[i + 1].size,
	   	req[i + 1].base_adr, req[i + 1].memory_left, req[i + 1].largest_chunk);
  }

  printf("%d Allocations Failed", count);
}