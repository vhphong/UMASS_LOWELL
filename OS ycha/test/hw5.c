#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw5.h"

typedef struct request{
	int failed ;
	int serial_number ;
	int request_type ;
	int sizeof_request ;
	int allocation_address ;
	int total_free ;
	int largest_available ;
	int true_size ;
} MY_ARRAY[NUM_ENTRIES] ;

typedef struct list {
	struct list *prev ;
	struct list *next ;
	int seq_num ;
	int start_addr ;
	int adj_addr ;
	int size ;
	int total_free ;
	int free_space ;
} MY_LIST ; 


MY_LIST *allocate_node( void ) ;
int free_node( int seq_num, int free_seq_num ) ;
int allocate_memory( int seq_num ) ;
int best( int seq_num ) ;
void coalesce( void ) ;
char *print_num( int num ) ;
void print_req_array( void ) ;
int buddy_system( int seq_num ) ;

int total_free_space ;
int policy ;
int largest_available ;
int total_allocations = 0 ;

MY_LIST *used_list ;
MY_ARRAY req_array ;

int main( int argc, char *argv[] ) 
{  
	int seq_num ;
	char req_type[20] ;
	int type_value ;
	FILE *fp ;

	policy = atoi( argv[1] ) ;

	if( !(policy == 3 || policy ==  4 || policy == 5 ) ){
		printf(" The first argument (argv[1]) should be:\n1 -- First Fit\n2 -- Best Fit\n3 -- Buddy System\n") ;
		printf("Try again\n") ;
		return 0 ;
	}
	total_free_space = ( atoi(argv[2] ) * 1024 ) ;
	largest_available = total_free_space ;  

	used_list = allocate_node( ) ;
	used_list -> start_addr = 0 ;
	used_list -> adj_addr = -1 ;
	used_list -> size = total_free_space ;

	fp = fopen( argv[3], "r" ) ;
	while( fscanf( fp,"%d %s %d", &seq_num, req_type, &type_value ) != EOF ) {
		if( strcmp( req_type, "alloc" ) == 0 ) {
			req_array[seq_num].serial_number = seq_num ;
			req_array[seq_num].sizeof_request = type_value ;
			req_array[seq_num].request_type = ALLOC ;

			switch (policy){
			case 3:
				allocate_memory( seq_num ) ;
			case 4:
				best(seq_num);
			case 5:
				buddy_system( seq_num ) ;
			}
		}
		else{
			req_array[seq_num].serial_number = seq_num ;
			req_array[seq_num].request_type = FREE ;  
			free_node( seq_num, type_value ) ; 			
		}
	}
	print_req_array();
	fclose( fp ) ;
	return 0 ;
}

void print_req_array( void ) {

	int i = 1 ;


	for( ; i < NUM_ENTRIES; i++ ) {

		if( req_array[i].failed && req_array[i].sizeof_request ) {
			printf("Failed req %d  is size: %d\n", req_array[i].serial_number, req_array[i].sizeof_request ) ; 
		} 
	}

	printf("\n\nTotal Allocations: %d\n", total_allocations) ;
	for(i = 1; i < NUM_ENTRIES; i++ ) {

		printf("Seq %d  Type %s  Size %d  done %s  tot mem %d  lrgest chk %d\n",
			req_array[i].serial_number, print_num(req_array[i].request_type), req_array[i].sizeof_request,
			print_num( req_array[i].failed ),  req_array[i].total_free,  req_array[i].largest_available  ) ;
	}

	return ; 
}

char *print_num( int num ) {

	switch( num ) {
	case 0:
		return "YES" ;
	case 1:
		return "NO" ;
	case 3:
		return "FIRST FIT" ; 
	case 4:
		return "BEST FIT" ;
	case 5: 
		return "BUDDY" ;
	case 6:
		return "alloc" ;
	case 7:
		return "free" ;
	default:
		return "?" ;
	}
}

int free_node( int seq_num, int free_seq_num ) {
	MY_LIST *p_free ;
	p_free = used_list ;

	while( p_free != NULL ) {
		if( free_seq_num == p_free->seq_num ) {
			req_array[seq_num].failed = FALSE ;
			req_array[seq_num].sizeof_request = p_free->size ;
			total_free_space += p_free -> size ;
			req_array[seq_num].total_free = total_free_space ;
			if( largest_available < p_free->size ){
				largest_available = p_free->size ;
			}
			req_array[seq_num].largest_available = largest_available ;

			p_free -> free_space = TRUE ;
			p_free -> seq_num = seq_num ;
			p_free -> total_free = total_free_space ;
			coalesce() ;
			return 0 ;    
		}
		p_free = p_free -> next ;
	}   
	req_array[seq_num].failed = TRUE;
	return 1 ;
}

void coalesce( void ) {

	MY_LIST *p_free ;
	MY_LIST *delete_node ;

	p_free = used_list ;

	while( p_free != NULL ) {


		if( (p_free -> free_space == TRUE) && (p_free -> next != NULL) ) {


			if( (p_free -> next -> free_space == TRUE) && (p_free -> next -> start_addr == 
				(p_free -> start_addr + p_free -> size ) ) ) {

					p_free -> size = p_free -> size + p_free -> next -> size ;

					delete_node = p_free -> next ;

					if( delete_node -> next != NULL ) {
						delete_node -> next -> adj_addr = p_free -> start_addr ;
						delete_node -> next -> prev = p_free ;
					}
					p_free -> next = delete_node -> next ;

					if( p_free -> size > largest_available )
						largest_available = p_free -> size ;


					free( delete_node ) ;


					coalesce() ;
					return ;
			}
		}

		p_free = p_free -> next ;

	}

	return ;
}

int best( int seq_num ) {
	MY_LIST *p_free ;
	MY_LIST *temp ;
	MY_LIST *best_fit = NULL;

	if( req_array[seq_num].sizeof_request <= total_free_space ) {
		p_free = used_list ;
		while( p_free != NULL ) {
			if( p_free->size == req_array[seq_num].sizeof_request ){
				if( p_free->size == largest_available ) {
					largest_available -= req_array[seq_num].sizeof_request ;
					printf("%d\n", largest_available);
				}				
				total_free_space -= p_free->size ;

				p_free->seq_num = req_array[seq_num].serial_number ;
				p_free->total_free = total_free_space ;
				p_free->free_space = FALSE ;

				req_array[seq_num].failed = FALSE ;
				req_array[seq_num].allocation_address = p_free->start_addr ;
				req_array[seq_num].largest_available = largest_available ;
				req_array[seq_num].total_free = total_free_space ;

				++total_allocations ;
				return 0 ;	      
			}
			else if( ( p_free->size > req_array[seq_num].sizeof_request ) && ( p_free->free_space == TRUE ) ){
				best_fit = p_free;
				while ( p_free != NULL ){
					if( (best_fit->size > p_free->size) && (p_free->size >= req_array[seq_num].sizeof_request) ) {
						best_fit = p_free ;						
					}
					if( (p_free->next == NULL) || (p_free->size == total_free_space) ){
						p_free = best_fit;
						temp = allocate_node() ;
						temp -> prev = p_free ;

						if( p_free -> size == largest_available ) {
							largest_available = largest_available - req_array[seq_num].sizeof_request ;
						}
						temp->next = p_free->next ;

						if( p_free -> next != NULL ) {
							p_free -> next -> prev = temp ;
						}
						p_free->next = temp ;
						p_free->free_space = FALSE ;

						temp->start_addr = p_free->start_addr + req_array[seq_num].sizeof_request ;
						temp->size = p_free->size-req_array[seq_num].sizeof_request ;
						temp->adj_addr = p_free->start_addr ;

						p_free -> size = req_array[seq_num].sizeof_request ;
						p_free -> seq_num = req_array[seq_num].serial_number ;
						total_free_space = total_free_space - p_free -> size ;
						p_free -> total_free = total_free_space ;

						req_array[seq_num].failed = FALSE ;
						req_array[seq_num].allocation_address = p_free -> start_addr ;
						req_array[seq_num].largest_available = largest_available ;
						req_array[seq_num].total_free = total_free_space ;


						++total_allocations ;
						return 0 ;
					}
					p_free = p_free->next;
				}
			}
			p_free = p_free -> next ;
		} 
		req_array[seq_num].failed = TRUE ;
		req_array[seq_num].allocation_address = 0 ;
		req_array[seq_num].largest_available = largest_available ;
		req_array[seq_num].total_free = total_free_space ;
		return 1 ;
	}
	else {
		req_array[seq_num].failed = TRUE ;
		req_array[seq_num].allocation_address = 0 ;
		req_array[seq_num].largest_available = largest_available ;
		req_array[seq_num].total_free = total_free_space ;
		return 1 ;
	}
	printf( "Unreachable code\n" ) ;
	return 1 ; 

}

int allocate_memory( int seq_num ) {
	MY_LIST *p_free ;
	MY_LIST *temp ;

	if( req_array[seq_num].sizeof_request <= total_free_space ) {
		p_free = used_list ;
		while( p_free != NULL ) {
			if( p_free->size == req_array[seq_num].sizeof_request ){
				if( p_free->size == largest_available ) {
					largest_available -= req_array[seq_num].sizeof_request ;
				}				
				total_free_space -= p_free->size ;

				p_free->seq_num = req_array[seq_num].serial_number ;
				p_free->total_free = total_free_space ;
				p_free->free_space = FALSE ;

				req_array[seq_num].failed = FALSE ;
				req_array[seq_num].allocation_address = p_free->start_addr ;
				req_array[seq_num].largest_available = largest_available ;
				req_array[seq_num].total_free = total_free_space ;

				++total_allocations ;
				return 0 ;	      
			}
			else if( ( p_free->size > req_array[seq_num].sizeof_request ) && ( p_free->free_space == TRUE ) ){
				temp = allocate_node() ;
				temp -> prev = p_free ;

				if( p_free -> size == largest_available ) {
					largest_available = largest_available - req_array[seq_num].sizeof_request ;
				}
				temp->next = p_free->next ;

				if( p_free -> next != NULL ) {
					p_free -> next -> prev = temp ;
				}
				p_free->next = temp ;
				p_free->free_space = FALSE ;

				temp->start_addr = p_free->start_addr + req_array[seq_num].sizeof_request ;
				temp->size = p_free->size-req_array[seq_num].sizeof_request ;
				temp->adj_addr = p_free->start_addr ;

				p_free -> size = req_array[seq_num].sizeof_request ;
				p_free -> seq_num = req_array[seq_num].serial_number ;
				total_free_space = total_free_space - p_free -> size ;
				p_free -> total_free = total_free_space ;

				req_array[seq_num].failed = FALSE ;
				req_array[seq_num].allocation_address = p_free -> start_addr ;
				req_array[seq_num].largest_available = largest_available ;
				req_array[seq_num].total_free = total_free_space ;


				++total_allocations ;
				return 0 ;
			}
			p_free = p_free -> next ;
		} 
		req_array[seq_num].failed = TRUE ;
		req_array[seq_num].allocation_address = 0 ;
		req_array[seq_num].largest_available = largest_available ;
		req_array[seq_num].total_free = total_free_space ;
		return 1 ;
	}
	else {
		req_array[seq_num].failed = TRUE ;
		req_array[seq_num].allocation_address = 0 ;
		req_array[seq_num].largest_available = largest_available ;
		req_array[seq_num].total_free = total_free_space ;
		return 1 ;
	}
	printf( "Unreachable code\n" ) ;
	return 1 ; 

}

MY_LIST *allocate_node( void ) {

	MY_LIST *temp ;

	if ((temp = (MY_LIST *)malloc( sizeof( MY_LIST ) )) == NULL){
		printf( "malloc error\n" ) ;
		return NULL ;
	}

	temp -> next = NULL ;
	temp -> prev = NULL ;
	temp -> free_space = TRUE;

	return temp ;
}

int buddy_system( int seq_num ) {

	MY_LIST *p_free ;
	MY_LIST *temp ;
	MY_LIST *buddy = NULL;

	int true_size ;
	int power_of_2 = 2 ;


	while( true_size != 0 ) {
		true_size = req_array[seq_num].sizeof_request / power_of_2 ;
		power_of_2 = power_of_2 * 2 ;
	}

	req_array[seq_num].true_size = true_size ;

	if( req_array[seq_num].true_size <= total_free_space ) {

		p_free = used_list ;


		while( p_free != NULL ) {

			if( ( p_free -> size > req_array[seq_num].true_size ) && ( p_free -> free_space == TRUE ) ){

				temp = allocate_node() ;
				temp -> prev = p_free ;

				if( p_free -> size == largest_available ) {
					largest_available = largest_available - req_array[seq_num].sizeof_request ;
				}

				temp -> next = p_free -> next ;

				if( p_free -> next != NULL ) {
					buddy = p_free -> next ;
					p_free -> next -> prev = temp ;
				}

				p_free -> next = temp ;
				p_free -> free_space = FALSE ;

				temp -> start_addr = p_free -> start_addr + req_array[seq_num].sizeof_request ;
				temp -> size = p_free -> size - req_array[seq_num].sizeof_request ;
				temp -> adj_addr = p_free -> start_addr ;

				p_free -> size = req_array[seq_num].sizeof_request ;
				p_free -> seq_num = req_array[seq_num].serial_number ;
				total_free_space = total_free_space - p_free -> size ;
				p_free -> total_free = total_free_space ;
				req_array[seq_num].failed = FALSE ;
				req_array[seq_num].allocation_address = p_free -> start_addr ;
				req_array[seq_num].largest_available = largest_available ;
				req_array[seq_num].total_free = total_free_space ;

				++total_allocations ;
				return 0 ;
			}

			p_free = p_free -> next ;


		} 

		req_array[seq_num].failed = TRUE ;
		req_array[seq_num].allocation_address = 0 ;
		req_array[seq_num].largest_available = 0 ;
		req_array[seq_num].total_free = 0 ;

		return 1 ;
	}
	else {

		req_array[seq_num].failed = TRUE ;
		req_array[seq_num].allocation_address = 0 ;
		req_array[seq_num].largest_available = 0 ;
		req_array[seq_num].total_free = 0 ;

		return 1 ;
	}

	printf( "Unreachable code\n" ) ;
	return 1 ; 


}
