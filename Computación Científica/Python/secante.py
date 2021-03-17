def f(x):
    return x**3+x-1
    
x = 0
y = 1
while x != y:
    z = y - (f(y)*(y-x))/(f(y)-f(x))
    print(z)
    print("x: ",x,"y: ",y)
    x = y
    y = z

