%%%%%%%%%%%%%%%%%   Ciudades.pl   %%%%%%%%%%%%%%%%%%%
% Para el archivo de ciudades, las consultas son del tipo:
%	'todos_caminos(ciudad_actual, Lista, M).'
% del cual, la lista retornada corresponde a las ciudades a la cual es
% posible llegar desde la actual con la cantidad de combustible entregada (M).

% Babylon Nippur CedarForest
% BloodTemple Ziggurat Uruk
% Cutah Ur Eridu Abzu Eresh
% Ebih Nineveh Assur

% path(x,Y,N)
% X -> Y con coste N
path(ba, ni, 3).
path(ni, eb, 9).
path(ur, ba, 2).
path(ur, ni, 6).
path(eb, ur, 10).
path(eb, en, 3).
path(en, ab, 6).
path(ab, zi, 8).
path(ce, ba, 9).
path(ce, urk, 4).
path(zi, ba, 8).
path(zi, ni, 7).
path(zi, ce, 5).
path(cu, ba, 3).
path(cu, ass, 5).
path(ass, erh, 10).
path(erh, cu, 8).
path(erh, urk, 7).
path(erh, nih, 6).
path(nih, ass, 9).
path(er, en, 3).
path(er, nih, 3).
path(er, erh, 1).
path(urk, er, 4).
path(urk, en, 1).
path(urk, ab, 9).

%%% pathos
% encuentra todos los posibles caminos entre un par de nodos
pathos(X,Y,P):-
    pathos(X,Y,P,[X]).
pathos(X,Y,P,_):-
    path(X,Y,P).
pathos(X,Y,P, Temp):-
    path(X,B,P1), not(member(B,Temp)),
    append(Temp,[B],Temp1), pathos(B,Y,P2,Temp1), P is P1 + P2.


todos_caminos(X, L1, Z) :- 
    findall(Y,(pathos(X, Y, V), V =< Z),L2), sort(L2,L1).

