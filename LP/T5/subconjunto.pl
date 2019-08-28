%%%%%%%%%%%%%%%%   Subconjunto.pl   %%%%%%%%%%%%%%%%%
% Para el archivo subconjunto, las consultas serán del tipo:
%	'allSumOf(conjunto_enteros, X, Lista).'
% donde Lista correspode a todos los subconjuntos del conjunto de enteros 
% en el cual cada subconjunto suma exactamente el entero X.

%%%% subconjunto:
% verifica si el conjunto X es subconjunto de L
% si se usa X como variable, subconjunto entrega todos
% los posibles subconjuntos de L

subconjunto([],[]).
subconjunto([X|L1],[X|L2]):-
       subconjunto(L1,L2).
subconjunto(L1,[_|L2]):-
       subconjunto(L1,L2).

%%% allsumof
% verifica si la suma de cada subconjunto X  de L es exactamente Z
% entrega en la lista R todos los correspondientes

allSumOf(L, Z, R):- 
    findall(X, (subconjunto(X,L), sumlist(X,C), C == Z), R).


