
def ble():
    f = lambda x: x**3 + 4*x**2 - 10

    #h = labmda x: f(x)
    
    x0 = 1.1
    
    x = x0
    i = 0
    n_max = 1000
    while i < n_max:
    #    if x < 1 or x > 2:
     #       return "mal"
        
        x_ult = x
        x = f(x)
        
        print(x)
        
        if (i > 0 and x_ult == x) or f(x) == x:
            return x
        
        i += 1
        
    return x

ble()
