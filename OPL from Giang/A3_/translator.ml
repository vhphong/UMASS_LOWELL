(*******************************************************************
   This file ("translator.ml") provides stub functions for the extra
   code you need to write for this assignment.
   
   There are two major stub functions in "translator.ml":
   "ast_ize_P" (which transforms a parse tree for a program into
                an abstract syntax tree[AST]); and
   "translate" (which translates an AST into an equivalent C program).
   
   You are also being provided with a file called "parser.ml" which
   contains working code to produce a parse tree for a program.
   Everything in the file "parser.ml" is complete and usable as-is.
  
   The major entry point for the parser provided in "parser.ml" is
   a function called "parse" invoked with two parameters: A parse table,
   and a string containing a calculator language program.
   
   The file "parser.ml" constructs two example parse tables:
   "cg_parse_table" (for the original calculator language grammar), and
   "ecg_parse_table" (for the extended calculator language grammar).
   
   Here are two parser examples which will work as-is:
   
      parse cg_parse_table sum_ave_prog;;
      parse ecg_parse_table primes_prog;;
		
   "sum_ave_prog" and "primes_prog" are provided at the end of this
   file (as strings). "sum_ave_prog" uses the original calculator
   language grammar, while "primes_prog" uses the extended calculator
   language grammar.
   
   When complete, your translator code should work when invoked as
   follows:
   
      print_string
        (snd
          (translate
            (ast_ize_P
              (parse ecg_parse_table primes_prog)
            )
          )
        );;
	
   The result of this invocation should be a C program on standard
   output, which can be compiled and run to produce the first N primes
   (where N is a number typed by the user).
 *******************************************************************)


 #use "parser.ml";;


(*******************************************************************
   Declarations and functions to transform a parse tree into an
   abstract syntax tree (AST)
 *******************************************************************)
 
type ast_sl = ast_s list
and ast_s =
    | AST_error
    | AST_assign of (string * ast_e)
    | AST_read of string
    | AST_write of ast_e
    | AST_if of (ast_e * ast_sl)
    | AST_do of ast_sl
    | AST_check of ast_e
and ast_e =
    | AST_binop of (string * ast_e * ast_e)
    | AST_id of string
    | AST_num of string;;

	
let rec ast_ize_P (p:parse_tree) : ast_sl =
  match p with
  | PT_nt ("P", [sl; PT_term "$$"]) -> ast_ize_SL sl
  | _ -> raise (Failure "malformed parse tree in ast_ize_SL")

and ast_ize_SL (sl:parse_tree) : ast_sl =
  match sl with
  | PT_nt ("SL", []) -> []
  | PT_nt ("SL", [h; t]) -> ast_ize_S h::ast_ize_SL t
  | _ -> raise (Failure "malformed parse tree in ast_ize_SL")

and ast_ize_S (s:parse_tree) : ast_s =
  match s with
  | PT_nt ("S", [PT_id lhs; PT_term ":="; expr])
        -> AST_assign (lhs, (ast_ize_expr expr))
  | PT_nt ("S", [PT_term "read"; PT_id id])
        -> AST_read(id)
  | PT_nt ("S", [PT_term "write"; expr])
        -> AST_write(ast_ize_expr expr)
  | PT_nt ("S", [PT_term "if"; expr; sl; PT_term "fi"])
        -> AST_if(ast_ize_expr expr, ast_ize_SL sl)
  | PT_nt ("S", [PT_term "do"; sl; PT_term "od"])
        -> AST_do(ast_ize_SL sl)
  | PT_nt ("S", [PT_term "check"; expr])
        -> AST_check(ast_ize_expr expr)
  | _ -> raise (Failure "malformed parse tree in ast_ize_S")

and ast_ize_expr (expr:parse_tree) : ast_e =
  (* e is an R, E, T, or F parse tree node *)
  match expr with
  | PT_nt ("R", [e; et]) ->
             ast_ize_reln_tail (ast_ize_expr e) et
  | PT_nt ("E", [t; tt]) ->
             ast_ize_expr_tail (ast_ize_expr t) tt
  | PT_nt ("T", [f; ft]) ->
             ast_ize_expr_tail (ast_ize_expr f) ft
  | PT_nt ("F", [PT_id id]) -> AST_id(id)
  | PT_nt ("F", [PT_num num]) -> AST_num(num) 
  | PT_nt ("F", [PT_term "("; expr; PT_term ")"]) -> ast_ize_expr(expr)
  | _ -> raise (Failure "malformed parse tree in ast_ize_expr")

and ast_ize_reln_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs in an inheritec attribute.
     tail is an ET parse tree node *)
  match tail with
  | PT_nt ("ET", [PT_nt("ro", [PT_term "=="]); rhs])
        -> AST_binop ("==", lhs, ast_ize_expr rhs)
  | PT_nt ("ET", [PT_nt("ro", [PT_term "<"]); rhs])
        -> AST_binop ("<", lhs, ast_ize_expr rhs)
  | PT_nt ("ET", [PT_nt("ro", [PT_term ">"]); rhs])
        -> AST_binop (">", lhs, ast_ize_expr rhs)
  | PT_nt ("ET", [PT_nt("ro", [PT_term "<="]); rhs])
        -> AST_binop ("<=", lhs, ast_ize_expr rhs)
  | PT_nt ("ET", [PT_nt("ro", [PT_term ">="]); rhs])
        -> AST_binop (">=", lhs, ast_ize_expr rhs)
  | PT_nt ("ET", [PT_nt("ro", [PT_term "<>"]); rhs])
        -> AST_binop ("<>", lhs, ast_ize_expr rhs)
  | PT_nt ("ET", []) -> lhs
  | _ -> raise (Failure "malformed parse tree in ast_ize_reln_tail")

and ast_ize_expr_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs in an inherited attribute.
     tail is a TT or FT parse tree node *)
  match tail with
  | PT_nt ("TT", [PT_nt ("ao", [PT_term "+"]); t; tt]) ->
        ast_ize_expr_tail (AST_binop ("+", lhs, ast_ize_expr t)) tt
  | PT_nt ("TT", [PT_nt ("ao", [PT_term "-"]); t; tt]) ->
        ast_ize_expr_tail (AST_binop ("-", lhs, ast_ize_expr t)) tt
  | PT_nt ("FT", [PT_nt ("mo", [PT_term "/"]); f; ft]) ->
        ast_ize_expr_tail (AST_binop ("/", lhs, ast_ize_expr f)) ft
  | PT_nt ("FT", [PT_nt ("mo", [PT_term "*"]); f; ft]) ->
        ast_ize_expr_tail (AST_binop ("*", lhs, ast_ize_expr f)) ft
  | PT_nt ("TT", [])
  | PT_nt ("FT", []) -> lhs
  | PT_nt ("TT", _) -> raise (Failure "TT doesn't work")
  | PT_nt ("FT", _) -> raise (Failure "FT doesn't work")
  | _ -> raise (Failure "malformed parse tree in ast_ize_expr_tail")
;;


(*******************************************************************
   Functions to translate an AST into C
 *******************************************************************)

(* The code below is (obviously) a bare stub. The intent is that when
   you run translate on a full, correct AST, you'll get back code for an
   equivalent C program. If there are any variables that are written in
   the program but never read, you'll also get a warning message
   indicating their names and the lines on which the writes occur. Your
   C program should contain code to check for dynamic semantic errors. *)

(*****  The following is commented out so this stub code will not produce errors! *****

    let rec translate (ast:ast_sl)
      :  string   * string
      (* warnings   output_program *) = ...

    and translate_sl (...

    and translate_s (...

    and translate_assign (...

    and translate_read (...

    and translate_write (...

    and translate_if (...

    and translate_do (...

    and translate_check (...

    and translate_expr (...

 *****)
let code_gen_preface =
"
#include <stdio.h>
#include <stdlib.h>

int getint() {
    int n;
    char buf[100];
    fgets(buf, sizeof(buf), stdin);
    if (sscanf(buf, \"%d\", &n) != 1) {
       if (buf[0] == '\\n') printf(\"Error: No input.\");
       else printf(\"Error: Input not integer.\");
       exit(0);
    }
    return n;
}
void putint(int n) {
    printf(\"%d\\n\", n);
}
int main() {
"
 
 let rec translate (ast:ast_sl)
  :  string * string =
  (* collect all assigned variable (from AST_assign and AST_read)
   * and return the collected id list *)
  let rec traverse_assigned_variables (ast:ast_sl) : string list =
    match ast with
    | [] -> []
    | h :: t ->
      match h with
      | AST_assign (id, expr)  -> id::traverse_assigned_variables t 
      | AST_read (id)          -> id::traverse_assigned_variables t
      | AST_do (sl)            ->
          traverse_assigned_variables sl @ traverse_assigned_variables t
      | AST_if (expr, sl)      ->
          traverse_assigned_variables sl @ traverse_assigned_variables t
      | AST_write (expr)       
      | AST_check (expr)       -> traverse_assigned_variables t
      | AST_error              -> raise (Failure "traverse_variables error")
  in
  (* Collect all used variables (in expr), no matter it is assigned or not. *)
  let rec traverse_used_variables (ast:ast_sl) : string list =
    (* expr_vars collects all the variables in expr 
     * if it matches id, then return [id] as a list
     * if it matches num, then return [] because we only need variables
     * if it matches binop, then recursively call it on both sides of the op.*)
    let rec expr_vars (expr:ast_e) : string list = 
      match expr with
      | AST_id (id) -> [id]
      | AST_num (n) -> []
      | AST_binop (op, lhs, rhs) -> expr_vars lhs @ expr_vars rhs
    in
      
    match ast with
    | [] -> []
    | h :: t ->
      match h with
      | AST_assign (id, expr)  -> expr_vars expr @ traverse_used_variables t
      | AST_read (id)          -> traverse_used_variables t
      | AST_do (sl)            ->
          traverse_used_variables sl @ traverse_used_variables t
      | AST_if (expr, sl)      ->
          expr_vars expr @ traverse_used_variables sl @ traverse_used_variables t
      | AST_write (expr)       
      | AST_check (expr)       -> expr_vars expr @ traverse_used_variables t
      | AST_error              -> raise (Failure "traverse_variables error")
  in
  (* Concat all variable declarations *)
  let rec variables_string = function 
    [] -> ""
    | h::t -> "int " ^ h ^ ";\n" ^ variables_string t
  in
  let var_list_assigned = remove_duplicates(traverse_assigned_variables ast) in
  let var_list_used = remove_duplicates(traverse_used_variables ast) in
  (* "Assigned but never used" warning *)
  let unused_warning used assigned = 
    let not_used = List.filter (fun x -> not (List.mem x used)) assigned in
    let rec n_use l = 
      match l with
      | [] -> ""
      | h::t -> "not used var: " ^ h ^ "\n" ^ n_use t
    in
    n_use not_used
  in
  let warning_msg = unused_warning var_list_used var_list_assigned in
  (warning_msg, code_gen_preface ^ variables_string var_list_assigned 
  ^ translate_sl ast ^ "return 0;\n}")

and translate_sl (ast:ast_sl) : string =
  match ast with
  | [] -> ""
  | h :: t -> translate_s h ^ translate_sl t

and translate_s (s:ast_s) : string =
  match s with
  | AST_assign(id, expr)  -> translate_assign id expr
  | AST_read(id)          -> translate_read id
  | AST_write(expr)       -> translate_write expr
  | AST_if(expr, sl)      -> translate_if expr sl
  | AST_do(sl)            -> translate_do sl
  | AST_check(rel)        -> translate_check rel
  | AST_error             -> raise (Failure "translate_s error")

and translate_assign (id:string) (expr:ast_e) : string =
  id ^ " = " ^ (translate_expr expr) ^ ";\n"

and translate_read (id:string) : string =
  id ^ " = getint();\n"  (* maybe we can pass a lineno to getint function. *)

and translate_write (expr:ast_e) : string =
  "putint(" ^ translate_expr(expr) ^ ");\n"

and translate_if (expr:ast_e) (sl:ast_sl) : string =
  "if (" ^ translate_expr(expr) ^ ") {\n" ^ translate_sl(sl) ^ "}\n"

and translate_do (ast:ast_sl) : string =
  "while(1) {\n" ^ translate_sl(ast) ^ "}\n"

and translate_check (expr:ast_e) : string =
  "if (!" ^ translate_expr(expr) ^ ") break;\n"

(* Wrap the divisor with zero_breaker, because "if" conditions are hard to implement here. *)
and translate_expr (expr:ast_e) : string =
  match expr with
  | AST_num(n) -> n
  | AST_id(id) -> id
  | AST_binop(op, lhs, rhs) ->
    "(" ^ translate_expr(lhs) ^ op ^ translate_expr(rhs) ^ ")"

(*******************************************************************
   Sample programs in the calculator language
 *******************************************************************)
 
let sum_ave_prog = "
  read a
  read b
  sum := a + b
  write sum
  write sum / 2";;
	 
let primes_prog = "
  read n
  cp := 2
  do check n > 0
    found := 0
    cf1 := 2
    cf1s := cf1 * cf1
    do check cf1s <= cp
      cf2 := 2
      pr := cf1 * cf2
      do check pr <= cp
        if pr == cp
          found := 1
        fi
        cf2 := cf2 + 1
        pr := cf1 * cf2
      od
      cf1 := cf1 + 1
      cf1s := cf1 * cf1
    od
    if found == 0
      write cp
      n := n - 1
    fi
    cp := cp + 1
  od";;