%% rotate для разностных списков.

%% with simple list
append([], L, L).
append([X|T], L, [X|R]) :- append(T, L, R).

rotate([H|T], R) :- append(T, [H], R).

%% rewrite with difference lists

%% append_d(L1,V1,L2,V2,L3,V3).
%% L1-V1
%% append_d(L1-V1,L2-V2,L3-V3):-V1=L2,L3=L1,V3=V2.
%% append_d(L1-B,B-V2,L3-V3):-B=B,L3=L1,V3=V2.
%% append_d(A-B,B-V2,A-V3):-A=A,V3=V2.
%% append_d(A-B,B-C,A-C):-C=C.
append_d(A-B, C-B, A-C).

%% rotate_d([H|T]-T1,R-S):-append_d(T-T1, [H|L]-L,R-S).
%% T1 -> [H|L]
%% rotate_d([H|T]-[H|L],R-S):-append_d(T-[H|L], [H|L]-L,R-S).
%% R ->T
%% rotate_d([H|T]-[H|L],T-S):-append_d(T-[H|L], [H|L]-L,T-S).
%% S -> L
%% rotate_d([H|T]-[H|L],T-L):-append_d(T-[H|L], [H|L]-L,T-L).
%% append_d can be remove

rotate_d([H|T]-[H|L],T-L).

%%  rotate_d([1,2,3,4,5|X]-X,R-[]).
