/* Complete recursive descent parser for the calculator language.
 Builds on figure 2.16.  Prints a trace of productions predicted and
 tokens matched.  Does no error recovery: prints "syntax error" and
 dies on invalid input.
 Michael L. Scott, 2008-2017.
 */

// Authors: Muhammad Muneeb and Hylton Carboo

#include <iostream>
#include <ios>
#include "scan.h"
#include <cstdlib>
#include <string>

using namespace std;

const char* names[] = {"read", "write", "id", "literal", "gets",
    "add", "sub", "mul", "div", "lparen", "rparen", "eof", "$$"};

// token nanmes to print
const string token_names[] = {"\"check\"", "\"read\"", "\"write\"", "id", "literal", "\"gets\"", "\"if\"",
                              "\"fi\"", "\"do\"", "\"(\"", "\")\"", "\"eof\"", "\"eps\"", "\"od\"", "\"==\"", "\"<>\"", "\"<\"", "\">\"",
                              "\"<=\"", "\">=\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"$$\""};

static string input_image = "";
static token input_token;
static int has_Error = 0;
static int tab_Number = 0;

string factor_tail();
string factor();
string relation_op();
string add_op();
string mul_op();
string check_relation();
string program();
string stmt_list();
string stmt();
string expr();
string expr_tail();
string term_tail();
string term();

// follow sets to check expression and relation
static token r_follow[] = {t_id, t_read, t_write, t_if, t_do, t_check, t_eof, t_fi, t_rparen};
static token s_follow[] = {t_id, t_read, t_write, t_if, t_do, t_check, t_eof};
static token e_follow[] = {t_id, t_read, t_write, t_if, t_do, t_check, t_eof, t_fi, t_rparen,
    t_equal, t_notequal, t_smaller, t_greater, t_smallerequal, t_greaterequal};

// This is the function that prints funtion to print postIndent
string postIndent(string str, int tab)
{
    int i = 0;
    while(i <= tab)
    {
        str += " ";
        i++;
    }
    return str;
}

// This is the function that prints funtion to print preFix
string prefix(string str, string end_tail)
{
    if(end_tail == "")
    {
        return str;
    }
    for (int i = 0; i < end_tail.length(); ++i)
    {
        if(end_tail[i] == ' ')
        {
            return end_tail.substr(0,i)+" "+ str +" "+ end_tail.substr(i+1, end_tail.length() - i);
        }
    }
    return "PreFix Error";
}

// This is the function that prints funiton for syntax error
void error ()
{
    cout << "syntax error\n";
    exit (1);
}

// This is a function that checks to see if a set contains the token
int contains(token _t, token set[])
{
    int i = 0;
    while(set[i])
    {
        if (_t == set[i++])
        {
            return 1;
        }
    }
    return 0;
}

// This fucntion checks to see if the expected token is matched
string match (token expected)
{
    if (input_token == expected)
    {
        input_image = getImage();
        input_token = scan ();
    }
    else
    {
        input_image = getImage();
        cout << "A token " << names[input_token] << ": you meant " << token_names[expected] << "?"<< endl;
        throw string("match");
    }
    return "";
}

// This is the program funtion with switch cases that act once a case is matched
string program ()
{
    // The switch statments below compare input tokens
    switch (input_token) 
    {
        case t_id:
        case t_read:
        case t_write:
        case t_if:
        case t_do:
        case t_check:
        case t_eof:
        {
            tab_Number++;
            // This is the string at the start of the program
            string first_str = "(program \n";
            first_str = postIndent(first_str, tab_Number);
            first_str += "[";
            first_str += stmt_list ();
            match (t_eof);
            first_str = postIndent(first_str, tab_Number);
            first_str += "]\n";
            if(has_Error)
            {
                return "";
            }
            return first_str+")\n";
        }
        default:
            return "";
    }
}

// This is the statement list funtion for list statment swith cases
string stmt_list ()
{
    // switch statments to compare input token
    switch (input_token)
    {
        case t_id:
        case t_check:
        case t_write:
        case t_read:
        case t_if:
            // This is the case for do in our laanguage
        case t_do:
        {
            string first_str = "";
            first_str = postIndent(first_str, tab_Number);
            first_str += "(" + stmt();
            first_str += stmt_list();
            first_str = postIndent(first_str, tab_Number);
            first_str += ")\n";
            tab_Number--;
            return first_str;
        }
        case t_eof:
            tab_Number--;
            return "\n";
        default:
            tab_Number--;
            return "\n";
    }
}

// statment function with switch cases
string stmt () {
    tab_Number++;
    try{
        // check if input token is equal to the id
        switch (input_token) 
        {
            case t_id:
            {
                match (t_id);
                match (t_gets);
                string first_str = "( := (id "+ input_image+")" + check_relation();
                first_str = postIndent(first_str, tab_Number);
                first_str += ")";
                tab_Number--;
                return first_str;
            }
                // check if input token is equal to the readtoken
            case t_read:
                match (t_read);
                match (t_id);
                tab_Number--;
                return "read (id"+input_image+" )\n";
                // check if input token is equal to the writetoken
            case t_write:
            {
                match (t_write);
                string first_str = check_relation();
                first_str = postIndent(first_str, tab_Number);
                tab_Number--;
                return "(write " + first_str + ")\n";
            }
                // check if input token is equal to the if
            case t_if:
            {
                match(t_if);
                string first_str = "(if \n";
                first_str = postIndent(first_str, tab_Number);
                first_str += check_relation();
                first_str = postIndent(first_str, tab_Number);
                string second_str  = stmt_list();
                second_str = postIndent(second_str, tab_Number);
                match(t_fi);
                tab_Number--;
                return first_str +"[\n"+ second_str + "])\n";
            }
                // check if input token is equal to the do
            case t_do:
            {
                match(t_do);
                string first_str = "(do\n";
                first_str += stmt_list();
                first_str = postIndent(first_str, tab_Number);
                match(t_od);
                tab_Number--;
                return "["+ first_str + "])\n";
            }
                // check if input token is equal to the check token
            case t_check:
            {
                match(t_check);
                string first_str = "";
                first_str = postIndent(first_str, tab_Number);
                first_str += check_relation();
                first_str = postIndent(first_str, tab_Number);
                tab_Number--;
                // return check with the string
                return "(check" + first_str + ")\n";
            }
                // default error
            default:
                error();
                tab_Number--;
                return "";
        }
    }
    catch(string e)
    {
        has_Error = 1;
        if(e == "match") cout <<"This token is not expected " << token_names[input_token] << " in a statement" <<endl;
        // error massage for the exception
        else cout << " This token is not expected " << token_names[input_token] << " in " << e << endl;
        // error massage for the exception
        cout << " Skipped: " << token_names[input_token] << endl;
        input_token = scan();
        while(!contains(input_token, s_follow) && input_token != t_eof)
        {
            cout << "It Skipped: " << token_names[input_token] << endl;
            input_token = scan();
        }
        if(contains(input_token, s_follow)){
            has_Error = 1;
            return "<error>\n";
        }
        return "";
    }
}

// This is the expr funtion with try catch statements to catch the errors
string expr () {
    tab_Number++;
    try
    {
        string first_str = term ();
        string second_str = term_tail ();
        tab_Number--;
        return prefix(first_str, second_str);
    }
    catch(string e)
    {
        has_Error = 1;
        if(e == "match") cout <<" Not excepting this " << token_names[input_token] << " in a expression" <<endl;
        // error massage for the exception
        else cout << " Token is Not expecting the" << token_names[input_token] << " in a" << e << endl;
        // error massage for the exception
        cout << " It Skipped>> " << token_names[input_token] << endl;
        input_token = scan();
        while(!contains(input_token, e_follow) && input_token != t_eof)
        {
            cout << " It Skipped>> " << token_names[input_token] << endl;
            input_token = scan();
        }
        if(contains(input_token, e_follow))
        {
            has_Error = 1;
            tab_Number--;
            return "<error>\n";
        }
        return "";
    }
    return "";
}


// This is the expression tail funtion with switch cases
string expr_tail(){
    tab_Number++;
    switch (input_token) 
    {
        case t_add:
        case t_sub:
        case t_equal:
        case t_notequal:
        case t_smaller:
        case t_greater:
        case t_smallerequal:
        // check if input token is greaterequal
        case t_greaterequal:
        {
            string first_str = relation_op();
            string second_str = expr();
            tab_Number--;
            return first_str + " " + second_str;
        }
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            tab_Number--;
            return "";
        default:
            tab_Number--;
            return "";
    }
}

// term tail funtion and switch cases
string term_tail ()
{
    tab_Number++;
    switch (input_token)
    {
        case t_add:
            // check if input token is equal to the subtract token
        case t_sub:
        {
            string first_str = add_op ();
            first_str = first_str + " ";
            first_str = first_str + term ();
            string second_str = term_tail ();
            tab_Number--;
            // return prefix with both strings
            return prefix(first_str, second_str);
        }
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            tab_Number--;
            return "";
        default:
            return "";
    }
}


// term funtion with try and ctach
string term () 
{
    try
    {
        tab_Number++;
        // set first string equal to factor
        string first_str = factor ();
        // set second string equal to tail factor
        string second_str = factor_tail ();
        tab_Number--;
        // return prefix with both strings
        return prefix(first_str, second_str);
    }
    catch(string e)
    {
        throw string("term");
        tab_Number--;
    }
    return "";
}


// factor tail funtion to check division
string factor_tail ()
{
    tab_Number++;
    switch (input_token)
    {
        case t_mul:
        // This checks if input token is equal to the division token
        case t_div:
        {
            string first_str = mul_op ();
            string second_str = factor ();
            first_str += second_str;
            first_str += factor_tail ();
            tab_Number--;
            return first_str + "";
        }
        case t_add:
        case t_sub:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            tab_Number--;
            return "";
        default:
            return "";
    }
}

// factor fuuntion with switch cases to check id and number
string factor () 
{
    tab_Number++;
    // check if input token is equal to the id token
    switch (input_token)
    {
        case t_id :
        {
            match (t_id);
            tab_Number--;
            string str1 = "(id"+input_image+")";
            return str1;
        }
            // check if input token is equal to the literal token
        case t_literal:
        {
            match (t_literal);
            tab_Number--;
            string str1 = "(num"+input_image+")";
            return str1;
        }
            // check if input token is equal to the left parenthesis
        case t_lparen:
        {
            match (t_lparen);
            string str1 = check_relation ();
            match (t_rparen);
            tab_Number--;
            return "(" + str1 + ")";
        }
        default:
            // throw exceptiom
            throw string("factor");
            tab_Number--;
            return "";
    }
}

// new relation operation used if statements to match
string relation_op()
{
    tab_Number++;
    // check if input token is equal to the equal = token
    if(input_token == t_equal)
    {
        match(t_equal);
        tab_Number--;
        return "== ";
    }
    // check if input token is not equal to equal token
    else if (input_token == t_notequal)
    {
        match(t_notequal);
        tab_Number--;
        return "<> ";
    }
    // check if input token is less than token
    else if (input_token == t_smaller)
    {
        match(t_smaller);
        tab_Number--;
        return "< ";
    }
    // check if input token is greater than token
    else if (input_token == t_greater)
    {
        match(t_greater);
        tab_Number--;
        return "> ";
    }
    // check if input token is smallerequal token
    else if (input_token == t_smallerequal)
    {
        match(t_smallerequal);
        tab_Number--;
        return "<= ";
    }
    // check if input token is greaterequal token
    else if (input_token == t_greaterequal)
    {
        match(t_greaterequal);
        tab_Number--;
        return ">= ";
    }
    else
    {
        throw string("The Relation Operation");
        tab_Number--;
        return "";
    }
}

// addition operator funtion
string add_op ()
{
    tab_Number++;
    // check if input token is equal to addition operator
    if (input_token == t_add)
    {
        match (t_add);
        tab_Number--;
        return "+ ";
    }
    // check if input token is equal to minus operator
    else if (input_token ==  t_sub)
    {
        match (t_sub);
        tab_Number--;
        return "- ";
    }
    else
    {
        throw string("The arirhematic operator");
        tab_Number--;
        return "";
    }
}

// Multiplication operator funtion
string mul_op ()
{
    tab_Number++;
    // This checks to see if input token is equal to multiplication operator
    if (input_token == t_mul)
    {
        match (t_mul);
        tab_Number--;
        return "* ";
    }
    // check if input token is equal to division operator
    else if(input_token == t_div)
    {
        match (t_div);
        tab_Number--;
        return "/ ";
    }
    else 
    {
        tab_Number--;
        throw string("The operator for aritematic");
        return "";
    }
}

// This is the relation funtion that does the eqal and all them signs
string check_relation()
{
    try
    {
        tab_Number++;
        string second_str = expr();
        string first_str = expr_tail();
        tab_Number--;
        return "(" + prefix(second_str, first_str) + ")\n";
    }
    catch(string e)
    {
        has_Error = 1;
        if(e == "match") cout <<" This token is not expected " << token_names[input_token] << " in Relation" <<endl;
        // error massage for the exception
        else cout << " This token is not expected " << token_names[input_token] << " in " << e << endl;
        // error massage for the exception
        cout << "It skipped: " << token_names[input_token] << endl;
        input_token = scan();
        while(!contains(input_token, r_follow) && input_token != t_eof)
        {
            cout << "It skipped: " << token_names[input_token] << endl;
            input_token = scan();
            cout << input_token<<endl;
        }
        if(contains(input_token, r_follow))
        {
            has_Error = 1;
            tab_Number--;
            return "(error)\n";
        }
        tab_Number--;
        return " eof";
    }
}

// main funtion
int main () {
    input_token = scan ();
    cout << program ();
    return 0;
}


