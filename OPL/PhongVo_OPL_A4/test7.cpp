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

void sub(Pointer<int> &foo)
{
    Pointer<int> bar(foo);
    Pointer<int> bat(bar);
    Pointer<int> qix(bat);
    Pointer<int> glorch(qix);
    
    *glorch = 100;
    if (*foo != 100)
        error("the Linking of the pointers isn't correct!");
    free(glorch);
}

int main(int argc, char **argv)
{
    Pointer<int> foo(new int(0));
    sub(foo);
    *foo = 1000;
    error("Didn't complain about use of dangling pointer testing foo!");
    
    return 0;
}
