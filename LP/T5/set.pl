%%%%%%%%%%%%%%%%%%%   set.pl   %%%%%%%%%%%%%%%%%%%%%%%
% Para el archivo del diccionario, para cada función las consultas serán del tipo:
% Agregar:
%	‘agregar(K,E)’
%
% Obtener valor:
%	‘getValue(K)’
%
% Obtener llaves:
%	‘getKeys(_)’
%
% Obtener todos los valores:
%	‘getVs(_)’
%
% Largo:
%	‘largo(_)’
%
% K corresponde a la llave de cada elemento, mientras que E es su valor asociado.
% En las funciones con ‘_’, se puede introducir lo que sea, distinto de vacío.

%Se trabaja con hechos como elementos del diccionario.

%hecho base (es necesario definirlo para evitar fallos al agregar).
d([]).

%En caso de existir un elemento con la misma llave, se elimina y agrega el nuevo elemento.

agregar(K,E) :- d([K,_]), retract(d([K,_])), assertz(d([K,E])), !; assertz(d([K,E])), !.

getValue(K) :- d([K,E]), write(E), nl, !.

getKeys(_) :- findall(K, d([K,_]), L), write(L), nl, !.

getVs(_) :- findall(E, d([_,E]), L), write(L), nl, !.

largo(_) :- findall(X, d([X,_]), Ll), length(Ll,L), write(L), nl, !.

