# coding=utf-8
import socket

direccionServidor = 'localhost' #o 127.0.0.1 | si servidor es en otra máquina, hay que poner ese ip
puertoServidor = 50500 #debe ser el mismo que en server

socketClient = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

msgEnv = input("Ingresar mensaje a convertir: ")
socketClient.sendto(msgEnv.encode(), (direccionServidor, puertoServidor))

#no es while, porque es solo un mensaje

mensaje, _ = socketClient.recvfrom(2048)
print(mensaje.decode())

socketClient.close()