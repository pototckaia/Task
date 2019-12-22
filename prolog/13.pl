member_(H, [H|_]).
member_(X, [_|T]) :- member_(X, T).

select_(X, [X|T], T).
select_(X, [H|T], [H|T1]) :- select_(X, T, T1).

insert_(X, [], [X]).
insert_(X, [H|T], [X, H|T]) :- precedes(X, H).
insert_(X, [H|T], [H|T1]) :-
    precedes(H, X),
    insert_(X, T, T1).

precedes(wolf, goat).
precedes(wolf, cabbage).
precedes(goat, cabbage).

illegal(Coast) :- member_(wolf, Coast), member_(goat, Coast).
illegal(Coast) :- member_(goat, Coast), member_(cabbage, Coast).

legal(state(left, _, Right)) :- not(illegal(Right)).
legal(state(right, Left, _)) :- not(illegal(Left)).

update_items(alone, _, Left, Right, Left, Right).
update_items(Item, left, Left, Right, NewLeft, NewRight) :-
    select_(Item, Right, NewRight),
    insert_(Item, Left, NewLeft).
update_items(Item, right, Left, Right, NewLeft, NewRight) :-
    select_(Item, Left, NewLeft),
    insert_(Item, Right, NewRight).

update_coast(left, right).
update_coast(right, left).

update(state(Coast, Left, Right), Item, state(NewCoast, NewLeft, NewRight)) :-
    update_coast(Coast, NewCoast),
    update_items(Item, NewCoast, Left, Right, NewLeft, NewRight).

move(state(left, Left, _), Item) :- member_(Item, Left).
move(state(right, _, Right), Item) :- member_(Item, Right).
move(state(_, _, _), alone).

final_state(state(right, [], [wolf, goat, cabbage])).

solve_dfs(State, _, []) :- final_state(State).
solve_dfs(State, History, [Move | Moves]) :-
    move(State, Move),
    update(State, Move, NewState),
    legal(NewState),
    not(member_(NewState, History)),
    solve_dfs(NewState, [NewState | History], Moves).

initial_state(state, state(left, [wolf, goat, cabbage], [])).

test_dfs(Name, Moves) :-
    initial_state(Name, State),
    solve_dfs(State, [State], Moves).

solve_puzzle(X):-test_dfs(state, X).

/*  Hill climbing  for problem solving*/

hill_climb(State, Move) :-
    findall(M, move(State, M), Moves),
    evaluate_and_order(Moves, State, [], MVs),
    member((Move, _), MVs).

solve_hill_climb(State, _, []) :- final_state(State).
solve_hill_climb(State, History, [Move | Moves]) :-
    hill_climb(State, Move),
    update(State, Move, State1),
    legal(State1),
    not(member(State1, History)),
    solve_hill_climb(State1, [State1 | History], Moves).



value(state(_, _, R), Value) :- length(R, Value).

/*
    evaluate_and_order(Moves, State, SoFar, OrderedMVs) :-
    All the Moves from the current State are evaluated and
    ordered as OrderedMVs. SoFar is an accumulator for
    partial computations.
*/
evaluate_and_order([Move | Moves], State, MVs, OrderedMVs) :-
    update(State, Move, State1),
    value(State1, Value),
    insert((Move, Value), MVs, MVs1),
    evaluate_and_order(Moves, State, MVs1, OrderedMVs).

evaluate_and_order([], _, MVs, MVs).

insert(MV, [], [MV]).
insert((M, V), [(M1, V1) | MVs], [(M, V), (M1, V1) | MVs]) :- V >= V1.
insert((M, V), [(M1, V1) | MVs], [(M1, V1) | MVs1]) :- V < V1, insert((M, V), MVs, MVs1).

/*  Testing the Framework */
test_hill_climb(state, Moves)  :-
    initial_state(state, State),
    solve_hill_climb(State, [State], Moves).

solve_puzzle_hc(X) :- test_hill_climb(state, X).




