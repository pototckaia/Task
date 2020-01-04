%% Однажды крестьянину понадобилось перевезти через реку волка, козу и капусту. 
%% У крестьянина есть лодка, в которой может поместиться, 
%% кроме самого крестьянина, только один объект — или волк, 
%% или коза, или капуста. Если крестьянин оставит без присмотра 
%% волка с козой, то волк съест козу; если крестьянин оставит 
%% без присмотра козу с капустой, коза съест капусту.

%% Как крестьянину перевезти на другой берег всё своё имущество в целости и сохранности?

precedes(wolf, goat).
precedes(wolf, cabbage).
precedes(goat, cabbage).

illegal(Coast) :- member(wolf, Coast), member(goat, Coast).
illegal(Coast) :- member(goat, Coast), member(cabbage, Coast).

legal(state(left, _, Right)) :- not(illegal(Right)).
legal(state(right, Left, _)) :- not(illegal(Left)).

insert_precedes(X, [], [X]).
insert_precedes(X, [H|T], [X, H|T]) :- precedes(X, H).
insert_precedes(X, [H|T], [H|T1]) :- precedes(H, X), insert_precedes(X, T, T1).

update_coast(left, right).
update_coast(right, left).

%% Item, NewCoast, Left, Right, NewLeft, NewRight
update_items(alone, _, Left, Right, Left, Right).
%% select(?Elem, ?List1, ?List2) - Is true when List1, with Elem removed, results in List2. 
update_items(Item, left, Left, Right, NewLeft, NewRight) :-
    select(Item, Right, NewRight),
    insert_precedes(Item, Left, NewLeft).
update_items(Item, right, Left, Right, NewLeft, NewRight) :-
    select(Item, Left, NewLeft),
    insert_precedes(Item, Right, NewRight).

update(state(Coast, Left, Right), Item, state(NewCoast, NewLeft, NewRight)) :-
    update_coast(Coast, NewCoast),
    update_items(Item, NewCoast, Left, Right, NewLeft, NewRight).

move(state(left, Left, _), Item) :- member(Item, Left).
move(state(right, _, Right), Item) :- member(Item, Right).
move(state(_, _, _), alone).

initial_state(state, state(left, [wolf, goat, cabbage], [])).
final_state(state(right, [], [wolf, goat, cabbage])).

solve_dfs(State, _, []) :- final_state(State).
solve_dfs(State, History, [Move|Moves]) :-
    move(State, Move),
    update(State, Move, NewState),
    legal(NewState),
    not(member(NewState, History)),
    solve_dfs(NewState, [NewState|History], Moves).

test_dfs(Name, Moves) :-
    initial_state(Name, State),
    solve_dfs(State, [State], Moves).

solve_puzzle_dfs(X):-test_dfs(state, X).

/*  Hill climbing  for problem solving*/


%% length(?List, ?Int)
value(state(_, _, R), Value) :- length(R, Value).

insert(MV, [], [MV]).
insert((M, V), [(M1, V1) | MVs], [(M, V), (M1, V1) | MVs]) :- V >= V1.
insert((M, V), [(M1, V1) | MVs], [(M1, V1) | MVs1]) :- V < V1, insert((M, V), MVs, MVs1).

%% evaluate_and_order(Moves, State, SoFar, OrderedMVs) :-
%% All the Moves from the current State are evaluated and
%% ordered as OrderedMVs. SoFar is an accumulator for
%% partial computations.

evaluate_and_order([], _, MVs, MVs).
evaluate_and_order([Move|Moves], State, MVs, OrderedMVs) :-
    update(State, Move, NewState),
    value(NewState, Value),
    insert((Move, Value), MVs, MVs1),
    evaluate_and_order(Moves, State, MVs1, OrderedMVs).


%% findall(+Template, :Goal, -Bag)
%% Create a list of the instantiations Template gets successively 
%% on backtracking over Goal and unify the result with Bag. 
%% Succeeds with an empty list if Goal has no solutions. 

hill_climb(State, Move) :-
    findall(M, move(State, M), Moves),
    evaluate_and_order(Moves, State, [], MVs),
    member((Move, _), MVs).

solve_hill_climb(State, _, []) :- final_state(State).
solve_hill_climb(State, History, [Move|Moves]) :-
    hill_climb(State, Move),
    update(State, Move, NewState),
    legal(NewState),
    not(member(NewState, History)),
    solve_hill_climb(NewState, [NewState|History], Moves).

/*  Testing the Framework */
test_hill_climb(state, Moves)  :-
    initial_state(state, State),
    solve_hill_climb(State, [State], Moves).

solve_puzzle_hc(X) :- test_hill_climb(state, X).