# coding=utf-8

import socket
import Link
import sys
from os import path


#Caché como lista enlazada
cache = Link.Link()
cacheNom = "./local.cache"

#De archivo de caché a lista
if path.exists(cacheNom):
	cacheArch = open(cacheNom,"r")
	cache.getCacheTexto(cacheArch)	
	cacheArch.close()

#Descomentar para limpiar caché
#cache.clearCache()

#49152 - 65535 (disponibles)
X = 60600
Z = "50500"

#Socket para handshake
TCPsocketServ = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
TCPsocketServ.bind(('',X))

#Indica que espere handshakes
TCPsocketServ.listen(1)

print("Servidor TCP escuchando en puerto: ", X)

#Por cada cliente
while True:

	#Socket de cliente
	TCPsocketCliente, TCPdireccionCliente = TCPsocketServ.accept() #acepta conexíón de socket (handshake)

	#Por cada url
	while True:
		
		#recibe URL
		rcvURL = TCPsocketCliente.recv(2048).decode()

		#Si se encuentra en caché, la función retorna el header
		URLenCache = cache.getHeader(rcvURL)

		#print("getheader: \n", cache.getHeader(rcvURL))
		
		#Terminar conexión cliente
		if rcvURL == "terminate":
			TCPsocketCliente.close()
			print("\n --- Cliente termino conexión ---\n")
			break

		elif URLenCache == None:
			
			#consulta GET con URL
			request = b"GET / HTTP/1.1\r\n\r\n"
			
			try:
				s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
				s.settimeout(15)
				s.connect((rcvURL, 80))
			
			#Error de URL
			except(socket.gaierror):
				
				sys.tracebacklimit = 0
				errorURL = "\nError de conexión con URL entregada.\n"
		
				print(errorURL)
				TCPsocketCliente.send(errorURL.encode())
		
				continue


			s.send(request)
			
			result = None
			result = s.recv(4096)
			result = result.decode()

			s.close()

			#Error en resultado
			if len(result) <= 0:
				print("\nError en resultado.\n")
				continue

			#Posicion final de header
			doctypeIndex = result.find("\r\n\r\n")
			Resultado = str(result[0:doctypeIndex])

		else:

			#Resultado de caché
			Resultado = URLenCache
		

		#Guardar en caché (mover de posición en caso de ya existir)
		cache.insertar(rcvURL, Resultado)
		#print("TAIL:\n", cache.tail.url)


		#Descomentar para ver caché en cada consulta
		#cache.verCache()


		#Enviar puerto de transferencia UDP
		TCPsocketCliente.send(Z.encode())
		print(" - Puerto UDP enviado -\n")

		#UDP
		UDPsocketServ = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

		UDPsocketServ.bind(('', int(Z))) #str vacío porque es ip interna
		
		#Respuesta cliente
		Status, UDPdireccionCliente = UDPsocketServ.recvfrom(2048)

		if Status.decode() == "OK":	
			#Enviar header
			UDPsocketServ.sendto(Resultado.encode(), UDPdireccionCliente)
		else:
			print("Error de estado. Estado altamente improbable. Revise código.")

		#Cerrar conexión UDP
		print(" - Conexión UDP cerrada -")
		UDPsocketServ.close()

	#Escribir en archivo caché
	cacheArc = open("local.cache","w")
	cache.aTexto(cacheArc)
	cacheArc.close()
