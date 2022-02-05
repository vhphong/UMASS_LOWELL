//
//  Scanner.cpp
//  a2_syntax_error_recovery
//
//  Created by CS Admin on 2/18/18.
//  Copyright © 2018 Viet Tran Quoc Hoang. All rights reserved.
//
#include <iostream>
#include <vector>
#include <cstring>
#include "Scanner.h"
using namespace std;
char token_image[100];
token scan() {
    static int c = ' ';
    int i = 0;
    while (isspace(c)) {
        c = cin.get();
    }
    if (c == EOF) {
        return t_eof;
    }
    if (isalpha(c)) {
        do {
            token_image[i++] = c;
            c = cin.get();
        } while(isalpha(c) || isdigit(c) || c == '_');
        
        token_image[i] = '\0';
        if (!strcmp(token_image, "read")) return t_read;
        else if (!strcmp(token_image, "write")) return t_write;
        else if (!strcmp(token_image, "if")) return t_if;
        else if (!strcmp(token_image, "fi")) return t_fi;
        else if (!strcmp(token_image, "do")) return t_do;
        else if (!strcmp(token_image, "od")) return t_od;
        else if (!strcmp(token_image, "check")) return t_check;
        else return t_id;
    }
    else if (isdigit(c)) {
        do {
            token_image[i++] = c;
            c = cin.get();
        } while (isdigit(c));
        token_image[i] = '\0';
        return t_literal;
    }
    else switch (c) {
            case ':':
                if ((c = cin.get()) != '=') {
                    cerr << "error\n";
                    exit(1);
                } else {
                    c = cin.get();
                    return t_gets; // :=
                }
            break;
            case '$':
                if ((c = cin.get()) != '$') {
                    cerr << "error\n";
                    exit(1);
                } else {
                    c = cin.get();
                    return t_eof; // $$
                }
            break;
            case '=':
                if ((c = cin.get()) != '=') {
                    cerr << "error\n";
                    exit(1);
                } else {
                    c = cin.get();
                    return t_eq_eq; // ==
                }
            break;
            case '<':
                c = cin.get();
                if (c == '=') {
                    c = cin.get();
                    return t_less_eq; //<=
                } else if (c == '>') {
                    c = cin.get();
                    return t_not_eq; // <>
                } else {
                    return t_less; // <
                }
                break;
            case '>':
                c = cin.get();
                if (c == '=') {
                    c = cin.get();
                    return t_great_eq; //<=
                } else {
                    return t_great; // >
                }
                break;
            case '+': c = cin.get(); return t_add;
            case '-': c = cin.get(); return t_sub;
            case '*': c = cin.get(); return t_mul;
            case '/': c = cin.get(); return t_div;
            case '(': c = cin.get(); return t_lparen;
            case ')': c = cin.get(); return t_rparen;
            default:
                cerr << "error\n";
                exit(1);
    }
}

