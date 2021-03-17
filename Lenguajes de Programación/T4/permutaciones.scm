#lang racket

#|Funcion: permutaciones
Descripcion: crea una lista con todas las permutaciones posibles de una lista dada
Parametros:
lista lista
Retorno: lista con sublistas correspondientes a las permutaciones de otra lista
|#

(define permutaciones
  (lambda (lista)
    (let (lpot '())
      (for-each
        (lambda (x)
          (do (potN '() (eq? (length? (cdr lista)) 2)
              (
               ;Switch
#|
123456
123465
123564
123546
123645
123654
124
|#