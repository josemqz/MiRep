def fpi(g, x_0, n_iter):
    # CONSIDERE que el metodo puede no converger
    # RECUERDE no incluir valores repetidos al final de la secuencia del arreglo de salida para no tener errores igual a 0
    
    res = []
    
    x = 0 # Calcular los valores de x para cada iteracion
    i = 0
    while i < n_iter:
        
        x_ant = x
        x = g(x)
        
        res.append(x)
        print(x)
        print("\n")
        
        if x_ant == x:
            return res
         
        i += 1
    
    return res

g = lambda x:x**3+4*x**2-10

fpi(g, 1, 1000)

