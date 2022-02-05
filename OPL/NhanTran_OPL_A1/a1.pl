#swipl
#['a1.pl'].
#permut_Prolog(P, [number, number, number]), writeln(P), fail.


permut_Prolog([], []).
permut_Prolog([H | T], NL) :-
	select(H, NL, NL1),
	permut_Prolog(T, NL1).
  
#https://rosettacode.org/wiki/Permutations?fbclid=IwAR0SwqCOQvPp5wMOVpU4kExXv21b41YarBfgF5Flv207itH57CqLf0YEZIs#Prolog