/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
    Michael L. Scott, 2008-2017.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "scan.h"

const char* names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen", "eof"};

static token input_token;
static std::string image = "";

void error() {
    std::cout << "syntax error\n";
	exit(1);
}

std::string match (token expected) {
    if (input_token == expected) {
		/*
        std::cout << "matched " << names[input_token];
        if (input_token == t_id || input_token == t_literal) {
            std::cout << ": " << token_image;
		}
        std::cout << "\n";
		*/
		image = get_image();
        input_token = scan ();
    }
    else {
		error ();
	}
	return "";
}

std::string program ();
std::string stmt_list ();
std::string stmt ();
std::string expr ();
std::string expr_tail();
std::string term ();
std::string term_tail ();
std::string factor ();
std::string factor_tail ();
std::string relation();
std::string relation_op();
std::string add_op ();
std::string mul_op ();

// receives input token and outputs program header
std::string program () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_if:
        case t_do:
        case t_check:
        case t_eof:{
            std::string str1 = "(program \n" ;
            str1 += "[";
            str1 += stmt_list ();
            match (t_eof);
            str1 += "]\n";
            return str1+")\n";
        }
        default: error();
    }
}

// list of statements
std::string stmt_list () {
    switch (input_token) {
        case t_id:
        case t_check:
        case t_write:
        case t_read:
        case t_if:
        case t_do:{
			std::string str1 = "";
			str1 += "("+stmt();
			str1 += stmt_list();
			str1 += ")\n";
			return str1;
        }
        case t_eof:
			return "";          /*  epsilon production */
        default:
			return "";
    }
}

// handles statement tokens
std::string stmt () {
    try{
		switch (input_token) {
			case t_id:{
				match (t_id);
				match (t_gets);
				std::string str1 = "(:= (id "+ image+")" + relation();
				str1 += ")";
				return str1;
			}
				case t_read:
				match (t_read);
				match (t_id);
				return "read ("+image+")";
			case t_write:{
				match (t_write);
				std::string str1 = relation();
				return "(write " + str1 + ")";
			}
			case t_if:{
				match(t_if);
				std::string str1 = "(if \n";
				str1 += relation();
				std::string str2  = stmt_list();
				match(t_fi);
				return str1 +"[\n"+ str2 + "])";
			}
			case t_do:{
				match(t_do);
				std::string str1 = "(do\n";
				str1 += stmt_list();
				match(t_od);
				return "["+ str1 + "])";
			}
			case t_check:{
				match(t_check);
				std::string str1 = "";
				str1 += relation();
				return "(check"+str1+")";
			}
			default: 
				error();
		}
    }
	catch(std::string e){
		while (true) {
				switch (input_token)
				{
					/* FIRST (factor) */
					case t_lparen: case t_id: case t_literal:
						factor (); // try again
						return "";
					/* FOLLOW (factor) */
					case t_add: case t_sub: case t_mul: case t_div:
					case t_rparen: case t_read: case t_write:
					case t_eof:
						return "";
					
					default:
						input_token = scan(); // get next token
				}
		}
        return "";
    }
}

// handles expr tokens 
std::string expr () {
    try{
		switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen: {
            std::string str1 = term ();
			std::string str2 = term_tail ();
			if(str2 == "") {
				return str1;
			}
			
			for (int i = 0; i < str2.length(); ++i){
				if(str2[i] == ' '){
					return str2.substr(0,i)+" "+ str1 +" "+ str2.substr(i+1, str2.length() - i);
				}
			}
			return std::string("expr error");
		}
        default: error ();
		}
    }
	catch(std::string e){
		while (true) {
				switch (input_token)
				{
					/* FIRST (factor) */
					case t_lparen: case t_id: case t_literal:
						factor (); // try again
						return "";
					/* FOLLOW (factor) */
					case t_add: case t_sub: case t_mul: case t_div:
					case t_rparen: case t_read: case t_write:
					case t_eof:
						return "";
					
					default:
						input_token = scan(); // get next token
				}
		}
        return "";
    }
}

// handles expr tails (relational operations, etc.)
std::string expr_tail(){
    switch (input_token) {
		case t_equal:
		case t_notequal:
		case t_smaller:
		case t_greater:
		case t_smallerequal:
		case t_greaterequal:{
			std::string str1 = relation_op();
			std::string str2 = expr();
			return str1+" "+str2;
		}
		case t_id:
		case t_read:
		case t_write:
		case t_eof:
			return "";
		default:
			return "";
	}
}

// handles term-related tokens
std::string term () {
	switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen: {
			std::string str1 = factor ();
			std::string str2 = factor_tail ();
			if(str2 == "") {
				return str1;
			}
			
			for (int i = 0; i < str2.length(); ++i){
			  if(str2[i] == ' '){
				return str2.substr(0,i)+" "+ str1 +" "+ str2.substr(i+1, str2.length() - i);
			  }
			}
		}
		default: error();
	}
	error();
}

//handles term tails (add/sub tokens, rparen, etc.)
std::string term_tail () {
	switch (input_token) {
		case t_add:
		case t_sub:{
			std::string str1 = add_op ();
			str1 += " ";
			str1 += term ();
			std::string str2 = term_tail ();
			if(str2 == "") {
				return str1;
			}
			
			for (int i = 0; i < str2.length(); ++i){
			    if(str2[i] == ' '){
			    	return str2.substr(0,i)+" "+ str1 +" "+ str2.substr(i+1, str2.length() - i);
			    }
			}
		}
		case t_rparen:
		case t_id:
		case t_read:
		case t_write:
		case t_eof:
		    return "";          /*  epsilon production */
		default:
		    return "";
	}
	error();
}

// handles factored tokens
std::string factor () {
    switch (input_token) {
		case t_id :{
		    match (t_id);
		    std::string str1 = "(id"+image+")";
		    return str1;
		}
		case t_literal:{
		    match (t_literal);
		    std::string str1 = "(num"+image+")";
		    return str1;
		}
		case t_lparen:{
			match (t_lparen);
			std::string str1 = relation ();
			match (t_rparen);
			return "("+str1+")";
	    }
		default:
			return "";
	}
}

// handles the end of the factor (arithmetic operators, etc.)
std::string factor_tail () {
    switch (input_token) {
		case t_mul:
		case t_div:{
			std::string str1 = mul_op ();
			std::string str2 = factor ();
			str1 += str2;
			str1 += factor_tail ();
			return str1+"";
		}
		case t_add:
		case t_sub:
		case t_rparen:
		case t_id:
		case t_read:
		case t_write:
		case t_eof:
		  return "";
		default:
		  return "";
    }
}

// handles relational operator tokens
std::string relation_op(){
	switch(input_token){
		case t_equal:
			match(t_equal);
			return "== ";
		case t_notequal:
			match(t_notequal);
			return "<> ";
		case t_smaller:
			match(t_smaller);
			return "< ";
		case t_greater:
			match(t_greater);
			return "> ";
		case t_smallerequal:
			match(t_smallerequal);
			return "<= ";
		case t_greaterequal:
			match(t_greaterequal);
			return ">= ";
		default:
			return "";
	}
}

// handles addition operators
std::string add_op () {
	switch (input_token) {
		case t_add:
			match (t_add);
			return "+ ";
		case t_sub:
			match (t_sub);
			return "- ";
		default:
			return "";
	}
}

// handles multiplication operators
std::string mul_op () {
    switch (input_token) {
		case t_mul:
			match (t_mul);
			return "* ";
		case t_div:
			match (t_div);
			return "/ ";
		default:
			return "";
	}
	return "";
}

// handles relations of expressions
std::string relation(){
    try {
        std::string str2 = expr();
        std::string str1 = expr_tail();
		std::string result = "";
	    if(str2 == "") {
			result = str1;
		}
		
		for (int i = 0; i < str2.length(); ++i){
		    if(str2[i] == ' '){
			  result = str2.substr(0,i)+" "+ str1 +" "+ str2.substr(i+1, str2.length() - i);
			}
		}
		return result+"\n";
    }
	catch(std::string e){
		while (true) {
				switch (input_token)
				{
					/* FIRST (factor) */
					case t_lparen: case t_id: case t_literal:
						factor (); // try again
						return "";
					/* FOLLOW (factor) */
					case t_add: case t_sub: case t_mul: case t_div:
					case t_rparen: case t_read: case t_write:
					case t_eof:
						return "";
					
					default:
						input_token = scan(); // get next token
				}
		}
        return " eof";
    }
}

//runs program
int main () {
    input_token = scan ();
    std::string syntax_tree = program ();
	std::cout << syntax_tree << std::endl;
    return 0;
}
