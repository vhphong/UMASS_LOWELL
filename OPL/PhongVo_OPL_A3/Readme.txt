Name: Phong Vo
Email: Phong_Vo@student.uml.edu	
Student ID: 01790283 
My partner: Hoang Do, David Huynh

Our program was built based on the provided snippet. It has two related parts.
In the first part, we accomplished the function by assigning the return value to variable which is able to be displayed. We used the the function let rec ast_ize_P (p:parse_tree) : ast_sl to transform the parse tree into AST.
In the second part, we translated the AST into an equivalent program in C. By completing the function let rec translate (ast : ast_sl) (program : string):  string * string. We also added an unused variable "NOT_Use := 3" in primes_prog  and test the detector that variable and print the output.


Code to run: 
ocaml translator.ml