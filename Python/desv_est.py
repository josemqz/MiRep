def desviacion_estandar(valores):
	s = 0
	x = 0
	prom = sum(valores)/len(valores)
	for i in valores:
		x = (i - prom)**2
		s = s + x
	d = s/len(valores)
	resultado = d**(1.0/2)
	return resultado

valores = [2, 3, 8, 10, 0, 1, 1.5, 1]
print desviacion_estandar(valores)