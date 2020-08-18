import numpy as np

#raiz de 2 está entre 1 y 2, se escoge un initial guess entre ellos
x = 1.1

n_max = 100
i = 0
while i < n_max:

    x_ant = x
    x = float('%.4f'%((x + 2/x)/2))
    print(x)
    if x_ant == x:
        break
    i += 1
