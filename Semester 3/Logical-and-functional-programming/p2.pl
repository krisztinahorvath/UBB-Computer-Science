/*
12.
a. Define a predicate to add after every element from a list, 
the divisors of that number.
b. For a heterogeneous list, formed from integer numbers and list of numbers, 
define a predicate to add in every sublist the divisors of every element.
Eg.: [1, [2, 5, 7], 4, 5, [1, 4], 3, 2, [6, 2, 1], 4, [7, 2, 8, 1], 2] 
=>[1, [2, 5, 7], 4, 5, [1, 4, 2], 3, 2, [6, 2, 3, 2, 1], 4, [7, 2, 8, 2, 4, 1], 2] 
*/

% a.Define a predicate to add after every element from a list, 
% the divisors of that number.


/* Mathematical model
 insertDivs(l1...ln, div, list) =
 	list, n <= 2 or n = div
 	div + insertDivs(l2...ln, div + 1, list), n % div = 0
 	insertDivs(l2...ln, div + 1, list), otherwise
*/

% insertDivs(N:number, Div:number, L:list, R:list)
% flow model insertDivs(i, i, i, o)

insertDivs(N, _, L, L):- N =< 2.
insertDivs(N, N, L, L). % if the divisor is the given number
insertDivs(N, Div, L, [Div|R]):- % we put the found divisors as the head of the resulting list in rev order of finding
    N mod Div =:= 0, !,
    NextDiv is Div + 1,
    insertDivs(N, NextDiv, L, R).
insertDivs(N, Div, L, R):-
    NextDiv is Div + 1,
    insertDivs(N, NextDiv, L, R).

/* Mathematical model
 divs(l1...ln) =
 	[], n = 0
 	insertDivs(l1, 2) + divs(l2...ln), otherwise
*/

% divs(L:list, R:list)
% flow model: divs(i, o) (i,, i)

divs([],[]).
divs([H|T], [H|R]):- % add H in front of the list changed by inserting the divisors of it
    divs(T, Res), % does this until we have two empty lists and we can take the last elem and find its divs
    insertDivs(H, 2, Res, R). % inserts the divs of the last elem from the initial list to the begin of the resulting list

test_divs:-
    divs([2,5,7,9], [2,5,7,9,3]),
    divs([10, 1], [10,2,5,1]),
    divs([2],[2]),
    divs([6,6,9,5],[6,2,3,6,2,3,9,3,5]),
    divs([],[]).


/*
b. For a heterogeneous list, formed from integer numbers and list of numbers, 
define a predicate to add in every sublist the divisors of every element.
Eg.: [1, [2, 5, 7], 4, 5, [1, 4], 3, 2, [6, 2, 1], 4, [7, 2, 8, 1], 2] 
=>[1, [2, 5, 7], 4, 5, [1, 4, 2], 3, 2, [6, 2, 3, 2, 1], 4, [7, 2, 8, 2, 4, 1], 2]  
*/

/* Mathematical model
 hetList(l1...ln) = 
 	[], n = 0
 	divs(l1) + hetList(l2...ln), is_list(l1) = True
 	l1 + hetList(l2...ln), otherwise
*/

% hetList(L:list, R:list)
% flow model: hetList(i, o) (i, i)

hetList([],[]).
hetList([H|T], [Res|R]):- % add the changed lists with the divs in the result
    is_list(H), !, 
    divs(H, Res),
    hetList(T, R). % taking the next elem in the het list
hetList([H|T], [H|R]):- % if it isn't a list just add it to the res
    hetList(T, R).

test_hetList:-
    hetList([1, [2, 5, 7], 4, 5, [1, 4], 3, 2, [6, 2, 1], 4, [7, 2, 8, 1], 2], [1, [2, 5, 7], 4, 5, [1, 4, 2], 3, 2, [6, 2, 3, 2, 1], 4, [7, 2, 8, 2, 4, 1], 2]),
    hetList([12, 9, [7], [2, 9]], [12, 9, [7], [2, 9, 3]]),
    hetList([1, 10, 3, []], [1, 10, 3, []]),
    hetList([5, [10], 10], [5, [10, 2, 5], 10]).

     
