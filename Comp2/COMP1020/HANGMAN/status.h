

#ifndef status_h
#define status_h

enum status { FAILURE,SUCCESS };
typedef enum status Status;
enum boolean {FALSE,TRUE};
typedef enum boolean Boolean;

typedef void* Item;
typedef Item* Item_ptr;
#endif /* status_h */
