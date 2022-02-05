I believe for the most part, the assignment should be done. It was pretty
straightforward and after going over ocaml in class, things seemed
managable to do. The code follows what the assignment asks for, however 
what lacks are some of the exceptions the assignment asked for in the 
C-code. The use of uninitialized variable part, I'm not sure if we do
need an exception for that since that's usually caught by the compiler
I believe. I also did not get to implement the divide by zero part,
but I may do so during resubmission. Everything else is fine.

Additionally, I'm unable to compile with the terminal cmd "ocamlc translator.ml".
I hope I'm not mistaken but I believe that's how you would compile an executable
for translator.ml, unless there is more I'm missing?

That should be most of my concerns. Everything else should work if you just 
open the ocaml interpretor with running "ocaml" in the terminal, followed by:

#use "test.ml";;

which will print the C-code that can be used to create the program where once
run, simply enter an "n" number, and it will display the output. The translated
AST will be within the c-program also.

I tested the code in Visual Studio like the professor did and I can confirm that it works.

NOTE: it doesn't prompt you for a number, but once you see the terminal open
you can just enter a number.