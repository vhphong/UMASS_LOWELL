# UMass Lowell
# Organization of Programming Languages (OPL)
# by Phong Vo - Spring 2019
# Assignment 1
# reference link: https://rosettacode.org/wiki/Permutations#Prolog

:- use_module(library(clpfd)). 	# using the clpfd library
 
permut_clpfd(L, N) :-
    length(L, N),
    L ins 1..N,
    all_different(L),
    label(L).
