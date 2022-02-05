#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define HEADERS 1
#define NO_HEADERS 0

typedef struct nament {
  char name[26];  
  int addr;      
  struct nament *next;
} SYMTABENTRY;

void add_symbol( char *symbol, int line_number );
void generate_code( int );
void print_first_pass( int );
void append_table( void );
void dump_table( void ); 
int get_sym_val( char *);

SYMTABENTRY *symtab = NULL;
FILE *p1, *p2;
char cstr_12[13];

int main( int argc, char* argv[]){
  int i, start, pc_offset = 0, pc = 0;
  int linum = 0, object_file = 0, dump_tab = 0;
  int line_number, new_pc;
  char instruction[18];
  char symbol[26]; 
  if(argc > 1 && (strcmp(argv[1], "-s") == 0)) dump_tab = linum = 1;
  else if(argc > 1 && (strcmp(argv[1], "-o") == 0)) object_file = 1;
  if((dump_tab==1) | (object_file==1)) start = 2;
  else{start = 1;}
  p1 = fopen("/tmp/daedalus", "w+");
  unlink("/tmp/daedalus");

  for(i = start; i < argc; i++){
    if((p2 = fopen(argv[i], "r")) == NULL){
      printf("Cannot open file named: %s", argv[i]);
      exit(2);
    }
    while(fscanf(p2, "%d %s", &pc, instruction) != EOF){
      if(pc == 4096) break;
      new_pc = pc + pc_offset;
      symbol[0] = '\0';
      if(instruction[0] == 'U'){fscanf(p2, "%s", symbol);}
	  fprintf(p1, " %d %s %s \n", new_pc, instruction, symbol);
    }
    while(fscanf(p2, "%s %d", symbol, &line_number) != EOF) add_symbol(symbol, line_number + pc_offset);
    pc_offset = new_pc + 1;
    fclose(p2);
  }
  if(object_file){
    print_first_pass(NO_HEADERS);
    printf("4096 x\n");
    append_table();
    return 0;
  }
  if(linum) {print_first_pass(HEADERS);}
  generate_code(linum);
  return 0;}

void generate_code(int linum){
  char instruction [18];
  char symbol[26];
  int i, j, pc, difference, mask, _symbol;
  int old_pc = 0;
  rewind(p1);
  while(fscanf(p1, "%d %s", &pc, instruction) != EOF){
    if((difference = pc - old_pc) > 1 ){
      for(j = 1; j < difference; j++){
	printf("1111111111111111 \n");
      }
    }
    old_pc = pc;
    if(instruction[0] != 'U'){
      printf("%s\n", instruction);
    } else { 
      fscanf(p1, "%s", symbol);
      _symbol = get_sym_val(symbol);
      if(_symbol == -1){
        exit(3);
      }
      for(i = 0; i<12; i++){
        cstr_12[i] = '0';
      }  
      cstr_12[12] = '\0';
      mask = 2048;
      for(i = 0; i < 12; i++){
        if(_symbol & mask){
          cstr_12[i] = '1';
        }
        mask >>= 1;
      }
      for(i = 0; i < 12; i++){
        instruction[i + 5] = cstr_12[i];
      }
      printf("%s\n", &instruction[1]);
    }
  }
  return;
}

void print_first_pass(int headers){
  char inbuf[81];
  if(headers != HEADERS){
    rewind(p1);
    while(fgets(inbuf, 80, p1) != NULL){
      printf(" %s", inbuf);
    } 
  } else {
    rewind(p1);
    while(fgets(inbuf, 80, p1) != NULL){
      printf(" %s", inbuf);
    }
  }
}

void add_symbol( char *symbol, int line_number ){
  SYMTABENTRY *_sym;
  _sym = (SYMTABENTRY *) malloc (sizeof (SYMTABENTRY));
  if(symtab != NULL){
    _sym -> next = symtab;
    symtab = _sym;
  } else {
    symtab = _sym;
    _sym -> next = NULL;
  }
  strcpy(_sym -> name, symbol);
  _sym -> addr = line_number;
  return; 
}

void append_table(){
  while(symtab != NULL){
    printf("%s \t\t\t%d\n", symtab -> name, symtab -> addr); 
    symtab = symtab -> next; 
  }
  return;
}

int get_sym_val(char *symbol){
  SYMTABENTRY *rec = symtab;
  int cmp;
  while(rec != NULL){
    cmp = strcmp(rec -> name, symbol);
    if(cmp != 0){
      rec = rec -> next;
    } else {
      return rec -> addr;
    }
  }
  return -1;
}