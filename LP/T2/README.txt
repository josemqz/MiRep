

Nombres:
          José Quezada Silva            Rol:  201773528-7
          Martin Salinas Scussolin      Rol:  201773557-0

Instrucciones de compilación:
                              En la carpeta donde se encuentren los archivos de la tarea, se debe
                              abrir la terminal y compilar usando el comando "make",
                              luego se debe ejecutar el programa usando "./out".

Supuestos:
            1)  Se debe tener un archivo llamado "fun.c" en la carpeta donde se quiera ejecutar la tarea,
                este archivo debe contener la función fun, la cual recibe un nodo de una lista.

            2)  Los nodos de la lista tienen un puntero al siguiente nodo, de la forma:

            //Estructura de nodo
            typedef struct node{
                void* data;
                char type;
                struct node* next;
            }listNode;

            3)  El tipo de lista implementado, debe tener la siguiente estructura, puesto que se necesita de
                los elementos que posee:

            //Estructura de lista enlazada
            typedef struct {
                listNode* head;
                listNode* tail;
                listNode* curr;
                int listSize;
                int pos;
            }linkList;

	    4)  Se debe tener instalado el paquete time.h para la correcta obtención de elementos aleatorios, al usar la función srand().
