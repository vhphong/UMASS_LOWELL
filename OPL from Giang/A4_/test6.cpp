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

Pointer<int> &rec(int n, Pointer<int> foo)
{
    static Pointer<int> result(new int(*foo));
    if (0 == n)
        return result;
    result = (Pointer<int>&)(rec(n-1, foo));
    *result += 1;
    return result;
}

Pointer<int> &recref(int n, Pointer<int> &foo)
{
    if (0 == n)
        return foo;
    *foo += 1;
    return rec(n-1, foo);
}

void proc()
{
    Pointer<int> foo(new int(0));
    Pointer<int> bar(rec(100, foo));
    
    if (*bar != 100 || *foo != 0)
        error("test or bar incorrect after rec()!");
    
    foo = recref(100, bar);
    if (*foo != 200)
        error("test is wrong after recref()!");
    if (foo != bar)
        error("test not an alias for bar after recref()!");
    free(foo);
}

int main(int argc, char **argv)
{
    proc();
    error("please Didn't mess up when leaking memory!");
    
    return 0;
}
