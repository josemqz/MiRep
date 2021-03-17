%%%%%%%%%%%%%%%%%%%   fsm.pl   %%%%%%%%%%%%%%%%%%%%%%%
% Para el archivo del autómata, las consultas serán del tipo:
%	’consulta(Palabra).’
% donde Palabra corresponde a la palabra cuya membresía al lenguaje correspondiente 
% al autómata será comprobada.

%alfabeto
%108: l.
%109: m.
%110: n.

%funciones de transición
d(q0,q0,108).
d(q0,q1,109).
d(q0,q2,110).
d(q1,q4,109).
d(q2,q1,108).
d(q2,q3,110).
d(q3,q4,110).
d(q3,q5,109).
d(q3,q6,108).
d(q4,q7,110).
d(q5,q8,110).
d(q6,q0,109).
d(q7,q8,110).
d(q8,q9,108).

%letras pertenecientes al alfabeto
alfb(108).
alfb(109).
alfb(110).

%condiciones de aceptacion
aceptacion([],q0):- write("Estado final: q0").
aceptacion([],q9):- write("Estado final: q9").

%cada letra (P1) debe pertenecer al alfabeto y debe existir una funcion de transición que lleve de Q a otro estado con P1
aceptacion([P1|P2], Q) :- alfb(P1), d(Q,Q2,P1), aceptacion(P2,Q2).

%función name(P,L) crea una lista L cuyos elementos corresponden a las letras de P
consulta(P) :- name(P, L), aceptacion(L,q0), !.

