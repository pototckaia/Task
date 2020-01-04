%% dutch для разностных списков и
%% варианта с обратным порядоком раскрашенных элементов
%% в результирующем списке

%% Флаг Нидерландов состоит из трех цветов: красного, белого и синего.
%% Получая шары этих трех цветов, расположенных в случайном порядке,
%% задача состоит в том, чтобы организовать их таким образом,
%% что все шары одного цвета были вместе, а и их общие цвета шли в
%% порядке как на данном флаге.


%%  строит три одноцветных списка.
distribute([], [], [], []).
distribute([r(H)|T], [r(H)|R], W, B) :- distribute(T, R, W, B).
distribute([w(H)|T], R, [w(H)|W], B) :- distribute(T, R, W, B).
distribute([b(H)|T], R, W, [b(H)|B]) :- distribute(T, R, W, B).

dutch(L, RWB) :-
    distribute(L, R, W, B),
    append(W, B, WB),
    append(R, WB, RWB).

%% Решение задачи о голландском флаге является примером программы,
%% в которой независимо строятся части решения, объединяемые
%% в конце решения.

dutch_d(L, RWB-[]) :-
    distr_d(L, RWB-WB, WB-B, B-[]).
%% RWB список элементов списка Xs, упорядоченных по цвету

distr_d([r(H)|T], [r(H)|R]-R1, W, B) :-distr_d(T, R-R1, W, B).
distr_d([w(H)|T], R, [w(H)|W]-W1, B) :-distr_d(T, R, W-W1, B).
distr_d([b(H)|T], R, W, [b(H)|B]-B1) :-distr_d(T, R, W, B-B1).
distr_d([], R-R, W-W, B-B).



reverse(L,R):-  reverse_d(L,R-[]).
reverse_d([],X-X).
reverse_d([H|T],L-X) :- reverse_d(T,L-[H|X]).

dutch_rev(L, RWB-[]) :-
    distr_re(L, RWB-WB, WB-B, B-[]).

distr_re([r(H)|T], R-R1, W, B) :-distr_re(T, R-[r(H)|R1], W, B).
distr_re([w(H)|T], R, W-W1, B) :-distr_re(T, R, W-[w(H)|W1], B).
distr_re([b(H)|T], R, W, B-B1) :-distr_re(T, R, W, B-[b(H)|B1]).
distr_re([], R-R, W-W, B-B).

%% пример
%% dutch_d([b(1),r(2),b(3),w(4),b(5),r(6)],R-[]).
%% dutch_rev([b(1),r(2),b(3),w(4),b(5),r(6)],R-[]).


