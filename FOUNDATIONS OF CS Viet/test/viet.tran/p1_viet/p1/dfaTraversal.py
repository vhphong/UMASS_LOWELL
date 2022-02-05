from dfaClass import DFA

def transition(dfa, delta):
    validTransitions = True
    transitions = dfa.getTransitions()
    currentState = dfa.getCurrentState()

    if dfa.isVerbose():
        print("Current State: " + currentState + "  Symbol: " + delta, end = " ")

    for i in range(0, len(transitions)):
        #If a transition from the current state using the passed symbol is found, transfer to it.
        if(transitions[i][0] == currentState and transitions[i][1] == delta):
            dfa.setCurrentState(transitions[i][2])
            if dfa.isVerbose():
                print(" --> New State: " + transitions[i][2])
            break;
        elif(i == len(transitions)-1):
            validTransitions = False
            print("ERROR: Required transition missing. Input not accepted.")
            
    return validTransitions
                
   
def runDFA(usrInput, dfa):
    alphabet = dfa.getAlphabet()
    validInputSymbs = True

    if dfa.isVerbose():
        print("Input: " + usrInput)
        
    for i in range(0, len(usrInput)):
        if(usrInput[i] in alphabet) == False:
            validInputSymbs = False
            print("Invalid symbol: " + usrInput[i] + ". Input not accepted by the machine.")
            print(usrInput + " --> NOT ACCEPTED\n")

    if validInputSymbs:
        dfa.setCurrentState(dfa.getStartState())
        for i in range (0, len(usrInput)):
           if(transition(dfa, usrInput[i])) == False:
               dfa.setCurrentState("Missing State")
               break;

        if dfa.getCurrentState() in dfa.getFinalState():
            print(usrInput + " --> ACCEPTED\n")
        else:
            print(usrInput + " --> NOT ACCEPTED\n")
