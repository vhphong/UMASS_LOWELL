//
//  Scanner.hpp
//  a2_syntax_error_recovery
//
//  Created by CS Admin on 2/18/18.
//  Copyright © 2018 Viet Tran Quoc Hoang. All rights reserved.
//

#ifndef Scanner_h
#define Scanner_h

#include <iostream>
#include <stdio.h>

using namespace std;

enum token { t_read, t_write, t_if, t_fi, t_do, t_od, t_check,t_id, t_literal,
    t_gets, t_eq_eq, t_not_eq, t_less, t_great, t_less_eq, t_great_eq, t_add,
    t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof};
const string names[] = {"read", "write", "if", "fi", "do", "od",  "check", "id",
    "literal", ":=","==", "<>", "<",">", "<=",">=","+", "-", "*", "/","(", ")"
    ,"eof"};
extern char token_image[100];
extern token scan();
#endif /* Scanner_h */
