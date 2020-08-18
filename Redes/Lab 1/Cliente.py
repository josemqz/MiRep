# encoding=utf-8
import socket

Y = 'localhost'
X = 60600

#Socket TCP
TCPsocketCliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#Realiza handshake
TCPsocketCliente.connect((Y,X))

#Enviar URL
URL = input("Ingrese URL: ")
TCPsocketCliente.send(URL.encode())

while URL != "terminate":
	
	#Recibe puerto UDP
	Z = TCPsocketCliente.recv(2048).decode()
	if not Z[0] in list(map(str,range(10))):
		
		print(Z)
		
		URL = input("Ingrese URL: ")
		TCPsocketCliente.send(URL.encode())
		
		continue

	#UDP
	UDPsocketClient = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	UDPsocketClient.sendto("OK".encode(), (Y, int(Z)))
	
	#Recibe header
	header, _ = UDPsocketClient.recvfrom(2048)
	print(" - Cabecera de página web recibida -")
	
	#print("HEADER CLIENTE:\n", header.decode())

	#Cerrar conexion
	UDPsocketClient.close()


	#Escribir header en archivo
	URLfile = open(URL + ".txt", "w")
	URLfile.write(header.decode())
	URLfile.close()

	#Enviar URL nuevamente
	URL = input("Ingrese URL: ")
	TCPsocketCliente.send(URL.encode())


print(" - Conexión TCP cerrada. -")
TCPsocketCliente.close()
