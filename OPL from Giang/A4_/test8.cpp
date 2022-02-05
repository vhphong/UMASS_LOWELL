//
//
//  Created by Hilton Carboo and Muhammad Muneeb on 4/26/18.
//  Copyright © 2018 BlaqCo. All rights reserved.
//


#include <iostream>
#include <stdlib.h>
#include "tombstones.h"

using namespace std;

void error(const char *text)
{
    cout << "ERROR: " << text << endl;
    exit(-1);
}

void fun(Pointer<int> &foo, int n)
{
    Pointer<int> bar(foo);
    if (n == 0)
        *bar = 100;
    else
    {
        fun(bar, n-1);
        if (n == 10)
        {
            if (*foo != 100)
                error("The Linking of pointers is not correct!");
            free(foo);
        }
    }
}

int main(int argc, char **argv)
{
    Pointer<int> foo(new int(0));
    fun(foo, 10);
    Pointer<int> bar(foo);
    error("Please Didn't complain about use of dangling pointer test foo!");
    
    return 0;
}
