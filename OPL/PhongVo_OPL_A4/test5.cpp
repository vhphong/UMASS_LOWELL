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

void proc()
{
    Pointer<int> foo(new int(12));
}

int main(int argc, char **argv)
{
    proc();
    error("please Didn't mess up when leaking memory!");
    
    return 0;
}
