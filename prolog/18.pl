%%   ABC
%% x
%%    BC
%% ________
%% DEFBC
%% с использованием средств из библиотеки распространения ограничений.

%% use_module(library(clpfd)).

puzzle2([A, B, C], [B, C], [D, E, F, B, C]):-
       Vs = [A, B, C, D, E, F],
       Vs ins 0..9, all_different(Vs),
       (A * 100 + B * 10 + C) * (B * 10 + C) #=
       (D * 10000 + E * 1000 + F * 100 + B * 10 + C),
       A #\= 0, B #\= 0, D #\= 0, label(Vs).
