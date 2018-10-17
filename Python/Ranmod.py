#!/usr/bin/python
import random

abc = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
rols = []
noms = []
aps = []
anio = []

for i in range(100):
    rols.append(random.randrange(100000000,999999999,1))
    anio.append(random.randrange(2010,2018,1))
    for y in range(15):
        noms.append(random.shuffle(abc))
        aps.append(random.shuffle(abc))
    #}
#}

#f = open("alumnos.txt","a")
