#lang scheme

#|
Funcion: biseccion
Descripcion: calcula una raíz de un polinomio dado al evaluar sucesivamente los puntos correspondientes
a la mitad del intervalo correspondiente en cada iteración, el que se irá reduciendo a la mitad.
Parametros:
func funcion
intervalo lista
iter entero
Retorno: solución del polinomio en caso exitoso.
|#

(define biseccion
  (lambda (func)
    (lambda (intervalo iter)
      (if (eq? 0 iter)
          (display "intervalos concluidos")
          (if (< 0 (* (func (car intervalo)) (func (car (cdr intervalo)))))
               (display "intervalo incorrecto")
               (let ((mit (/ (+ (car (cdr intervalo)) (car intervalo)) 2)) (neg 0) (pos 0))
                 (cond
                   ((> 0 (func (car intervalo))) (set! neg (car intervalo)) (set! pos (car (cdr intervalo))))
                   (else (set! pos (car intervalo)) (set! neg (car (cdr intervalo))))
                 )
                 (cond
                   ((= 0 (func mit)) mit)
                   ((< 0 (func mit)) ;mitad positiva
                     (if (< mit neg)
                         (biseccion func (list mit neg) (- iter 1))
                         (biseccion func (list neg mit) (- iter 1))
                     )
                   )
                   (else
                     (if (< mit pos)
                         (biseccion func (list mit pos) (- iter 1))
                         (biseccion func (list pos mit) (- iter 1))
                   ))
                 )
               )
           )
       )
     )
  )
)


((biseccion (lambda(x) (+ (* x x x) (* 3 x x) -2))) '(-3 1) 1000)