# NAME: Chhun Kim
# E-Mail: chhun_kim@student.uml.edu
# Credit to http://code.runnable.com/VcYmRqc8eztFx-Ap/dfa-simulator-python

# import json to generate the inputs from json files
import json

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
        print "INPUT: " + input_str

        for char in input_str:
            if (current_state not in self.transitions):
                print "Invalid DFA: " + current_state + " is not a state in the DFA."
	        return
            
	    new_state = self.transitions[current_state][char]
						
            print "--Current State: " + current_state + " Symbol: " + char + " --> New State: " + new_state
            current_state = new_state

        if any(current_state in s for s in self.accepted_states):
            print input_str + "  -->  ACCEPT\n"
        else:
            print input_str + "  -->  NOT ACCEPT\n"

if __name__ == "__main__":
    dfa, input_strings = DFA("Ex16b.json").get_dfa
    print dfa.description + "\n" + "States: q1, q2, q3, q4"
    print "Alphabet: 0, 1\n" + "StartState: q1\n" + "FinalState: q4\n"
    
    for s in input_strings:
        dfa.run_dfa(s)

