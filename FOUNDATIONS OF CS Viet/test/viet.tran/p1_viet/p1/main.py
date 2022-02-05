import sys
import argparse
from dfaClass import DFA
from dfaTraversal import *

#Initializes an ArgumentParser object for establishing the program's command line requirements and parameters.
parser = argparse.ArgumentParser(
    description = "This program implements a DFA defined by a .dfa file. Proceeding user input is then interpreted as strings to be fed through the machine. If symbols from input are not of the machine's alphabet, or if traversal thorugh the machine ends anywhere other than an accept state, the program informs the user that their input was not accepted. If symbols are from the machine's alphabet and traversal ends in an accept state, the input is accepted.")

parser.add_argument(
    "-v", "--verbose", help = "Enables verbose mode. Displays machine information, state transistions as they occur, and info messages if input string is not of the machine's alphabet. Optional.", action = "store_true")

parser.add_argument(
    "-d", metavar = "<file.dfa>", help = ".dfa file for interpretation. Required.", required = True)

#Command line arguments are parsed, and a namespace containing the parsed argument values is returned to args.
args = parser.parse_args()

if (args.d.endswith(".dfa")) == False:
    print("Error: file passed with -d flag is not a .dfa file.")
else:
    dfa = DFA(args.verbose)
    #Stores each line of the .dfa file into an element of a list dfaLines
    dfaLines = (open(args.d, "r")).readlines()

    for i in range(0, len(dfaLines)):
        dfaLines[i] = dfaLines[i].replace("\n", "")
        (category, values) = dfaLines[i].split(": ")

        if category == "states":
            dfa.setStates(list(values.split(" ")))
        
        elif category == "alphabet":
            dfa.setAlphabet(list(values.split(" ")))
        
        elif category == "startstate":
            dfa.setStartState(values)

        elif category == "finalstate":
            dfa.setFinalState(list(values.split(" ")))
        
        elif category == "transition":
            dfa.addTransition(list(values.split(" ")))

    if(args.verbose):
        dfa.printDef()

    #Runs the DFA with every line of input the user feeds the DFA.
    print("Please enter tape input: ")
    for line in sys.stdin:
        line = line.strip("\n")
        runDFA(line, dfa);
        print("Please enter tape input (CTRL+C to quit): ")
