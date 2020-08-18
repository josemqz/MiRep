# encoding=utf-8
class Nodo:

	def __init__(self, url, header = ""):
		
		self.url = url
		self.header = header
		self.next = None

class Link:
	
	def __init__(self):
		
		self.largo = 0
		self.head = None
		self.tail = None
		self.act = None

	
	#mMeve nodo actual al anterior
	def prev(self, nodo):

		if nodo != self.head:
			self.act = self.head
			
			while self.act.next != nodo:
				self.act = self.act.next
		else:
			print("Can't go back, you're head ònó")

	
	#Retorna el nodo del URL buscado
	def buscar(self, urlB):

		if self.largo > 0:

			self.act = self.head
			
			while self.act != None:

				if self.act.url == urlB:
					return self.act

				self.act = self.act.next

		#else:
			#print("No hay elementos para buscar en caché")
		
		return None


	#Inserta un elemento en caché, recibe URL y header correspondiente
	def insertar(self, url, header):
	
		nodo = Nodo(url,header)

		if self.largo == 0:

			self.tail = nodo
			self.act = nodo
			self.head = nodo
			self.largo += 1

		#no se encuentra
		elif self.buscar(url) == None:

			#print("No se encontró", url, ". Insertando en cabecera.")

			#llena
			if self.largo == 5:
								
				#kill tail
				self.prev(self.tail)
				self.tail = self.act
				self.tail.next = None

				#nueva cabeza
				nodo.next = self.head
				self.head = nodo
				
			#no llena ^ ^
			elif self.largo < 5:

				nodo.next = self.head
				self.head = nodo
				self.largo += 1
		
		#se encuentra
		else:
			
			self.act = self.buscar(url)
			#print("\nElemento se encuentra en caché.")
			
		#self.act.url == nodo.url
			if self.act != self.head:
				auxNodo = self.act

				self.prev(self.act)
				self.act.next = self.act.next.next
				
				#nueva cola
				if auxNodo == self.tail:
					self.tail = self.act

				#nueva cabeza
				auxNodo.next = self.head
				self.head = auxNodo

		#print("\nElemento ", nodo.url, " insertado.\n")
		#print("Cantidad de URLs en caché: ", self.largo, "\n")


	#Imprime todos los elementos en caché
	def verCache(self):
		
		print("·---------------·")
		print("| URLs en caché |")
		print("·---------------·")
		print("·---------------·")

		self.act = self.head
		
		while self.act != None:

			print(self.act.url)
			print(self.act.header)
			self.act = self.act.next
		
			print("·-------------·")
			
		print("·-------------·\n")
		

	#Retorna header de url en caso de estar en caché
	def getHeader(self,url):
		
		if self.buscar(url) != None:
			return self.act.header
		
		else:
			return None


	#Recibe un archivo abierto y genera lista enlazada a partir de archivo de texto de caché
	def getCacheTexto(self, arch):
		
		if self.largo == 0:
			
			indexURL = index = 0
			lineas = arch.readlines()
			cHeader = ""
			
			
			for l in lineas:
				
				if l == "<<< EOC >>>\n":
					
					self.insertar(lineas[indexURL].strip(),cHeader)
					#print("texto a linked:\n", lineas[indexURL], "\n", cHeader)

					indexURL = index + 1
					cHeader = ""
					
				if index > indexURL:
					cHeader += l
				
				index += 1
		
		else:
			#No debería ocurrir
			print("\nLista enlazada de caché ya se encuentra con elementos.\n")


	#Recibe un archivo abierto y escribe elementos de lista enlazada a archivo de texto
	def aTexto(self, arch):
		
		self.act = self.head
		
		while self.act != None:
			
			if not arch.closed: #check
			
				arch.write(self.act.url)
				arch.write("\n")
				arch.write(self.act.header)
				arch.write("\n<<< EOC >>>\n")

				self.act = self.act.next


	# PROBANDO
	#Limpia caché
	def clearCache(self):
		
		self.act = self.tail
		
		while self.act != self.head:
		
			self.prev(self.act)
			self.act.next = None	#verificar si está bien hacer eso

		self.head = self.act = None
		self.largo = 0

		print("Caché borrado.")



#TESTING

'''
cache = Link()

cache.insertar("www.ble.cl","urlT: blabla\ntypeA:True")
cache.insertar("www.hhh.cl","urlT: hhhhhh\ntypeA:True")
cache.insertar("www.ññ.cl","urlT: ñ\ntypeA:True")
cache.insertar("www.F.cl","urlT: SF\ntypeA:False")
cache.insertar("www.ji.cl","urlT: jjj\ntypeA:True")

cache.insertar("www.muycierto.cl","urlT: muymuy\ntypeA:False")
'''
'''
cache.insertar("www.muycierto.cl","urlT: muymuy\ntypeA:False")
cache.insertar("www.muycierto.cl","urlT: muymuy\ntypeA:False")
cache.insertar("www.muycierto.cl","urlT: muymuy\ntypeA:False")


cache.verCache()

cache.getHeader("www.ji.cl")
cache.getHeader("www.muycierto.cl")
'''
