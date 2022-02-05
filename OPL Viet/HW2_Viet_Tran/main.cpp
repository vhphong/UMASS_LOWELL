//
//  main.cpp
//  a2_syntax_error_recovery
//
//  Created by CS Admin on 2/18/18.
//  Copyright © 2018 Viet Tran Quoc Hoang. All rights reserved.
//

#include <iostream>
#include "Scanner.h"
#include "Parser.h"
using namespace std;
static token input_token;
int main(int argc, const char * argv[]) {
    input_token = scan();
    program(input_token);
    cout << "Abstract Syntax Tree output :" << endl;
    cout << ast_string << endl;
    return 0;
}
