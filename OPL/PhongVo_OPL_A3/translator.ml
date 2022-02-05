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
	
   The myStringult of this invocation should be a C program on standard
   output, which can be compiled and run to produce the first N primes
   (where N is a number typed by the user).
 *******************************************************************)


 #use "parser.ml";;
 #load "str.cma";;


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
  (* your code should replace the following line *)
  match p with
  | PT_nt ("P", [statement_list; PT_term "$$"]) 
        -> (ast_ize_SL statement_list)
  | _ -> raise (Failure "malformed parse tree in ast_ize_P")

and ast_ize_SL (sl:parse_tree) : ast_sl =
  match sl with
    | PT_nt ("SL", []) -> []
(*
your code here ...
*)	
    | PT_nt ("SL", [statement; statement_list])
        -> (ast_ize_S statement)::(ast_ize_SL statement_list) 
  (*Concatanating two AST together*)
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
  | PT_nt ("S", [PT_term "if"; reln; statement_list; PT_term "fi"])
        -> AST_if (ast_ize_expr reln, ast_ize_SL statement_list)
  | PT_nt ("S", [PT_term "do"; statement_list; PT_term "od"])
        -> AST_do (ast_ize_SL statement_list)      
  | _ -> raise (Failure "malformed parse tree in ast_ize_S")


(** DONE!!!**)
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


(** DONE!!!**)
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

(*******************************************************************
   Functions to translate an AST into C
 *******************************************************************)

(* The code below is (obviously) a bare stub. The intent is that when
   you run translate on a full, correct AST, you'll get back code for an
   equivalent C program. If there are any variables that are written in
   the program but never read, you'll also get a warning message
   indicating their names and the lines on which the writes occur. Your
   C program should contain code to check for dynamic semantic errors. *)

let sum_ave_prog = "
  read a
  read b
  sum := a + b
  write sum
  write sum / 2";;

let primes_prog = "
  read n
  cp := 2
  Un_USED := 3
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

let firPosition (x,_ ,_ ) = x;;
let sndPosition (_, x, _) = x;;
let trdPosition (_,_ , x) = x;;

let rec declared id declared_list =
    match declared_list with [] -> false
    | h :: t -> if h = id then true else declared id t;;

let rec used id used_list =
    match used_list with [] -> false
    | h :: t -> if h = id then true else used id t;;

let compare l1 l2 = 
    List.filter (fun x -> not (List.mem x l2)) l1

let contains s subString =
    let reg = regexp_string subString in
    try ignore (search_forward reg s 0); true
    with Not_found -> false

let rec print_list = function [] -> ()
    | h :: t -> print_string h ; print_newline () ; print_list t;;

let rec translate (ast : ast_sl) (program : string) : string * string =
    let warning = "" in
    let declared_list = [] in
    let used_list = [] in

    let rec translate_code (declared_list : string list) (used_list : string list) (ast : ast_sl) 
                : string list * string list * string =
    match ast with [] -> (declared_list @ [], used_list @ [], "")
    | h :: t ->
        (match h with
        | AST_assign (s) -> 
            let assing_myString = assign_job declared_list used_list s in
            let myString = translate_code (firPosition assing_myString) (sndPosition assing_myString) t in
            (firPosition myString, sndPosition myString, (trdPosition assing_myString) ^ (trdPosition myString))
        | AST_read (s) -> 
            let read_myString = read_job declared_list used_list s in
            let myString = translate_code (firPosition read_myString) (sndPosition read_myString) t in
            (firPosition myString, sndPosition myString, (trdPosition read_myString) ^ (trdPosition myString))
        | AST_write (s) -> 
            let write_myString = write_job declared_list used_list s in
            let myString = translate_code (firPosition write_myString) (sndPosition write_myString) t in
            (firPosition myString, sndPosition myString, (trdPosition write_myString) ^ (trdPosition myString))
        | AST_if (s) ->
            let if_myString = if_job declared_list used_list s in
            let myString1 = translate_code (firPosition if_myString) (sndPosition if_myString) (snd s) in
            let myString2 = translate_code (firPosition myString1) (sndPosition myString1) t in
            (firPosition myString2, sndPosition myString2, (trdPosition if_myString) ^ (trdPosition myString1) ^ "}\n" ^ (trdPosition myString2))
        | AST_do (s) ->
            let myString1 = translate_code declared_list used_list s in
            let do_myString = do_job (firPosition myString1) (sndPosition myString1) (trdPosition myString1) in 
            let myString2 = translate_code (firPosition do_myString) (sndPosition do_myString) t in
            (firPosition myString2, sndPosition myString2, (trdPosition do_myString) ^ (trdPosition myString2)) 
        | AST_check (s) ->
            let check_myString = check_job declared_list used_list s in
            let myString = translate_code (firPosition check_myString) (sndPosition check_myString) t in
            (firPosition myString, sndPosition myString, (trdPosition check_myString) ^ (trdPosition myString))
        | _ -> raise (Failure "Error")) in

    let prefix = "#include <stdio.h>\n#include <stdlib.h>\n" ^ 
    "int getint(){\nint x;\nscanf(\"%d\", &x);\nreturn x;\n}\n" ^
    "void putint(int n){\nprintf(\"%d\\n\", n);\n}\n" ^
    "int main(){\n" in

    let suffix = "return 0;\n}" in

    let myString_tuple = translate_code declared_list used_list ast in

    let declared_new_list = unique_sort (firPosition myString_tuple) in

    let used_new_list = unique_sort (sndPosition myString_tuple) in

    let no_used_list = compare declared_new_list used_new_list in

    let line_list = split (regexp "[\n]+") program in

    let rec create_warning no_used_list line_list warning = 
        let rec helper sub l =
            match l with
            | [] -> raise (Failure "Error")
            | h :: t -> if contains h sub then sub ^ " never used, defined in : " ^ (String.trim h) else helper sub t in
        match no_used_list with [] -> warning
        | hs :: ts -> warning ^ "\n" ^ (helper hs line_list) ^ (create_warning ts line_list warning) in

    (create_warning no_used_list line_list warning, prefix ^ trdPosition myString_tuple ^ suffix)

and assign_job (declared_list : string list) (used_list : string list)  (s : string * ast_e) 
                  : string list * string list * string =
    if declared (fst s) declared_list then
        let myString = create_expr declared_list used_list (snd s) in
        (firPosition myString, sndPosition myString, fst s ^ " = " ^ trdPosition myString ^ ";\n") 
    else
        let myString = create_expr (declared_list @ [fst s]) used_list (snd s) in
        (firPosition myString, sndPosition myString, "int " ^ fst s ^ " = " ^ trdPosition myString ^ ";\n") 

and read_job (declared_list : string list) (used_list : string list) (s : string) 
                : string list * string list * string =
    if declared s declared_list then (declared_list, used_list, s ^ " = getint();\n")
    else (declared_list @ [s], used_list, "int " ^ s ^ " = getint();\n")

and write_job (declared_list : string list) (used_list : string list) (s : ast_e) 
                : string list * string list * string =
    let myString = create_expr declared_list used_list s in
    (firPosition myString, sndPosition myString, "putint(" ^ trdPosition myString ^ ");\n")

and if_job (declared_list : string list) (used_list : string list) (s : ast_e * ast_sl) 
              : string list * string list * string =
    let myString = create_expr declared_list used_list (fst s) in
    (firPosition myString, sndPosition myString, "if(" ^ trdPosition myString ^ "){\n")

and do_job (declared_list : string list) (used_list : string list) (s : string)
              : string list * string list * string =
    (declared_list, used_list, "while(" ^ s ^ "}\n")

and check_job (declared_list : string list) (used_list : string list) (s : ast_e) 
              : string list * string list * string =
    let myString = create_expr declared_list used_list s in
    (firPosition myString, sndPosition myString, trdPosition myString ^ "){\n")

and create_expr (declared_list : string list) (used_list : string list) (s : ast_e) 
                : string list * string list * string =
    match s with
    | AST_id (id) -> if used id used_list then (declared_list, used_list, id)
                      else (declared_list, used_list @ [id], id)
    | AST_num (num) -> (declared_list, used_list, num)
    | AST_binop (binop) ->
        let myString1 = create_expr declared_list used_list (sndPosition binop) in
        let myString2 = create_expr (firPosition myString1) (sndPosition myString1) (trdPosition binop) in
        (firPosition myString2, sndPosition myString2, trdPosition myString1 ^ " " ^ firPosition binop ^ " " ^ trdPosition myString2)

let () =   
    let trans_myString = translate (ast_ize_P (parse ecg_parse_table primes_prog)) primes_prog in
    print_string (snd trans_myString);
    if String.length (fst trans_myString) > 0 then
        print_string ("\n\nWarnings:" ^ (fst trans_myString) ^ "\n");
    print_newline ();
