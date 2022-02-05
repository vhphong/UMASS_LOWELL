let rec comb m lst =
  match m, lst with
    0, _ -> [[]]
  | _, [] -> []
  | m, x :: xs -> List.map (fun y -> x :: y) (comb (pred m) xs) @
                  comb m xs
;;

print_string "Enter a string: ";
let str = read_line () in
  print_string "Enter an integer: ";
  let num = read_int () in
    Printf.printf "%s%d\n" str num
