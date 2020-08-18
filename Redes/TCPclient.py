# encoding=utf-8
import socket

direccionServ = 'localhost'
puertoServ = 60600

socketCliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #AF_INET -> IPv4 | SOCK_STREAM -> TCP

socketCliente.connect((direccionServ,puertoServ)) #Realiza handshake

msgEnv = input("Ingrese texto: ")
socketCliente.send(msgEnv.encode())

resp = socketCliente.recv(2048).decode()
print(resp)

socketCliente.close()