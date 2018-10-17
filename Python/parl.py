band = True
hr_laborales=0
S_inoperante = ""
D_inoperante = ""
while band:
	flag = True
	nombre_parlamentario = raw_input("nombre parlamentario:")
	if nombre_parlamentario != "Fin":
		cargo = raw_input("cargo:")
		if cargo == "S":
			hr_laborales = 0
			hr_extra_laborales = 0
			while flag:
				actividad = raw_input("actividad:")
				if actividad == "Legislar" or actividad == "Comision":
					#<<<<<<<< AQUI FALTA
				hora_termino = raw_input("hora termino:")
				if hora_termino <= "08:00":
					print "Hora invalida"
				elif hora_termino > "18:00":
					print "Hora invalida"
				if hora_termino == "18:00":
					flag = False
				else:
	else:
		print "Senador mas inoperante:", S_inoperante, "Diputado mas inoperante:", D_inoperante
		band = False