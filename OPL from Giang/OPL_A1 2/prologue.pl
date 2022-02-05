:- use_module(library(clpfd)).

# combination funtion
comb_clpfd(M, N, L) :-

# Length funtion to get the lengts for combination
length(L, M),
L ins 1..N,
chain(L, #<),
label(L).


