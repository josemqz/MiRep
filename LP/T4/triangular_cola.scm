#lang scheme

#|Funcion: triangular_cola
Descripcion: se verifica si un número corresponde a un número triangular a través de recursión de cola
Parametros:
n entero
Retorno: true en caso positivo, false en negativo
|#

(define triangular_cola
  (lambda (n)
    (if (= n 0) #f
        (let htc ((s n) (i 0))
          (cond
            ((= s 0) #t)
            ((> s 0)
             (htc (- s i)(+ i 1) )
             )
            (else #f)
          )
        )
    )
  )
)
  
(triangular_cola 0)
(triangular_cola (/ 624 8))
(triangular_cola 55)