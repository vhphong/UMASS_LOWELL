typedef void* MY_STRING;

enum status { FAILURE, SUCCESS };
typedef enum status Status;

MY_STRING my_string_init_default(void);

void my_string_destroy(MY_STRING* phMy_string);

MY_STRING my_string_init_c_string(const char* c_string);

int my_string_get_capacity(MY_STRING hMy_string);

int my_string_get_size(MY_STRING hMy_string);

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);

Status my_string_extraction(MY_STRING hMy_string, FILE* fp);

Status my_string_insertion(MY_STRING hMy_string, FILE* fp);
