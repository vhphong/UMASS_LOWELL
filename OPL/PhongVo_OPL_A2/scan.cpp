/* Simple ad-hoc scanner for the calculator language.
    Michael L. Scott, 2008-2017.
*/
/* UMass Lowell
Organization of Programming Languages (OPL)
by Phong Vo - Spring 2019
Student ID: 01790283
Assignment 1 */
   
#include<iostream>
#include<ios>
#include <string>
#include <cstring>
#include <cctype>
#include "scan.h"
using namespace std;

char token_image[100];

token scan() {
    static int c = ' ';
        /* next available char; extra (int) width accommodates EOF */
    int i = 0;              /* index into token_image */

    /* skip white space */
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
        } while (isalpha(c) || isdigit(c) || c == '_');
        token_image[i] = '\0';
        if (token_image == "read") 			return t_read;
        else if (token_image == "write")	return t_write;
        else if (token_image == "if") 		return t_if;
        else if (token_image == "fi") 		return t_fi;
        else if (token_image == "do") 		return t_do;
        else if (token_image == "od") 		return t_od;
        else if (token_image == "check") 	return t_check;
        else return t_id;
    }
    else if (isdigit(c)) {
        do {
            token_image[i++] = c;
            c = cin.get();
        } while (isdigit(c));
        token_image[i] = '\0';
        return t_literal;
    } else switch (c) {
        case ':':
            if ((c = cin.get()) != '=') {
                cerr << "error\n";
                exit(1);
            } else {
                c = cin.get();
                return t_gets;
            }
            break;
		case '+': c = cin.get(); return t_add;
        case '-': c = cin.get(); return t_sub;
        case '*': c = cin.get(); return t_mul;
        case '/': c = cin.get(); return t_div;
        case '(': c = cin.get(); return t_lparen;
        case ')': c = cin.get(); return t_rparen;
        case '=':
            if ((c = cin.get()) == '='){
				c = cin.get();
                return t_eq;
            }
			else{
				cerr << "error\n";
                exit(1);
            }
            break;
        case '<':
            c = cin.get();
            if (c == '=') {
                c = cin.get();
                return t_lesseq;
            } else if (c == '>') {
                c = cin.get();
                return t_noteq;
            } else return t_less;
            break;
        case '>':
             c = cin.get();
            if (c == '=') {
                c = cin.get();
                return t_greatereq;
            } else return t_greater;
            break;
		case '$':
            if ((c = cin.get()) != '$') {
                cerr << "error\n";
                exit(1);
            } else {
                c = cin.get();
                return t_eof;
            }
            break;
        default:
            cerr << "error\n";
            exit(1);
    }
}
