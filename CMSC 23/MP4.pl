%Propositions in item 1
female(scarlet).
female(white).
female(peacock).
female(orchid).
% Propositions in item 2
male(plum).
male(mustard).
male(green).
%Proposition in item 3 (Miss Scarlet hates Rev. Green)
hates(scarlet, green).
% Proposition in item 4
hates(green, scarlet).
% Propositions in item 5
hates(plum, white).
hates(white, plum).
% Propositions in item 6
hates(mustard, X) :- female(X).
hates(mustard, plum).
% Propositions in item 7
likes(scarlet, orchid).
likes(peacock, orchid).
% Proposition in item 8
likes(orchid, peacock).
% Proposition in item 9
likes(scarlet, white).
% Propositions in item 10
likes(scarlet, plum).
likes(plum, scarlet).
% Propositions in item 11
likes(plum, X) :- hates(mustard, X).
%Rule in item 12 (People who hate each other are enemies)
enemies(X,Y) :- hates(X,Y), hates(Y,X).
% Rule in item 13
friends(X,Y) :- likes(X,Y), likes(Y,X).
% Rule in item 14
friends(X, Y) :- enemies(X, Z), enemies(Z, Y).