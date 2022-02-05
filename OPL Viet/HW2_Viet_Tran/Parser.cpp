//
//  Parser.cpp
//  a2_syntax_error_recovery
//
//  Created by CS Admin on 2/18/18.
//  Copyright © 2018 Viet Tran Quoc Hoang. All rights reserved.
// Used http://hackingoff.com/compilers/predict-first-follow-set
//  and phrase level recovery algo to implement syntax error recovery

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Scanner.h"
#include "Parser.h"
#include <regex>

string operands;
bool is_relation = false;
string ast_string;
static token input_token;
void error(string function_name, token input_token) {
    cout << "Syntax error at " << function_name << " with token "
    << names[input_token] << endl;
    return;
}

void match(token expected){
    if (input_token == expected) {
        cout << "matched " << names[input_token];
        if (input_token == t_add ||input_token == t_sub ||
            input_token == t_mul ||input_token == t_div) {
            ast_string.append("(");
            is_relation = true; // boolean to print the closing bracket
            ast_string.append(names[expected] +" ");
        }
        else if (input_token == t_id || input_token == t_literal) {
            cout << ": " << token_image;
            // check if not a relation, print directly
            if (operands.empty()) {
                ast_string.append("\"" + string(token_image) + "\"");
            } // if a relation, print operators first, store operands for later
            else {
                operands.append("\"" + string(token_image) + "\"");
            }
        }
        else if (input_token == t_fi || input_token == t_od ||
                 input_token == t_eof || input_token == t_gets) {
           // dont print anything for these markers
        }
        else {
            ast_string.append(names[expected] +" ");
        }
        cout << endl;
        input_token = scan();
    } else {
        error(__func__, input_token);
        input_token = expected;
        throw Syntax_Error(input_token);
    }
}

void stmt_list() {
    try {
        switch (input_token) {
            case t_id:
            case t_read:
            case t_write:
            case t_if:
            case t_do:
            case t_check:
                // cout << "predict stmt_list --> stmt stmt_list" << endl;
                stmt();
                stmt_list();
                break;
            case t_eof:
            case t_fi:
            case t_od:
                // cout << "predict stmt_list --> epsilon" << endl;
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_id:
                case t_read:
                case t_write:
                case t_if:
                case t_do:
                case t_check:
                    stmt_list();
                    return;
                case t_fi:
                case t_od:
                case t_eof:
                    return;
                default:
                    input_token = scan();
                    break;
            }
        }
    }
    
}

void stmt() {
    try {
        switch (input_token) {
            case t_id:
                // cout << "predict stmt --> id gets expr" << endl;
                ast_string.append(three_spaces + "(");
                ast_string.append(names[t_gets] + ' ');
                match(t_id);
                ast_string.append(" ");
                match(t_gets);
                relation();
                prefix_print();
                ast_string.append(")\n" );
                break;
            case t_read:
                // cout << "predict stmt --> read id" << endl;
                ast_string.append("(");
                match(t_read);
                match(t_id);
                ast_string.append(")\n");
                break;
            case t_write:
                // cout << "predict stmt --> write expr" << endl;
                ast_string.append(three_spaces + "(");
                match(t_write);
                expr();
                prefix_print();
                ast_string.append(")\n");
                break;
            case t_do:
                // cout << "predict stmt --> do stmt_list" << endl;
                ast_string.append(three_spaces + "(");
                match(t_do);
                ast_string.append("\n" + three_spaces + three_spaces + "[" );
                stmt_list();
                match(t_od);
                ast_string.append(three_spaces + "]\n");
                ast_string.append(three_spaces + ")\n");
                break;
            case t_check:
                // cout << "predict stmt --> check expr" << endl;
                ast_string.append(three_spaces + "(");
                match(t_check);
                relation();
                prefix_print();
                ast_string.append(")\n" + three_spaces);
                break;
            case t_if:
                // cout << "predict stmt --> if relation stmt_list if" << endl;
                ast_string.append(three_spaces + three_spaces+ "(");
                match(t_if);
                ast_string.append("\n");
                ast_string.append(three_spaces + three_spaces +"(");
                relation();
                prefix_print();
                ast_string.append(")");
                ast_string.append("\n" + three_spaces + three_spaces + "[");
                stmt_list();
                ast_string.append(three_spaces + "]\n");
                match(t_fi);
                ast_string.append(three_spaces + ")\n");
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_id:
                case t_read:
                case t_write:
                case t_if:
                case t_do:
                case t_check:
                    stmt();
                    return;
                case t_fi:
                case t_od:
                case t_eof:
                    return;
                default:
                    input_token = scan();
                    break;
            }
        }
    }
}

void prefix_print() {
    // append remaining operands, clear the stack
    ast_string.append(operands);
    operands.clear();
    if (is_relation) {
        // if an operator has been printed, close brackets, clear the bool
        ast_string.append(")");
        is_relation = false;
    }
}

void relation() {
    try {
        switch (input_token) {
            case t_id:
            case t_literal:
            case t_lparen:
                // cout << "predict relation --> expr expr_tail" << endl;
                expr();
                expr_tail();
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_id:
                case t_literal:
                case t_lparen:
                    relation();
                    return;
                case t_rparen:
                case t_read:
                case t_write:
                case t_do:
                case t_od:
                case t_if:
                case t_fi:
                case t_check:
                case t_eof:
                    return;
                default:
                    input_token = scan();
            }
        }
    }
}

void expr() {
    try {
        switch (input_token) {
            case t_id:
            case t_literal:
            case t_lparen:
                // cout << "predict expr --> term term_tail" << endl;
                term();
                term_tail();
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_lparen:
                case t_id:
                case t_literal:
                    term();
                    return;
                case t_add:
                case t_sub:
                case t_div:
                case t_mul:
                case t_eof:
                case t_eq_eq:
                case t_not_eq:
                case t_less:
                case t_great:
                case t_less_eq:
                case t_great_eq:
                case t_rparen:
                case t_if:
                case t_fi:
                case t_do:
                case t_od:
                case t_check:
                    return;
                default:
                    input_token = scan();
            }
        }
    }
    
}

void expr_tail() {
    try {
        switch (input_token) {
            case t_eq_eq:
            case t_not_eq:
            case t_less:
            case t_great:
            case t_less_eq:
            case t_great_eq:
                relational_op();
                expr();
                break;
            case t_id:
            case t_eof:
            case t_do:
            case t_od:
            case t_if:
            case t_fi:
                // cout << "predict term_tail --> epsilon" << endl;
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_eq_eq:
                case t_not_eq:
                case t_less:
                case t_great:
                case t_less_eq:
                case t_great_eq:
                    expr_tail();
                case t_rparen:
                case t_id:
                case t_read:
                case t_write:
                case t_check:
                case t_if:
                case t_fi:
                case t_do:
                case t_od:
                case t_eof:
                    return;
                default:
                    input_token = scan();
            }
        }
    }
    
}

void term() {
    try {
        switch (input_token) {
            case t_id:
            case t_literal:
            case t_lparen:
                // cout << "predict term --> factor factor_tail" << endl;
                factor();
                factor_tail();
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_id:
                case t_literal:
                case t_lparen:
                    term();
                    break;
                case t_add:
                case t_sub:
                case t_read:
                case t_write:
                case t_check:
                case t_do:
                case t_od:
                case t_if:
                case t_fi:
                case t_eq_eq:
                case t_not_eq:
                case t_less:
                case t_great:
                case t_less_eq:
                case t_great_eq:
                case t_eof:
                    return;
                default:
                    input_token = scan();
            }
        }
    }
}

void term_tail() {
    try {
        switch (input_token) {
            case t_add:
            case t_sub:
                // cout << "predict term_tail --> add_op term term_tail" << endl;
                add_op();
                term();
                term_tail();
                break;
            case t_rparen:
            case t_id:
            case t_read:
            case t_write:
            case t_eof:
            case t_eq_eq:
            case t_not_eq:
            case t_less:
            case t_great:
            case t_less_eq:
            case t_great_eq:
            case t_do:
            case t_od:
            case t_if:
            case t_fi:
                // cout << "predict term_tail --> epsilon" << endl;
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_add:
                case t_sub:
                    term_tail();
                    break;
                case t_rparen:
                case t_id:
                case t_read:
                case t_write:
                case t_check:
                case t_eof:
                case t_eq_eq:
                case t_not_eq:
                case t_less:
                case t_great:
                case t_less_eq:
                case t_great_eq:
                case t_if:
                case t_fi:
                case t_do:
                case t_od:
                    return;
                default:
                    input_token = scan();
            }
        }
    }
    
}

void factor() {
    try {
        switch (input_token) {
            case t_id:
                // cout << "predict factor --> id" << endl;
                operands.append(("(id "));
                match(t_id);
                operands.append(") ");
                break;
            case t_literal:
                // cout << "predict factor --> literal" << endl;
                operands.append(("(num "));
                match(t_literal);
                operands.append((") "));
                break;
            case t_lparen:
                // cout << "predict factor --> lparen" << endl;
                match(t_lparen);
                expr();
                match(t_rparen);
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_lparen:
                case t_id:
                case t_literal:
                    factor();
                    return;
                case t_add:
                case t_sub:
                case t_div:
                case t_mul:
                case t_eof:
                case t_eq_eq:
                case t_not_eq:
                case t_less:
                case t_great:
                case t_less_eq:
                case t_great_eq:
                case t_rparen:
                case t_read:
                case t_write:
                case t_check:
                case t_do:
                case t_od:
                case t_if:
                case t_fi:
                default:
                    input_token = scan();
            }
        }
    }
}

void factor_tail() {
    try {
        switch (input_token) {
            case t_mul:
            case t_div:
                // cout << "predict factor_tail --> mul_op factor factor_tail" << endl;
                mul_op();
                factor();
                factor_tail();
                break;
            case t_add:
            case t_sub:
            case t_eof:
            case t_eq_eq:
            case t_not_eq:
            case t_less:
            case t_great:
            case t_less_eq:
            case t_great_eq:
            case t_rparen:
            case t_id:
            case t_read:
            case t_write:
            case t_do:
            case t_od:
            case t_if:
            case t_fi:
                // cout << "predict factor_tail --> epsilon" << endl;
                break;  /*  epsilon production */
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_mul:
                case t_div:
                    factor_tail();
                    return;
                case t_add:
                case t_sub:
                case t_eq_eq:
                case t_not_eq:
                case t_less:
                case t_great:
                case t_less_eq:
                case t_great_eq:
                case t_rparen:
                case t_id:
                case t_read:
                case t_write:
                case t_do:
                case t_od:
                case t_if:
                case t_fi:
                case t_eof:
                    return;
                default:
                    input_token = scan();
            }
        }
    }
}

void relational_op() {
    try {
        switch (input_token) {
            case t_eq_eq:
                // cout << "predict relational_op --> equal equal" << endl;
                match(t_eq_eq);
                break;
            case t_not_eq:
                // cout << "predict relational_op --> not equal" << endl;
                match(t_not_eq);
                break;
            case t_less:
                // cout << "predict relational_op --> less" << endl;
                match(t_less);
                break;
            case t_great:
                // cout << "predict relational_op --> great" << endl;
                match(t_great);
                break;
            case t_less_eq:
                // cout << "predict relational_op --> less than or equal" << endl;
                match(t_less_eq);
                break;
            case t_great_eq:
                // cout << "predict relational_op --> greater than or equal" << endl;
                match(t_great_eq);
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_eq_eq:
                case t_not_eq:
                case t_less:
                case t_great:
                case t_less_eq:
                case t_great_eq:
                    relational_op();
                    return;
                case t_lparen:
                case t_id:
                case t_literal:
                    return;
                default:
                    input_token = scan();
            }
        }
    }
    
}

void add_op() {
    try {
        switch (input_token) {
            case t_add:
                // cout << "predict add_op --> add" << endl;
                match(t_add);
                break;
            case t_sub:
                // cout << "predict mul_op --> sub" << endl;
                match(t_sub);
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_add:
                case t_sub:
                    add_op();
                    return;
                case t_lparen:
                case t_id:
                case t_literal:
                    return;
                default:
                    input_token = scan();
            }
        }
    }
}


void mul_op() {
    try {
        switch (input_token) {
            case t_mul:
                // cout << "predict mul_op --> mul" << endl;
                match(t_mul);
                break;
            case t_div:
                // cout << "predict mul_op --> div" << endl;
                match(t_div);
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }

    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_mul:
                case t_div:
                    mul_op();
                    return;
                case t_lparen:
                case t_id:
                case t_literal:
                    return;
                default:
                    input_token = scan();
                    break;
            }
        }
    }
}

void program(token input) {
    ast_string.append("(program\n");
    ast_string.append(three_spaces + "[");
    input_token = input;
    try {
        switch (input_token) {
            case t_id:
            case t_read:
            case t_write:
            case t_eof:
            case t_if:
            case t_fi:
            case t_do:
            case t_od:
            case t_check:
                // cout << "predict program --> stmt_list eof" << endl;
                stmt_list();
                match(t_eof);
                break;
            default:
                error(__func__, input_token);
                throw Syntax_Error(input_token);
                break;
        }
    } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_eof:
                    return;
                default:
                    input_token = scan();
                    break;
            }
        }
        
    }
    
    ast_string.append(three_spaces + "]\n)");
}

