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
 #load "str.cma";;


(*******************************************************************
   Declarations and functions to transform a parse tree into an
   abstract syntax tree (AST)
 *******************************************************************)

let fst_of (x, _, _) = x;;

let snd_of (_, x, _) = x;;

let trd_of (_, _, x) = x;;


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
  (* your code should replace the following line *)
  match p with
  | PT_nt ("P", [sl; PT_term "$$"]) -> ast_ize_SL sl
  | _ -> raise (Failure "malformed parse tree in ast_ize_P")

and ast_ize_SL (sl:parse_tree) : ast_sl =
  match sl with
  | PT_nt ("SL", []) -> []
  | PT_nt ("SL", [s; sl]) -> ast_ize_S s :: ast_ize_SL sl
  | _ -> raise (Failure "malformed parse tree in ast_ize_SL")


and ast_ize_S (s:parse_tree) : ast_s =
  match s with
  | PT_nt ("S", [PT_id lhs; PT_term ":="; expr])
      -> AST_assign (lhs, (ast_ize_expr expr))
  (*
     your code here ...
  *)
  | PT_nt ("S", [PT_term "read"; PT_id id])
      -> AST_read id
  | PT_nt ("S", [PT_term "write"; expr])
      -> AST_write (ast_ize_expr expr)
  | PT_nt ("S", [PT_term "check"; reln])
        -> AST_check (ast_ize_expr reln)
  | PT_nt ("S", [PT_term "if"; reln; sl; PT_term "fi"])
        -> AST_if (ast_ize_expr reln, ast_ize_SL sl)
  | PT_nt ("S", [PT_term "do"; sl; PT_term "od"])
        -> AST_do (ast_ize_SL sl)      
  | _ -> raise (Failure "malformed parse tree in ast_ize_S")

and ast_ize_expr (e:parse_tree) : ast_e =
  (* e is an R, E, T, or F parse tree node *)
  match e with
  (*
     your code here ...
  *)
  | PT_nt ("R", [expr; expr_tail])
        -> ast_ize_reln_tail (ast_ize_expr expr) expr_tail
  | PT_nt ("E", [term; term_tail])
        -> ast_ize_expr_tail (ast_ize_expr term) term_tail
  | PT_nt ("T", [fact; fact_tail])
        -> ast_ize_expr_tail (ast_ize_expr fact) fact_tail
  | PT_nt ("F", [PT_id id])
        -> AST_id id
  | PT_nt ("F", [PT_num num])
        -> AST_num num
  | PT_nt ("F", [PT_term "("; expr; PT_term ")"])
        -> ast_ize_expr expr  
  | _ -> raise (Failure "malformed parse tree in ast_ize_expr")

and ast_ize_reln_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs in an inheritec attribute.
     tail is an ET parse tree node *)
  match tail with
  (*
     your code here ...
  *)
  | PT_nt ("ET", []) -> lhs
  | PT_nt ("ET", [PT_nt ("ro", [PT_term ro]); expr]) when member ro ["=="; "<>"; "<"; ">"; "<="; ">="]
        -> AST_binop (ro, lhs, ast_ize_expr expr)  
  | _ -> raise (Failure "malformed parse tree in ast_ize_reln_tail")

and ast_ize_expr_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs in an inherited attribute.
     tail is a TT or FT parse tree node *)
  match tail with
  (*
     your code here ...
  *)
  | PT_nt ("TT", []) -> lhs
  | PT_nt ("TT", [PT_nt ("ao", [PT_term ao]); term; term_tail]) when member ao ["+"; "-"]
        -> AST_binop (ao, lhs, ast_ize_expr_tail (ast_ize_expr term) term_tail)
  | PT_nt ("FT", []) -> lhs
  | PT_nt ("FT", [PT_nt ("mo", [PT_term mo]); fact; fact_tail]) when member mo ["*"; "/"]
        -> AST_binop (mo, lhs, ast_ize_expr_tail (ast_ize_expr fact) fact_tail)  
  | _ -> raise (Failure "malformed parse tree in ast_ize_expr_tail")
;;


let sum_ave_prog = "
  read a
  read b
  sum := a + b
  write sum
  write sum / 2";;

let primes_prog = "
  read n
  cp := 2
  UU := 3
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
		read NN
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


(*******************************************************************
   Functions to translate an AST into C
 *******************************************************************)

(* The code below is (obviously) a bare stub. The intent is that when
   you run translate on a full, correct AST, you'll get back code for an
   equivalent C program. If there are any variables that are written in
   the program but never read, you'll also get a warning message
   indicating their names and the lines on which the writes occur. Your
   C program should contain code to check for dynamic semantic errors. *)

let rec check_declared id id_dec_list =
    match id_dec_list with
    | [] -> false
    | h :: t -> if h = id then true else check_declared id t;;

let rec check_used id id_used_list =
    match id_used_list with
    | [] -> false
    | h :: t -> if h = id then true else check_used id t;;

let diff l1 l2 = 
    List.filter (fun x -> not (List.mem x l2)) l1

let contains s sub =
    let re = regexp_string sub in
    try ignore (search_forward re s 0); true
    with Not_found -> false

let rec print_list = function 
    | [] -> ()
    | h :: t -> print_string h ; print_newline () ; print_list t;;

let rec translate (ast : ast_sl) (program : string)
    :  string * string
    (* warnings  output_program *) =
    let warnings = "" in
    let id_dec_list = [] in
    let id_used_list = [] in

    let rec gen_body (id_dec_list : string list) (id_used_list : string list) (ast : ast_sl) 
                : string list * string list * string =
    match ast with
    | [] -> (id_dec_list @ [], id_used_list @ [], "")
    | h :: t ->
        (match h with
        | AST_assign (s) -> 
            let assing_res = translate_assign id_dec_list id_used_list s in
            let res = gen_body (fst_of assing_res) (snd_of assing_res) t in
            (fst_of res, snd_of res, (trd_of assing_res) ^ (trd_of res))
        | AST_read (s) -> 
            let read_res = translate_read id_dec_list id_used_list s in
            let res = gen_body (fst_of read_res) (snd_of read_res) t in
            (fst_of res, snd_of res, (trd_of read_res) ^ (trd_of res))
        | AST_write (s) -> 
            let write_res = translate_write id_dec_list id_used_list s in
            let res = gen_body (fst_of write_res) (snd_of write_res) t in
            (fst_of res, snd_of res, (trd_of write_res) ^ (trd_of res))
        | AST_if (s) ->
            let if_res = translate_if id_dec_list id_used_list s in
            let res1 = gen_body (fst_of if_res) (snd_of if_res) (snd s) in
            let res2 = gen_body (fst_of res1) (snd_of res1) t in
            (fst_of res2, snd_of res2, (trd_of if_res) ^ (trd_of res1) ^ "}\n" ^ (trd_of res2))
        | AST_do (s) ->
            let res1 = gen_body id_dec_list id_used_list s in
            let do_res = translate_do (fst_of res1) (snd_of res1) (trd_of res1) in 
            let res2 = gen_body (fst_of do_res) (snd_of do_res) t in
            (fst_of res2, snd_of res2, (trd_of do_res) ^ (trd_of res2)) 
        | AST_check (s) ->
            let check_res = translate_check id_dec_list id_used_list s in
            let res = gen_body (fst_of check_res) (snd_of check_res) t in
            (fst_of res, snd_of res, (trd_of check_res) ^ (trd_of res))
        | _ -> raise (Failure "Error")) in

    let prog_prefix = "#include <stdio.h>\n#include <stdlib.h>\n" ^ 
    "int getint(){\nint x;\nscanf(\"%d\", &x);\nreturn x;\n}\n" ^
    "void putint(int n){\nprintf(\"%d\\n\", n);\n}\n" ^
    "int main(){\n" in

    let prog_suffix = "return 0;\n}" in

    let res_tuple = gen_body id_dec_list id_used_list ast in

    let id_dec_revised_list = unique_sort (fst_of res_tuple) in

    let id_used_revised_list = unique_sort (snd_of res_tuple) in

    let id_never_used_list = diff id_dec_revised_list id_used_revised_list in

    let prog_line_list = split (regexp "[\n]+") program in

    let rec gen_warnings id_never_used_list prog_line_list warnings = 
        let rec helper sub l =
            match l with
            | [] -> raise (Failure "Error")
            | h :: t -> if contains h sub then sub ^ " never used, defined in : " ^ (String.trim h) else helper sub t in
        match id_never_used_list with
        | [] -> warnings
        | hs :: ts -> warnings ^ "\n" ^ (helper hs prog_line_list) ^ (gen_warnings ts prog_line_list warnings) in

    (gen_warnings id_never_used_list prog_line_list warnings, prog_prefix ^ trd_of res_tuple ^ prog_suffix)

and translate_assign (id_dec_list : string list) (id_used_list : string list)  (s : string * ast_e) 
                  : string list * string list * string =
    if check_declared (fst s) id_dec_list then
        let res = translate_expr id_dec_list id_used_list (snd s) in
        (fst_of res, snd_of res, fst s ^ " = " ^ trd_of res ^ ";\n") 
    else
        let res = translate_expr (id_dec_list @ [fst s]) id_used_list (snd s) in
        (fst_of res, snd_of res, "int " ^ fst s ^ " = " ^ trd_of res ^ ";\n") 

and translate_read (id_dec_list : string list) (id_used_list : string list) (s : string) 
                : string list * string list * string =
    if check_declared s id_dec_list then (id_dec_list, id_used_list, s ^ " = getint();\n")
    else (id_dec_list @ [s], id_used_list, "int " ^ s ^ " = getint();\n")

and translate_write (id_dec_list : string list) (id_used_list : string list) (s : ast_e) 
                : string list * string list * string =
    let res = translate_expr id_dec_list id_used_list s in
    (fst_of res, snd_of res, "putint(" ^ trd_of res ^ ");\n")

and translate_if (id_dec_list : string list) (id_used_list : string list) (s : ast_e * ast_sl) 
              : string list * string list * string =
    let res = translate_expr id_dec_list id_used_list (fst s) in
    (fst_of res, snd_of res, "if(" ^ trd_of res ^ "){\n")

and translate_do (id_dec_list : string list) (id_used_list : string list) (s : string)
              : string list * string list * string =
    (id_dec_list, id_used_list, "while(" ^ s ^ "}\n")

and translate_check (id_dec_list : string list) (id_used_list : string list) (s : ast_e) 
              : string list * string list * string =
    let res = translate_expr id_dec_list id_used_list s in
    (fst_of res, snd_of res, trd_of res ^ "){\n")

and translate_expr (id_dec_list : string list) (id_used_list : string list) (s : ast_e) 
                : string list * string list * string =
    match s with
    | AST_id (id) -> if check_used id id_used_list then (id_dec_list, id_used_list, id)
                      else (id_dec_list, id_used_list @ [id], id)
    | AST_num (num) -> (id_dec_list, id_used_list, num)
    | AST_binop (binop) ->
        let res1 = translate_expr id_dec_list id_used_list (snd_of binop) in
        let res2 = translate_expr (fst_of res1) (snd_of res1) (trd_of binop) in
        (fst_of res2, snd_of res2, trd_of res1 ^ " " ^ fst_of binop ^ " " ^ trd_of res2)

		
let () =   
    print_string ("\nResult:\n");
    let trans_res = translate (ast_ize_P (parse ecg_parse_table primes_prog)) primes_prog in
    print_string (snd trans_res);
    if String.length (fst trans_res) > 0 then
        print_string ("\n\nWarnings:" ^ (fst trans_res) ^ "\n");
    print_newline ();
