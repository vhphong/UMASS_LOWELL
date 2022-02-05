#Defines the DFA machine class
class DFA:

    def __init__(self, verbose):
        #Boolean value indicating if the program should be verbose (True) or not (False)
        self.verbose = verbose
        #List of states of the DFA
        self.states = []
        #List of symbols of the DFA's alphabet
        self.alphabet = []
        #Start state of the DFA
        self.startState = None
        #Current state of the DFA
        self.currentState = None
        #Valid accept state for the DFA. Can exceed 1.
        self.finalState = []
        #List of lists of DFA transitions in the format [qA, delta, qB], where qB is the state qA will traverse to if delta is the next read symbol.
        self.transitions = []

    def isVerbose(self):
        return self.verbose
    
    def setStates(self, states):
        self.states = states

    def getStates(self):
        return self.states

    def setAlphabet(self, alphabet):
        self.alphabet = alphabet

    def getAlphabet(self):
        return self.alphabet

    def setStartState(self,startState):
        self.startState = startState

    def getStartState(self):
        return self.startState

    def setCurrentState(self, currentState):
        self.currentState = currentState

    def getCurrentState(self):
        return self.currentState

    def setFinalState(self, finalState):
        self.finalState = finalState

    def getFinalState(self):
        return self.finalState
    
    def addTransition(self, transition):
        self.transitions.append(transition)

    def getTransitions(self):
        return self.transitions

    def printDef(self):
        print("\n\n---Input DFA's definition---")

        print("\nStates: ")
        print(self.states)
        print("\nAlphabet: ")
        print(self.alphabet)
        print("\nStart State: ")
        print(self.startState)
        print("\nFinal State: ")
        print(self.finalState)

        print("\nTransitions: ")
        for i in range(0, len(self.transitions)):
            print(self.transitions[i])

        print("\n---End DFA Definition---\n")
