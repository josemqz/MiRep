# coding=utf-8
import socket

#49152-65535 (disponibles)

serverPort = 50500

socketServ = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) #AF_INET -> ipv4 | DGRAM -> UDP

socketServ.bind(('', serverPort)) #str vacío porque es ip interna

print("serv escuchando en puerto:", serverPort)

while True:
	
	mensaje, direccionCliente = socketServ.recvfrom(2048) #tamaño buffer en bytes
	#mensaje codificado
	decodMsg = mensaje.decode()
	print("se recibe: ",decodMsg)

	resp = "Respuesta: " + decodMsg.upper()
	socketServ.sendto(resp.encode(),direccionCliente)