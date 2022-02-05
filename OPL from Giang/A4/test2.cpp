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
    Pointer<int> foo;
    foo = new int(12);
    Pointer<int> bar(foo);
    
    if (bar == 0)
        error("The Bar should not be a null!");
    if (*bar != 12)
        error("The Bar got the wrong value!");
    if (foo != bar)
        error("The test Foo and bar are NOT distinct pointers!");
    if (*foo != *bar)
        error("The test Foo and bar should have the same value here!");
    *foo = 15;
    if (*bar != 15)
        error("The Bar should still match foo!");
    
    free(foo);
    free(bar);
    error("Try to double-delete pointer not flagged!");
    
    return 0;
}
