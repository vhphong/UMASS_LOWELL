(* 
  ocamlc -o a1 a1.ml
  ./a1 
 *)

let next_perm p =
	let n = Array.length p in
	let i = let rec aux i = 
		if (i < 0) || (p.(i) < p.(i+1)) then i
		else aux (i - 1) in aux (n - 2) in
	let rec aux j k = if j < k then
		let t = p.(j) in
			p.(j) <- p.(k);
			p.(k) <- t;
			aux (j + 1) (k - 1)
	else () in aux (i + 1) (n - 1);
	if i < 0 then false else
		let j = let rec aux j =
			if p.(j) > p.(i) then j
			else aux (j + 1) in aux (i + 1) in
		let t = p.(i) in
			p.(i) <- p.(j);
			p.(j) <- t;
			true;;
 
let print_perm p =
	let n = Array.length p in
	for i = 0 to n - 2 do
		print_int p.(i);
		print_string " "
	done;
	print_int p.(n - 1);
	print_newline ();;          (*print new line*)
 
let print_all_perm n =
	let p = Array.init n (function i -> i + 1) in
	print_perm p;
	while next_perm p do
		print_perm p
	done;;

let () = print_string "Please enter an integer number: " in (*Asking for the integer*)
  let i = read_int () in               (*put the integer to i*)
    print_all_perm i;;                (*call the function*)
    
(*https://rosettacode.org/wiki/Permutations?fbclid=IwAR0SwqCOQvPp5wMOVpU4kExXv21b41YarBfgF5Flv207itH57CqLf0YEZIs#OCaml*)