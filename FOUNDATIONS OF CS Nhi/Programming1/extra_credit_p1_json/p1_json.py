# DangNhi Ngoc Ngo

# import json to generate the inputs from json files
import json
import sys
import argparse


# initialize all necessary variables
DFA_DESCRIPTION = "description"
TOTAL_STATES = "states"
START_STATE = "start"
ALPHABETS = "alphabet"
TRANSITION_TABLE = "transitions"
ACCEPTED_STATE = "accept"
TEST_STRINGS = "inputs"

class DFA:
    # set all variables to NONE
    states = None
    alphabet = None
    description = None
    start_state = None
    accept_states = None
    transitions = None
    test_strings = None
	
    def __init__(self, file_name):
	# Load the json input files
        dfa = json.load(open(file_name))
        self.states = dfa[TOTAL_STATES]
        self.alphabet = dfa[ALPHABETS]
        self.description = dfa[DFA_DESCRIPTION]
        self.start_state = dfa[START_STATE]
        self.accepted_states = dfa[ACCEPTED_STATE]
        self.transitions = dfa[TRANSITION_TABLE]
        self.test_strings = dfa[TEST_STRINGS]

    @property
    def get_dfa(self):
        return self, self.test_strings

    def run_dfa(self, input_str):
        current_state = self.start_state
        print("INPUT: " + input_str)

        for char in input_str:
            if (current_state not in self.transitions):
                print("Invalid DFA: " + current_state + " is not a state in the DFA.")
                return
            
            new_state = self.transitions[current_state][char]				
            print("--Current State: " + current_state + " Symbol: " + char + " --> New State: " + new_state)
            current_state = new_state

        if any(current_state in s for s in self.accepted_states):
            print(input_str + "  -->  ACCEPT\n")
        else:
            print(input_str + "  -->  NOT ACCEPT\n")

if __name__ == "__main__":
    #Initializes an ArgumentParser object for establishing the program's command line requirements and parameters.
    parser = argparse.ArgumentParser(
    description = "This program implements a DFA defined by a .dfa file. \n"+
    "Proceeding user input is then interpreted as strings to be fed through the machine.\n"+
    " If symbols from input are not of the machine's alphabet, or if traversal thorugh the machine ends\n "
     +"anywhere other than an accept state, the program informs the user that their input was not accepted.\n" 
     +"If symbols are from the machine's alphabet and traversal ends in an accept state, the input is accepted.")
    #Initializes an ArgumentParser object for establishing the program's command line requirements and parameters.
    parser.add_argument(
    "-d", metavar = "<file.json>", help = ".json file for interpretation. Required.", required = True)
    args = parser.parse_args()
    # get file from args
    fileName = vars(args)
    # convert to string from dict type
    input = str(list(fileName.values()))[2:-2]
    print (input)
    dfa, input_strings = DFA(input).get_dfa
    print (dfa.description + "\n" + "States: "+ str(dfa.states)[1:-1].replace("'",""))
    print ("Alphabet: " + str(dfa.alphabet)[1:-1].replace("'","")    + "\nStartState: " 
        +  str(dfa.start_state).replace("'","") +  "\nFinalState: "
         + str(dfa.accepted_states)[1:-1].replace("'","")  +"\n")
    
    for s in input_strings:
        dfa.run_dfa(s)

