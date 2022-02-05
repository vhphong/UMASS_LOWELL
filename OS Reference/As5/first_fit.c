#include "structures.h"

int total_free_space;
int total_allocated = 0;

int allocate_memory(struct request*, int);
int update_list(int, int);
void print_array(int);

int first_fit(int kbnum, char *filename)
{
	int i, seq_num, type_value;
	char type[20];
	FILE *fp;
	struct free_list *p;

	total_free_space = kbnum *1024;

	if (kbnum == 1024){
		printf("FIRST FIT RESULTS FOR 1MB (%4dKB)\n\n", kbnum);
	}else if (kbnum == 512){
		printf("FIRST FIT RESULTS FOR 512KB (%3dKB)\n\n", kbnum);
	}else if (kbnum == 256){
		printf("FIRST FIT RESULTS FOR 256KB (%3dKB)\n\n", kbnum);
	}else{
		printf("\nWRONG ALLOCATION SIZE, PLEASE CHOOSE 1024 512 OR 256\n");
	}

	for(i = 0; i< NUMBER_ENTRIES; i++){
		req_array[i].is_req = FALSE;
		req_array[i].is_allocated = FALSE;
	}

	if((top = malloc(sizeof(struct free_list))) == NULL){
		printf("\nunable to allocate memory\n");
		exit(4);
	}

	top->next = NULL;
	top->previous = &list_head;
	top->block_size = total_free_space;
	top->block_adr = 0;
	top->adjacent_adr = total_free_space;

	list_head.next = top;
	list_head.previous = NULL;
	list_head.block_size = -1;
	list_head.block_adr = -1;
	list_head.adjacent_adr = -1;

	fp = fopen(filename, "r");
	while (fscanf(fp, "%d %s %d", &seq_num, type, &type_value) != EOF){
		if(strcmp(type, "alloc") == 0){
			req_array[seq_num].is_req = TRUE;
			req_array[seq_num].size = type_value;

			allocate_memory(&req_array[seq_num], seq_num);

			req_array[seq_num].elements_on_free_list = 0;
			req_array[seq_num].largest_chunk = 0;
			for(p=list_head.next; p; p=p->next){
				++req_array[seq_num].elements_on_free_list;
				if(p->block_size>req_array[seq_num].largest_chunk){
					req_array[seq_num].largest_chunk=p->block_size;
				}
			}
		}
		else{
			req_array[seq_num].size=req_array[type_value].size;
			req_array[seq_num].base_adr = -1;
			req_array[seq_num].is_allocated=req_array[type_value].is_allocated;

			update_list(type_value, seq_num);

			req_array[seq_num].memory_left=total_free_space;
			req_array[seq_num].elements_on_free_list=0;
			req_array[seq_num].largest_chunk=0;
			for(p=list_head.next; p; p=p->next){
				++req_array[seq_num].elements_on_free_list;
				if(p->block_size>req_array[seq_num].largest_chunk){
					req_array[seq_num].largest_chunk = p->block_size;
				}
			}
		}
	}
	print_array(kbnum);
	fclose(fp);
}

void print_array(int kbnum)
{
	int i;
	printf("\nTOTAL ALLOCATIONS: %d\n", total_allocated);	
	for(i = 1; i < NUMBER_ENTRIES; i++){
		printf("seq %4d type %6s size %7d done  %s  tot mem %7d links %3d lrgst chk %7d\n",
			i, (req_array[i].is_req)?"alloc":"free", req_array[i].size, (req_array[i].is_allocated)?"YES":"NO", req_array[i].memory_left, req_array[i].elements_on_free_list, req_array[i].largest_chunk);
	}
	return;
}

int allocate_memory(struct request *req_array, int seq_num)
{
	struct free_list *p;
	p = list_head.next;

	while (p && p->block_size < req_array->size) {
		p = p->next;
	}
	if(p){
		if (p->block_size == req_array->size) {
			req_array->base_adr = p->block_adr;
			req_array->next_boundary_adr = req_array->base_adr + req_array->size;
			total_free_space = total_free_space - req_array->size;
			req_array->memory_left = total_free_space;
			req_array->is_allocated = TRUE;
			p->previous->next = p->next;
			p->next->previous = p->previous;
			total_allocated++;
		}
		else if (p->block_size > req_array->size) {
			req_array->base_adr = p->block_adr;
			req_array->next_boundary_adr = req_array->base_adr + req_array->size;
			total_free_space = total_free_space - req_array->size;
			req_array->memory_left = total_free_space;
			req_array->is_allocated = TRUE;
			p->block_size = p->block_size - req_array->size;
			p->block_adr = p->block_adr + req_array->size;
			total_allocated++;
		}
		else printf("Failed Req %4d is size %6d\n", seq_num, req_array->size);
	}
	else printf("Failed Req %4d is size %6d\n", seq_num, req_array->size);
}

int update_list(int type_value, int seq_num)
{
	struct free_list *p,