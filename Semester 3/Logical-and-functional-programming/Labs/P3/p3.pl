% 1. Write a predicate to generate the list of all subsets with all elements of a given list. 
% Eg: [2, 3, 4] N=2 => [[2,3],[2,4],[3,4]]


/* Mathematical model
 combinations(l1...ln, k) =
 	[], k = 0
 	l1 + combinations(l2...ln, k - 1), k > 0
 	combinations(l2...ln, k), k > 0  */

% combinations(L:list, K:number, R:list)
% flow model (i, o)

combinations(_, 0, []).
combinations([H|T], K, [H|R]) :-
    K > 0,
    NK is K - 1,
    combinations(T, NK, R).
combinations([_|T], K, R) :-
    K > 0,
    combinations(T, K, R).


% allSolutions(L:list, N:number, R:list)
% flow model (i, i, o) 

allSolutions(L, N, R) :-
    findall(RPartial, combinations(L, N, RPartial), R).

test_allSolutions:-
    allSolutions([2, 3, 4], 2, [[2, 3], [2, 4], [3, 4]]).
