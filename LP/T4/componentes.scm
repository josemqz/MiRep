#lang scheme

#|
Funcion: remove_index
Descripcion: elimina un elemento de una lista L a partir de el índice i
Parametros:
L lista
i entero
Retorno: lista con elemento eliminado
|#
(define (remove_index L i)
  (if (null? L)
      null
      (if (= i 0)
          (cdr L)
          (cons (car L) (remove_index (cdr L) (- i 1)))
       )
    )
)

#|
Funcion: componentes
Descripcion: Funcion que recibe una lista de nodos y sus vecinos, y cuenta la cantidad de componentes del grafo
Parametros:
grafo lista
Retorno: numero de componentes del grafo
|#
(define (componentes grafo)
  (let ((Ll '()))
    (if (eq? grafo '())
        0
        (for-each
          (lambda (v)
            (let ((flag #f) (index_k 0) (listaH '()))

              (for-each
                (lambda (k) ;lista componentes

                  (if (member (car v) k)
                      (set! flag #t)
                      (for-each
                        (lambda (j)

                          (cond
                            ((member j k) (set! flag #t))
                          )
                        )(car (cdr v))
                      )
                   )

                   (cond
                     (flag
                       (set! listaH (append listaH k))
                       (set! listaH (append listaH (cons (car v) (car (cdr v)))))
                       (set! listaH (remove-duplicates listaH))
                       (set! Ll (remove_index Ll index_k))
                       (set! Ll (append Ll (list listaH)))
                     )
                   )

                   (set! index_k (+ index_k 1))
                )Ll
              )
              (cond
                ((not flag) (set! Ll (append Ll (list (cons (car v) (car (cdr v)))))))
                ;break
              )
            )
          )grafo
        )
    )
    (length Ll)
  )
)

(componentes '((1 (2 2)) (2 (4)) (3 (6)) (4 (2 1)) (5 (6)) (6 (5)) (7 ()) (89 ())))
(componentes '((1 ())))
