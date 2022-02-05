typedef void* MY_STRING;

enum status { FAILURE, SUCCESS };
typedef enum status Status;

enum boolean {TRUE, FALSE};
typedef enum boolean Boolean;

MY_STRING my_string_init_default(void);

void my_string_destroy(MY_STRING* phMy_string);

MY_STRING my_string_init_c_string(const char* c_string);

int my_string_get_capacity(MY_STRING hMy_string);

int my_string_get_size(MY_STRING hMy_string);

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);

Status my_string_extraction(MY_STRING hMy_string, FILE* fp);

Status my_string_insertion(MY_STRING hMy_string, FILE* fp);
//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: If successful, places the character item at the end of the
// string and returns SUCCESS. If the string does not have enough room and
// cannot resize to accomodate the new character then the operation fails
// and FAILURE is returned. The resize operation will attempt to amortize
// the cost of a resize by making the string capacity somewhat larger than
// it was before (up to 2 times bigger).
Status my_string_push_back(MY_STRING hMy_string, char item);

Status my_string_pop_back(MY_STRING hMy_string);

char* my_string_at(MY_STRING hMy_string, int index);

char* my_string_c_str(MY_STRING hMy_string);

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend);

Boolean my_string_empty(MY_STRING hMy_string);
