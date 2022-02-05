from nfa import NFA as NFA
from exceptions import RejectionError as exceptions
import sys
import argparse
from collections import defaultdict
from itertools import zip_longest
# NFA which matches strings beginning with 'a', ending with 'a', and containing
# no consecutive 'b's

parser = argparse.ArgumentParser(description="This program implements a NFA defined by a .dfa file.")
parser.add_argument("-d", metavar="<file.nfa>", help=".nfa file for interpretation. Required.", required=True)
parser.add_argument("-v", "--verbose", help="Enables verbose mode. Displays machine information, "
                                            "state transitions as they occur,""and info messages if "
                                            "input string is not of the machine's alphabet. Optional.",
                    action="store_true")
args = parser.parse_args()
if not args.d.endswith(".nfa"):
    print("Error: file passed with -d flag is not a .nfa file.")
else:
    nfaLines = (open(args.d, "r")).readlines()
    nfaTransitionDict = defaultdict(list)
    nfaTransition = {}
    for i in range(0, len(nfaLines)):
        nfaLines[i] = nfaLines[i].replace("\n", "")
        (category, values) = nfaLines[i].split(": ")
        if category == "states":
            nfaStates = set(values.split(" "))
        elif category == "alphabet":
            nfaAlphabet = set(values.split(" "))
        elif category == "startstate":
            nfaInitialState = ''.join((values.split(" ")))
        elif category == "finalstate":
            nfaFinalState = set(values.split(" "))
        elif category == "transition":
            string = list(values.split(" "))
            value = {string[1]: {string[2]}}
            nfaTransitionDict[string[0]].append(value)

    nfaTransitionDict = dict(nfaTransitionDict)
    new_dict = {}
    # convert from defaultdict to regular dict
    for key in nfaTransitionDict.keys():
        for items in nfaTransitionDict[key]:
            subkey = list(items.keys())
            for subkeys in subkey:
                fn = items.pop(subkeys)
                new_dict[key] = {subkeys: fn}
    nfa = NFA(
        states=nfaStates,
        input_symbols=nfaAlphabet,
        transitions=new_dict,
        initial_state=nfaInitialState,
        final_states=nfaFinalState
    )
# Runs the DFA with every line of input the user feeds the DFA.
print("Please enter tape input: ")
for line in sys.stdin:
    line = line.strip("\n")
    try:
        if len(nfa.validate_input(line)) >= 0: # 0101
            if args.verbose:
                print("­­­BEGIN DFA definition­­­ ")
                print("States:")
                print(' '.join(nfa.states))
                print("Alphabet:")
                print(' '.join(nfa.input_symbols))
                print("StartState:")
                print(nfa.initial_state)
                print("FinalState:")
                print(' '.join(nfa.final_states))
                print("Transitions:")
                print(''.join(nfaTransition))
                print("­­­END DFA definition­­-")
                for i in range(0, len(list(nfa.validate_input(line, step=True)))):
                    result_list = list(nfa.validate_input(line, step=True))
                    if i is 0:
                        print("Current state: " + nfa.initial_state + " Symbol: " + result_list[i][1] +
                              " Next state: " + str(result_list[i][0]).replace('{\'','').replace('\'}',''))
                    else:
                        print("Current state: " + str(result_list[i-1][0]).replace('{\'','').replace('\'}','') + " Symbol: " + result_list[i][1] +
                              " Next state: " + str(result_list[i][0]).replace('{\'','').replace('\'}',''))
            print(line + " --> ACCEPT")
    except exceptions:
        print(line + " --> NOT ACCEPT")
    print("Please enter tape input (CTRL+C to quit): ")

