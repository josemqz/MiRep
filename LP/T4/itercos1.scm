#lang racket

#|Funcion: factorial
Descripcion: realiza la funcion factorial de un número
Parametros:
n entero
Retorno: factorial de n
|#

( define factorial
   ( lambda (n)
      ( let fact ((i n))
         ( if (= i 0)
              1
              (* i ( factorial (- i 1) ) )
          )
       )
    )
)

#|Funcion: iter_cos
Descripcion: realiza una aproximacion del coseno de un valor dado a través de sumatorias (>n >precisión)
Parametros:
x entero
n entero
Retorno: valor aproximado del coseno de x
|#

(define iter_cos
  (lambda (x n)
    (if (> n 0)
      (let ((i 0) (s 0))
        (do ((i 0 (+ i 1)))
          ((> i (- n 1)))
          (set! s (+ s (/ (* (expt -1 i) (expt x (* 2 i))) (factorial(* 2 i))) ))
        )
        s
      )
      (display "wrong")
    )
  )
)      

(iter_cos (/ pi 2) 10)