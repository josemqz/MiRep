#Retorna 
def bisection(f, a, b, n_iter):
    # CONSIDERE el caso que f(a) * f(b) sea positivo
    # RECUERDE no incluir valores repetidos al final de la secuencia del arreglo de salida para no tener errores igual a 0
    
    ratio = []
    res = []
    
    x = 0 # Calcular los valores de x para cada iteracion
    i = 0
    
    g = lambda x: f(x) - x
    
    #En caso que g(a) * g(b) sea positivo
    auxA = g(a)
    auxB = g(b)
    if auxA * auxB > 0:
        
        rango = 10.0
        infL = a - rango        
        supL = b + rango
        numR = 50
        recta = np.linspace(infL, supL, numR)
        j = 0
        
        while g(recta[j]) >= 0 and j < numR:
            j += 1
        
        rj = recta[j]
        print("g obtenido con rj =", rj, ":",g(rj))
        
        
        #debería tener un valor de g que sea negativo
        if rj < a:
            b = rj
        
        elif rj > b:
            a = rj
        
        else:
            #está entremedio
            if abs(rj - a) > abs(rj - b):
                b = rj
            else:
                a = rj
                
        #No es muy eficiente, pero funciona ;) (el tema es que estuve pensando en casos muy raros)

        
    while i < n_iter:
        
        x_ant = x
        x = (a + b) / 2
                
        #print("g: ", g(x))
        #print(x)
        res.append(x)
  
        if g(x) == 0.0 or x_ant == x:
            return res, ratio
        
        elif g(x) * g(b) < 0:
            a = x
        
        else:
            b = x
        
        i += 1
                
        if i > 1:
            ratio.append(abs((a + b) / 2 - x) / abs(x - x_ant))

    return res, ratio
