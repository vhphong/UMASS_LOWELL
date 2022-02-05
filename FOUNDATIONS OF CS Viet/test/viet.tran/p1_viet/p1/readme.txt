Author: Viet Tran

This program reads in a DFA defined by a user in a .dfa file . The .dfa file must be in the format...

states:  <Set of states for the machine>
alphabet: <Symbols accepted by the machine>
startstate: <Machine's starting state>
finalstate: <Machine's final state(s)>
transition: <currentState inputSymbol targetState>
.
.
.
transition: <currentState inputSymbol targetState> (for as many transistions necessary)

With a passed .dfa file, a user may use stdin to pass strings of symbols of the machine's alphabet to test whether or not each string is of the machine's language
(whether or not the machine accepts input). They may do so by piping in input, or by entering string themselves line-by-line. If the latter, the user will have to terminate
stdin themselves with Ctx + C to terminate the program.

The program was written using Python 3.4. To run the program, enter

python3 main.py -d <.dfa file>  
optionally with a verbose flag -v or stdin directives. 

Sample commands to run: 
python3 main.py -d 1_6b.dfa 

python3 main.py -d 1_6b.dfa -v

python3 main.py -d 1_6b.dfa -v < 1_6b.in 
python3 main.py -d 1_6c.dfa -v < 1_6c.in
python3 main.py -d 1_6f.dfa -v < 1_6f.in
python3 main.py -d a*_c.dfa -v < a*_c.in

python3 main.py -d 1_6b.dfa -v < 1_6b.in > 1_6b.out && cat 1_6b.out

cat 1_6b.in | python3 main.py -d 1_6b.dfa


