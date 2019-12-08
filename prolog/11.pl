%% задачи о трёх программистах. 
my_name(friend(X, _, _), X).
country(friend(_, Y, _), Y).
sport(friend(_, _, Z), Z).

did_better(X, Y, [X, Y, _]).
did_better(X, Y, [X, _, Y]).
did_better(X, Y, [_, X, Y]).

first(X, [X, _, _]).

structure(test, [friend(_,_,_),
                 friend(_,_,_),
                 friend(_,_,_)]).

clues(test, Friends, 
    [
    (did_better(F1C1, F2C1, Friends),
        my_name(F1C1, mike),
        sport(F1C1, basketball),
        country(F2C1, usa)),
    (did_better(F1C2, F2C2, Friends),
        my_name(F1C2, lee),
        country(F1C2, korea),
        sport(F2C2, tennis)),
    (first(F1C3, Friends),
        sport(F1C3, cricket))]).

member_(H, [H|_]).
member_(X, [_|T]):-member_(X, T).

solve_([H|T]):-H, solve_(T).
solve_([]).

queries(test, Friends, 
    [member_(Q1, Friends),
        country(Q1, australia),
        my_name(Q1, Name),
        member_(Q2, Friends),
        my_name(Q2, richard),
        sport(Q2, Sport)],
    [['the australian is ', Name], ['Richard likes ', Sport]]).

test_p(Pname, puzzle(Clues, Queries, Solution)):-
    structure(Pname, Structure),
    clues(Pname, Structure, Clues),
    queries(Pname, Structure, Queries, Solution).

solve_p(puzzle(C, Q, S), S):-solve_(C), solve_(Q).


find_friends(S):-test_p(test, puzzle(C, Q, S)), solve_p(puzzle(C, Q, S), S).

