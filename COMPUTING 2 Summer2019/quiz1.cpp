// Quiz 1

//q2
//#include <stdio.h>
//    void pFunction(int*);
//    int main()
//    {
//        int i = 10;
//        pFunction((&i)++);
//    }
//    void pFunction(int *p)
//    {
//        printf("%d\n", *p);
//    }

//q3
//#include <stdio.h>
//void pFunction(int **p);    
//int main()
//{
//  int i = 97, *p = &i;
//  pFunction(&p);
//  printf("%d ", *p);
//  return 0;
//  }
//void pFunction(int **p)
//{
// int j = 2;
// *p = &j;
//  printf("%d ", **p);
//}

//q4
#include <stdio.h>
void pFunction(int *const *p); 
   int main()
    {
        int i = 11;
        int *p = &i;
        pFunction(&p);
        printf("%d ", *p);
    }
    void pFunction(int *const *p)
    {
        int j = 10;
        *p = &j;
        printf("%d ", **p);
    }
