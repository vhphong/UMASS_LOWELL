/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
    Michael L. Scott, 2008-2017.
*/
/* Name: Hoang Do
   Student ID: 01521888
   Partner: David Huynh */

#include <iostream>
#include <ios>
#include <stdio.h>
#include "scan.h"
#include <cstdlib>
#include <string>
using namespace std;

const string names[] = {"read", "write", "id", "literal", ":=",
                       "+", "-", "*", "/", "(", ")", "eof", "if",
                       "fi", "do", "od", "check", "==", "<>", "<", ">", "<=",
                       ">="};

static token input_token;
string myString, operandString;
bool relation = false;

void error (token input_token) {
  cout << "syntax error by token " << names[input_token] << endl;
    return;
}

void match (token expected) {
    if (input_token == expected) {
        cout << "matched " << names[input_token];
	if (input_token == t_add ||input_token == t_sub ||
            input_token == t_mul ||input_token == t_div) {
            myString.append("(");
            relation = true;
            myString.append(names[expected] +" ");
        } else if (input_token == t_id || input_token == t_literal) {
            cout << ": " << token_image;
            if (operandString.empty()) {
                 myString.append("\"" + string(token_image) + "\"");
            }
            else {
                 operandString.append("\"" + string(token_image) + "\"");
            }
        }  else if (input_token == t_fi || input_token == t_od ||
            input_token == t_eof || input_token == t_gets) {
        } else {
            myString.append(names[expected] +" ");
        }
        cout << endl;
        input_token = scan ();
    }
    else error (input_token);
}

class SyntaxErrorException : public exception {
    public :
    virtual const char* what() const throw() {
        return "Syntax Error Exception";
    }
};

class Syntax_Error : public SyntaxErrorException {
    private :
    string message;
    public :
    Syntax_Error(const token invalid_token)  {
        message = (string("Invalid " + names[input_token] + "\n"));
    }
    virtual const char* what() const throw() {
        return message.c_str();
    }
};

string program ();
void stmt_list ();
void stmt ();
void expr ();
void expr_tail ();
void term_tail ();
void term ();
void factor_tail ();
void factor ();
void add_op ();
void mul_op ();
void prefixPrint();
void relations ();
void relationOperand();

string program () {
    myString.append("(program\n");
    myString.append("   [");
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
            stmt_list ();
            match (t_eof);
            break;
        default: error (input_token);
      }
    myString.append("   ]\n)\n");
    return myString;
}

void stmt_list () {
  try {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_if:
        case t_do:
        case t_check:
            stmt ();
            stmt_list ();
            break;
        case t_eof:
        case t_fi:
        case t_od:
            break;
        default: error (input_token);
    }
  } catch (Syntax_Error) {
        while (1) {
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

void stmt () {
  try {
    switch (input_token) {
        case t_id:
            myString.append("   (");
            myString.append(names[t_gets] + ' ');
            match (t_id);
            myString.append(" ");
            match (t_gets);
            relations();
            prefixPrint();;
            myString.append(")\n");
            break;
        case t_read:
            myString.append ("(");
            match (t_read);
            match (t_id);
            myString.append(")\n");
            break;
        case t_write:
            myString.append("   ("); 
            match (t_write);
            expr ();
            prefixPrint();
            myString.append(")\n");
            break;
        case t_do:
            myString.append("   (");
            match(t_do);
            myString.append("\n");
	    myString.append("      [");
            stmt_list();
            match(t_od);
            myString.append("   ]\n");
            myString.append("   )\n");
            break;
        case t_check:
            myString.append("   (");
            match(t_check);
            relations();
            prefixPrint();
            myString.append(")\n");
	    myString.append("   ");
            break;
        case t_if:
            myString.append("      (");
            match(t_if);
            myString.append("\n");
            myString.append("      (");
            relations();
            prefixPrint();
            myString.append(")");
            myString.append("\n");
	    myString.append("      [");
            stmt_list();
            myString.append("   ]\n");
            match(t_fi);
            myString.append("   )\n");
            break;
        default: error (input_token);
    }
  } catch  (Syntax_Error) {
        while (1) {
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

void expr () {
  try {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            term ();
            term_tail ();
            break;
        default: error (input_token);
    }
  } catch (Syntax_Error) {
        while (1) {
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
                case t_eq:
                case t_noteq:
                case t_less:
                case t_greater:
                case t_lesseq:
                case t_greatereq:
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
        case t_eq:
        case t_noteq:
        case t_less:
        case t_greater:
        case t_lesseq:
        case t_greatereq:
            relationOperand();
            expr();
            break;
        case t_id:
        case t_eof:
        case t_do:
        case t_od:
        case t_if:
        case t_fi:
            break;
            default: error(input_token);
     }
   }catch (Syntax_Error) {
        while (1) {
            switch (input_token) {
                case t_eq:
                case t_noteq:
                case t_less:
                case t_greater:
                case t_lesseq:
                case t_greatereq:
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

void term_tail () {
  try {
    switch (input_token) {
        case t_add:
        case t_sub:
            add_op ();
            term ();
            term_tail ();
            break;
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
        case t_eq:
        case t_noteq:
        case t_less:
        case t_greater:
        case t_lesseq:
        case t_greatereq:
        case t_do:
        case t_od:
        case t_if:
        case t_fi:
            break;
        default: error (input_token);
    }
  } catch (Syntax_Error) {
        while (1) {
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
                case t_eq:
                case t_noteq:
                case t_less:
                case t_greater:
                case t_lesseq:
                case t_greatereq:
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

void term () {
  try {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            factor ();
            factor_tail ();
            break;
        default: error (input_token);
    }
  }catch (Syntax_Error) {
        while (1) {
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
                case t_eq:
                case t_noteq:
                case t_less:
                case t_greater:
                case t_lesseq:
                case t_greatereq:
                case t_eof:
                    return;
                default:
                    input_token = scan();
            }
        }
    }
}

void factor_tail () {
  try {
    switch (input_token) {
        case t_mul:
        case t_div:
            mul_op ();
            factor ();
            factor_tail ();
            break;
        case t_add:
        case t_sub:
        case t_eof:
        case t_eq:
        case t_noteq:
        case t_less:
        case t_greater:
        case t_lesseq:
        case t_greatereq:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_do:
        case t_od:
        case t_if:
        case t_fi:
            break; 
        default: error (input_token);
    }
  } catch (Syntax_Error) {
        while (1) {
            switch (input_token) {
                case t_mul:
                case t_div:
                    factor_tail();
                    return;
                case t_add:
                case t_sub:
                case t_eq:
                case t_noteq:
                case t_less:
                case t_greater:
                case t_lesseq:
                case t_greatereq:
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

void factor () {
  try {
    switch (input_token) {
        case t_id :
            operandString.append("(id ");
            match (t_id);
            operandString.append(")");
            break;
        case t_literal:
            operandString.append("(num ");
            match (t_literal);
            operandString.append(")");
            break;
        case t_lparen:
            match (t_lparen);
            expr ();
            match (t_rparen);
            break;
        default: error (input_token);
    }
  } catch (Syntax_Error) {
        while (1) {
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
                case t_eq:
                case t_noteq:
                case t_less:
                case t_greater:
                case t_lesseq:
                case t_greatereq:
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

void add_op () {
  try {
    switch (input_token) {
        case t_add:
            match (t_add);
            break;
        case t_sub:
            match (t_sub);
            break;
        default: error (input_token);
    }
  }catch (Syntax_Error) {
        while (1) {
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

void mul_op () {
  try{
    switch (input_token) {
        case t_mul:
            match (t_mul);
            break;
        case t_div:
            match (t_div);
            break;
        default: error (input_token);
    }
  } catch (Syntax_Error) {
        while (1) {
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

void prefixPrint() {
    myString.append(operandString);
    operandString.clear();
    if (relation) {
        myString.append(")");
        relation = false;
    }
}

void relations() {
  try {
     switch (input_token) {
          case t_id:
          case t_literal:
          case t_lparen:
              expr();
              expr_tail();
              break;
          default: error(input_token);
     }
  } catch (Syntax_Error) {
        while (true) {
            switch (input_token) {
                case t_id:
                case t_literal:
                case t_lparen:
                    relations();
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

void relationOperand() {
  try {
     switch (input_token) {
           case t_eq:
               match(t_eq);
               break;
           case t_noteq:
               match(t_noteq);
               break;
           case t_less:
               match(t_less);
               break;
           case t_greater:
               match(t_greater);
               break;
           case t_lesseq:
               match(t_lesseq);
               break;
           case t_greatereq:
               match(t_greatereq);
               break;
           default: error(input_token);
     }
   }catch(Syntax_Error) {
        while (1) {
            switch (input_token) {
                case t_eq:
                case t_noteq:
                case t_less:
                case t_greater:
                case t_lesseq:
                case t_greatereq:
                    relationOperand();
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
int main () {
    input_token = scan ();
    cout <<  program();
    return 0;
}
