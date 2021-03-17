
f = lambda x: x**3 + 4*x**2 - 10

a = 1
b = 2

x = 0
i = 0
n_max = 100
while i < n_max:
    
    ant_x = x
    x = float('%.10f'%((b + a)/2))

    print(i, x)

    if f(x) == 0 or ant_x == x:
        break

    if f(a)*f(x) < 0:
        b = x
    else:
        a = x

    i += 1
