:- use_module(library(clpfd)).

list_length([], 0).
list_length([_|Tail], Length) :-
    Length #= Tail_length + 1,
    list_length(Tail, Tail_length).

emptylist([]).

list_last([E], E).
list_last([_|Tail], E) :-
    list_last(Tail, E).

list_member([E|_], E).
list_member([_|Tail], E) :-
    list_member(Tail, E).

list_sum([], 0).
list_sum([Head|Tail], N) :-
    N #= Head + Tailsum,
    list_sum(Tail, Tailsum).

list_upperbound([], _).
list_upperbound([Head|Tail], N) :-
    N #>= Head,
    list_upperbound(Tail, N).


list_max([E], E).
list_max([Head, Next|Tail], N) :-
    N #= max(Head, Tailmax),
    list_max([Next|Tail], Tailmax).


list_subset(_, []).
list_subset(L, [Head|Tail]) :-
    list_member(L, Head),
    list_subset(L, Tail).