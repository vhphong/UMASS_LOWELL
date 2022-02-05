/* Assignment 5: Unility.c */

#include "utility.h"
#include "math.h"
int update_list(int index){

  /* free_lists to hold objects*/
  struct free_list* freeList;
  struct free_list* newBlock;  
  struct free_list* combineBlock;
 
  if(req_array[index].is_allocated == FALSE){
    return 0;
  }

  /* block is done */
  req_array[index].is_allocated = DONE;
  total_free += req_array[index].size;

  /* look at all the blocks in the free list */
  for(freeList = list_head.next; freeList; freeList = freeList -> next){

    /* out of range */
    if(req_array[index].base_adr > freeList -> block_adr) {
      /* skip */
      continue;
    }

    /* create a block to store */
    newBlock = malloc(sizeof(struct free_list));    
    newBlock -> block_size = req_array[index].size;
    newBlock -> block_adr = req_array[index].base_adr;
    newBlock -> adjacent_adr = newBlock -> block_adr + newBlock -> block_size;

    newBlock->next = freeList;
    freeList -> previous -> next = newBlock;
    newBlock -> previous = freeList -> previous;
    freeList -> previous = newBlock;
    
    /* Check to see if we can combine with next */
    if(newBlock -> adjacent_adr == newBlock -> next -> block_adr) {
      combineBlock = newBlock -> next;
      newBlock -> block_size = newBlock -> block_size + newBlock -> next -> block_size;
      newBlock -> adjacent_adr = newBlock -> next -> adjacent_adr;
      newBlock -> next = newBlock -> next -> next;
      
      if(newBlock -> next){
        newBlock -> next -> previous = newBlock;
      }

      free(combineBlock);

    }

    /* with previous */ 
    newBlock = newBlock -> previous;
    if((newBlock != NULL) && (newBlock -> adjacent_adr != 0)) {
      if(newBlock -> adjacent_adr == newBlock -> next -> block_adr) {
        combineBlock = newBlock->next;
        newBlock -> block_size = newBlock -> block_size + newBlock -> next -> block_size;
        newBlock -> adjacent_adr = newBlock -> next -> adjacent_adr;
        newBlock -> next = newBlock -> next -> next;

        if(newBlock -> next){
          newBlock ->next -> previous = newBlock;
	}

        free(combineBlock);

      }
    }

    return 0;

  }
}

void print_results(char* policy, int memorySize, struct request* req){

  /* Headers */
  printf("POLICY: %s\tMEMORY SIZE: %d\n\n", policy, memorySize);
  printf("\nNUMBER \tSEQUENCE \tSIZE \tADR \tMEMORY LEFT \tLARGEST CHUNK\n");

  int i = 1;
  int fails = 0;
  char operation[6];

  for(i; i < NUMBER_ENTRIES; i++){

    if(req[i].is_allocated == FALSE){
      /* set to invalid address */
      req[i].base_adr = -1;

      /* keep track of how many fails */
      fails++;
    }

    /* operation type */
    if(req[i].is_req == 1){
      sprintf(operation, "%s", "alloc");
    } else {
      sprintf(operation, "%s", "free");
    }

    /* data about the request */ 
    printf("\t%d \t%s \t\t%d \t%d \t\t%d \t\t%d\n", i, operation, req[i].size,
	   req[i].base_adr, req[i].memory_left, req[i].largest_chunk);

  }

  /* bad request */ 
  printf("%d Allocations Failed", fails);

}


struct lel *find_el(int bit){
                struct lel *rtn;
                int mask;

                mask = pow(2,bit);
                if(bit > 20)return NULL;
                if(lst_ary[bit].cnt > 0){
                  --lst_ary[bit].cnt;
                  rtn = lst_ary[bit].head;
                  lst_ary[bit].head = lst_ary[bit].head->next;
                  if(lst_ary[bit].head)lst_ary[bit].head->prev = NULL;
                  return rtn;
                }else{
                  rtn = find_el(bit + 1);
                  if(rtn){
                    lst_ary[bit].head = malloc(sizeof(struct lel));
		    ++mal_cnt;
                    lst_ary[bit].head->next = NULL;
                    lst_ary[bit].head->prev = NULL;
                    lst_ary[bit].head->adr = (rtn->adr) + mask;
                    lst_ary[bit].head->bit = bit;
		    lst_ary[bit].head->bud_adr = rtn->adr;
		    lst_ary[bit].cnt = 1;

		    rtn->bud_adr = (rtn->adr) + mask;

                    rtn->bit = bit;
                    rtn->next = NULL;
                    rtn->prev = NULL;
                 }
                 return rtn;
               }
}

int update_lists(struct lel *el){
        struct lel *p, *q;
	int nmask;

        if(lst_ary[el->bit].head){
	  nmask = pow(2, (el->bit)+1);
          for(p=lst_ary[el->bit].head; p; p=p->next){
                if(p->adr == el->bud_adr || p->bud_adr == el->adr){
                  if(p->adr > el->adr){
			if((el->adr) & nmask){
                          el->bud_adr = (el->adr) & (~nmask);
			}else{
			  el->bud_adr = (el->adr) | nmask;
			}
			if(p->next){
                          if(p->prev){
                                p->prev->next = p->next;
				p->next->prev = p->prev;
                          }else{
                                lst_ary[el->bit].head  = p->next;
			     	lst_ary[el->bit].head->prev = NULL;
                          }
                        }else{
                          if(p->prev){
                                p->prev->next = p->next;
                          }else{
                                lst_ary[el->bit].head =NULL;
                          }
                        }
                        --lst_ary[el->bit].cnt;

                        free(p);
                        el->bit = el->bit+1;
                        if(update_lists(el) == 0)return 0;
                        else return -1;
                  }else{
			if((p->adr) & nmask){
                          p->bud_adr = (p->adr) & (~nmask);
			}else{
			  p->bud_adr = (p->adr) | nmask;
			}
			if(p->next){
			  if(p->prev){
				p->prev->next = p->next;
				p->next->prev = p->prev;
			  }else{
				lst_ary[el->bit].head  = p->next;
			     	lst_ary[el->bit].head->prev = NULL;
			  }
			}else{
			  if(p->prev){
                                p->prev->next = p->next;
			  }else{
			  	lst_ary[el->bit].head =NULL;
			  }
			}
			--lst_ary[el->bit].cnt;

                        free(el);
                        p->bit = p->bit+1;
                        if(update_lists(p)== 0)return 0;
                        else return -1;
                 }
                }
          }
          for(p=lst_ary[el->bit].head; p; p=p->next){
                q = p;
                if(el->adr > p->adr)continue;
                else{
                  if(p->prev)p->prev->next = el;
                  else lst_ary[el->bit].head = el;
                  el->next = p;
                  el->prev = p->prev;
                  p->prev = el;
                  ++lst_ary[el->bit].cnt;
                  return 0;
                }
          }
          q->next = el;
          el->next = NULL;
          el->prev = q;
          ++lst_ary[el->bit].cnt;
          return 0;
        }else{
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
