#lang scheme

(define or
  (lambda (x y)
    (if (eq? 0 x)
        (if (eq? 0 y) 0 1)
        1
    )
  )
)

(define and
  (lambda (x y)
    (if (eq? 1 x)
        (if (eq? 1 y) 1 0)
        0
    )
  )
)


#|Funcion: operar
Descripcion: realiza la función entregada con cada par de elementos de dos listas de elementos binarios 
y se crea una lista con los resultados
Parametros:
fun funcion lambda
lista1 lista
lista2 lista
Retorno: lista con los resultados de las funciones
|#

(define operar
  (lambda (fun)
    (lambda (lista1 lista2)
      (let ((lf '()))

        (for-each
          (lambda (a b)

            (if (= 1 (fun a b)) (set! lf (append lf '(1)))
              (set! lf (append lf '(0)))
            )

          )lista1 lista2
        )
        lf
      )
    )
  )
)


((operar and) (list 0 1 1 1) (list 0 0 1 0))