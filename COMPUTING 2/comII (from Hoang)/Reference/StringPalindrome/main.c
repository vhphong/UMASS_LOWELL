/**********************************************************************
Program: Palindrome
Author: Viet Tran Quoc Hoang
Date: 3/29/2016
Time spent: 12 hours
Purpose: Get a line from a txt file then determine whether the string is a palinedrome
***********************************************************************/

#include "palindrome.h"
#define DAILY8
int main(int argc, const char * argv[]) {

#ifdef DAILY8
    String_Ptr hString = NULL;
    FILE* fp;
    hString = string_init_default();
    fp = fopen("simple.txt","r");
    while (get_line(hString, fp)) {
        //string_insertion(hString, stdout);
        //printf("\n");
        if(is_palindrome(hString)){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
        reset_size(hString);
    }
    fclose(fp);
    string_destroy(&hString);
    fclose(stdout);
#endif //DAILY8
    

    
    return 0;
}
