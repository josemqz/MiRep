#lang scheme

#|Funcion: suma_help
Descripcion: realiza la busqueda de un nodo especifico, mientras se suma el valor de los recorridos, a partir de los
hijos de la raíz
Parametros:
arb lista
num entero
sum entero
Retorno: entero correspondiente a la suma de los nodos recorridos para llegar a uno específico, en caso de existir
|#

(define suma_help
  (lambda (arb num sum)
    (cond
      ((eq? arb '()) null)
      ((number? (car arb))
        (set! sum (+ sum (car arb)))
        (cond
          ((eq? (car arb) num) sum)
          ((< num (car arb)) (suma_help (car(cdr arb)) num sum))
          (else (suma_help (car(cdr(cdr arb))) num sum))
        )
      )
      (else null)
    )
  )
)

#|Funcion: suma_arbol
Descripcion: busca un número en un árbol binario de búsqueda y suma los nodos recorridos. Comienza en la raíz y luego
utiliza una funcion auxiliar para continuar con los hijos
Parametros:
arbol lista
numero entero
Retorno: nada
|#

(define suma_arbol
  (lambda (arbol numero)
    (let ((suma 0))
      (if (not(eq? arbol '()))
        (set! suma (+ suma (car arbol)))
        ('())
      )
      (cond
        ((eq? (car arbol) numero) numero)
        ((< numero (car arbol)) (suma_help (car(cdr arbol)) numero suma))
        (else (suma_help (car(cdr(cdr arbol))) numero suma))
      )
    )
  )
)

(suma_arbol '(8 (3 (1 () ()) (6 (4 () ()) () )) (10 () (45 () (50 () ())))) 50)