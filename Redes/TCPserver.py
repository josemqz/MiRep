# coding=utf-8
import socket

#49152 - 65535 (disponibles)
puertoServ = 60600

#Socket para handshake
socketServ = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #AF_INET -> IPv4 | SOCK_STREAM -> TCP
socketServ.bind(('',puertoServ))

#indica que espere handshakes
socketServ.listen(1) #1-> cantidad de elementos en cola para atender

print("Servidor TCP escuchando en puerto: ", puertoServ)

while True:
	
	#socket de cliente
	socketCliente, direccionCliente = socketServ.accept() #acepta conexíón de socket (handshake)
	mensaje = socketCliente.recv(2048).decode()
	print("Se recibió: ", mensaje)
	resp = "Respuesta: " + mensaje.upper()

	socketCliente.send(resp.encode())

	socketCliente.close()