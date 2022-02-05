//
//  Parser.hpp
//  a2_syntax_error_recovery
//
//  Created by CS Admin on 2/18/18.
//  Copyright © 2018 Viet Tran Quoc Hoang. All rights reserved.
//

#ifndef Parser_h
#define Parser_h

#include <stdio.h>
#include "Scanner.h"
extern string ast_string;
const string three_spaces(3,' ');
void program(token);
void error(string function_name, token input_token);
void match(token expected);
void stmt_list();
void relation();
void expr();
void expr_tail();
void stmt();
void term();
void term_tail();
void factor();
void factor_tail();
void relational_op();
void add_op();
void mul_op();
void prefix_print();
class SyntaxErrorException : public exception {
    public :
    virtual const char* what() const throw() {
        return "Syntax Error Exception";
    }
};
class Syntax_Error : public SyntaxErrorException {
    private :
    token input_token;
    string message;
    public :
    Syntax_Error(const token invalid_token): input_token(invalid_token) {
        message = (string("Invalid " + names[input_token] + "\n"));
    }
    virtual const char* what() const throw() {
        return message.c_str();
    }
};
#endif /* Parser_h */
