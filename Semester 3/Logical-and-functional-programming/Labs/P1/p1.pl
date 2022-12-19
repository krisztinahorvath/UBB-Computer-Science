/* 5.
a. Write a predicate to compute the union of two sets.
b. Write a predicate to determine the set of all the pairs of elements in a list.
Eg.: L = [a b c d] => [[a b] [a c] [a d] [b c] [b d] [c d]]. */
 
% a

/* Mathematic model:
     remove_occurences(l1...ln, e) =
     [], n = 0
     remove_occurences(l2...ln, e), l1 = e
     l1 + remove_occurences(l2...ln, e), l1 != e
*/

% remove_occurences(L:list, E:number, R:list)
% remove_occurences(i, i, o)

remove_occurences([], _, []).
remove_occurences([H|T], E, R) :- H =:= E,
    remove_occurences(T, E, R).
remove_occurences([H|T], E, [H|R]) :- H =\= E,
    remove_occurences(T, E, R).

 /*Mathematic model:
    union(a1...an, b1...bm) =
  	[], n = 0 and m = 0
 	a1 + union(remove_occurences(a1...an, a1), remove_occurences(b1...bm, a1)), n > 0
 	union(b1...bm, []), n = 0*/

% union(A:list, B:list, R:list)
% union(i, i, o)

union([], [], []).
union([H|T], B, [H|R]) :-
    remove_occurences([H|T], H, R1),
    remove_occurences(B, H, R2),
    union(R1, R2, R).
union([], B, R) :-
      union(B, [], R).

% b

/* Mathematic model:
  sets(l1...ln, k) =
  	[], k = 0
  	l1 + sets(l2...ln, k - 1), k > 0
  	sets(l2...ln, k), k > 0*/

% sets(L:list, K:number, R:list)
% sets(i, i, o)

sets(_, 0, []) :- !.
sets([H|T], K, [H|R]) :-
    K1 is K - 1,
    sets(T, K1, R).
sets([_|T], K, R) :-
    sets(T, K, R).


/* Mathematic model:
  gen_sets(l1..ln) =
 	[], n = 0
 	findall(sets(l1...ln, 2))

  gen_sets(L:list, R:list)
  gen_sets(i, o)*/

% list, goal, and template

gen_sets([], []).
gen_sets(L, R) :- findall(RS, sets(L, 2, RS), R).


/* 
union([1,2,3],[5],[1,2,3,5]),
union([2],[6],[2,6]),
union([1,2,3],[2,3],[1,2,3]),
union([],[2],[2]),
union([],[],[]),

gen_sets([a,b,c,d],[[a,b],[a,c],[a,d],[b,c],[b,d],[c,d]]),
gen_sets([1,2,3],[[1,2],[1,3],[2,3]]),
gen_sets([],[]),
gen_sets([a,b,c,d,e],[[a,b],[a,c],[a,d],[a,e],[b,c],[b,d],[b,e],[c,d],[c,e],[d,e]]).
*/
