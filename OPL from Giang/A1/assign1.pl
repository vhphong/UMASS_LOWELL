:- use_module(library(clpfd)). %using the clpfd library
 
combination(K, N, L) :- %function
    length(L, K), %boolean expression to compared L with K, if L == K, the expression returns false
    L ins 1..N, %set domain of list L to 1 until N
    chain(L, #<), % chain takes L(finite set of domains) and chain it with all values less than it. 
    label(L). %iterate L until the N(final value)
  
