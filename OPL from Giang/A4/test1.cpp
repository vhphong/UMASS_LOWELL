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

int main(int argc, char **argv)
{
    Pointer<int> foo(new int(12));
    Pointer<int> tmp((int*)NULL);
    Pointer<int> bar = tmp;
    
    if (foo == 0)
        error("the Foo shouldn't be null!");
    if (bar != 0)
        error("the Bar should be zero null!");
    bar = new int(12);
    if (foo == bar)
        error("Foo and bar are distinct pointers!");
    if (*foo != *bar)
        error("The Foo and bar should have the same value here!");
    
    free(foo);
    free(bar);
    cout << "foo1: OK" << endl;
    return 0;
}
