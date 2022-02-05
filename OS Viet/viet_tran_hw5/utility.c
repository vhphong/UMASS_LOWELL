#include<stdlib.h>
#include "utility.h"


int update_list_bf_ff(int index){
	struct free_list *templist;
	struct free_list *block;  
	struct free_list *cBlock;
 
	if(req_array[index].is_allocated == FALSE)
		return 0;
	

	req_array[index].is_allocated = DONE;
	total_free = (total_free + req_array[index].size);
	

	for(templist=list_head.next; templist; templist=templist->next){
		

		if(req_array[index].base_adr > templist->block_adr) {
			continue;
		}
		

		if((block = malloc(sizeof(struct free_list))) == NULL) {
			printf("\nmalloc error, goodbye\n");
			exit(1);
		} else {
			block->block_size = req_array[index].size;
			block->block_adr = req_array[index].base_adr;
			block->adjacent_adr = block->block_adr + block->block_size;
			block->next = templist;
			templist->previous->next = block;
			block->previous = templist->previous;
			templist->previous = block;
		}

		if(block->adjacent_adr == block->next->block_adr) {
			cBlock = block->next;
			block->block_size += block->next->block_size;
			block->adjacent_adr = block->next->adjacent_adr;
			block->next = block->next->next;
			
			if(block->next){
				block->next->previous = block;
			}
			free(cBlock);
		}

		if(block->previous->adjacent_adr == block->block_adr) {
			block->previous->block_size += block->block_size;
			block->previous->adjacent_adr = block->adjacent_adr;
			block->previous->next = block->next;
			
			if(block->next){
				block->next->previous = block->previous;
			}
			free(block);
		}
		return;
	}
}

int update_list_bs(struct lel * el) {
    struct lel *list, *temp;
    int mask;

    if (lst_ary[el->bit].head) {
        mask = pow(2, (el->bit)+1);
        for (list = lst_ary[el-> bit].head; list; list = list->next) {
            if (list-> adr == el-> bud_adr || list->bud_adr == el->adr) {
                if (list->adr > el->adr) {
                    if ((el->adr) & mask) {
                        el->bud_adr = (el->adr) & (~mask);
                    } else {
                        el->bud_adr = (el->adr) | mask;
                    }
                    if (list->next) {
                        if (list->prev) {
                            list->prev->next = list->next;
                            list->next->prev = list->prev;
                        } else {
                            lst_ary[el->bit].head = list->next;
                            lst_ary[el->bit].head->prev = NULL;
                        }
                    } else {
                        if (list->prev) {
                            list->prev->next = list->next;
                        } else {
                            lst_ary[el->bit].head = NULL;
                        }
                    }
                    --lst_ary[el->bit].cnt;

                    free(list);
                    el->bit = el->bit + 1;
                    if (update_list_bs(el) == 0){
						return 0;
                    } else {
						return -1;
					}
                } 
				else 
				{

                    if ((list->adr) & mask) {
                        list->bud_adr = (list->adr) & (~mask);
                    } else {
                        list->bud_adr = (list->adr) | mask;
                    }

                    if (list->next != NULL) {
                        if (list->prev) {
                            list->prev->next = list->next;
                            list->next->prev = list->prev;
                        } else {
                            lst_ary[el->bit].head = list->next;
                            lst_ary[el->bit].head->prev = NULL;
                        }
                    } else {
                        if (list->prev) {
                            list->prev->next = list->next;
                        } else {
                            lst_ary[el->bit].head = NULL;
                        }
                    }

                    --lst_ary[el->bit].cnt;

                    free(el);

                    list->bit = list->bit + 1;
                    if (update_list_bs(list) == 0) {
						return 0;
					} else {
						return -1;
					}
                }
            }
        }
        for (list= lst_ary[el->bit].head; list; list= list->next) {
            temp = list;
            if (el->adr > list->adr){
				continue;
			} else {
                if (list->prev) list->prev->next = el;
                else lst_ary[el->bit].head = el;
                el->next = list;
                el->prev = list->prev;
                list->prev = el;
                ++lst_ary[el->bit].cnt;
                return 0;
            }
        }
        temp->next = el;
        el->next = NULL;
        el->prev = temp;
        ++lst_ary[el->bit].cnt;
        return 0;
    } else {
        lst_ary[el->bit].head = el;
        lst_ary[el->bit].head->next = NULL;
        lst_ary[el->bit].head->prev = NULL;
        lst_ary[el->bit].head->adr = el->adr;
        lst_ary[el->bit].head->bud_adr = el->bud_adr;
        lst_ary[el->bit].cnt = 1;
        return 0;
    }

    return 0;
}


void printout(char* policy, int Size, struct request *array)
{

	int i, total = 0;
	int fails = 0;

	
	

	printf("\tMANAGEMENT = %s\t\tSIZE: %d KB\n\n", policy, Size);
	
	for(i=0; i<NUMBER_ENTRIES; i++){
		if(array[i].is_req && array[i].is_allocated){
		  ++total;
		}else{
			if(array[i].is_req){
				printf("Failed Req %d is size %d\n", i, array[i].size);
			}
		}
	}
	
	printf("SERIAL-NUM \t REQUEST \tSIZE \tALLOC-ADDR \tTOTAL-FREE \tLARGEST-PART\n");


    for(i=1; i<NUMBER_ENTRIES; i++){
		
		if(array[i].is_allocated == FALSE){
			/* set to invalid address */
			array[i].base_adr = -1;
			/* keelisttrack of how many fails */
			fails++;
		}

		printf("%4d\t\t",i);
		
		if(array[i].is_req == 1) {
			printf("%6s\t\t", "alloc");
		} else {
			printf("%6s\t\t", "free");
		}

		printf("%6d\t\t", array[i].size);
		printf("%6d\t\t", array[i].base_adr);
		printf("%6d\t\t", array[i].memory_left);
		printf("%6d\n", array[i].largest_chunk);
    }
	/* bad request */ 
	printf("%d Allocations Failed", fails);
	
	
	
	printf("\nTOTAL ALLOCATIONS: %d \n", total);
	
}
