//clientes
package main

import (
	
	"fmt"
	"os"
	//"time"
	"log"
	
	"encoding/csv"

	//"bufio"
	"io"
)

/*func leerCSV(arch string){
	???
}*/

func main() {
    
    //declarar variable
	//var [nombre] [tipo]

	//time:
	//time.sleep([segundos] time.Second)

	//leer csv
	//hay que leer ambos al mismo tiempo? que sean intercalados? what
	//bueno, por mientras:
	pyme_csv, err_csv := os.Open("pymes.csv")

    if err_csv != nil {
    	log.Fatalln("No se pudo abrir el archivo csv", err_csv)
        return
    }

    //io.Reader
    rPyme := csv.NewReader(pyme_csv)

	for {
		
		// Lee cada entrada (pedido) del csv
		pedidoP, err_read := rPyme.Read()
		
		if err_read == io.EOF {
			break
		}
		
		if err_read != nil {
			log.Fatal(err_read)
			return
		}
		
		fmt.Printf("%s, %s\n", pedidoP[0], pedidoP[1])
	}


	//cada cierto tiempo (definido por input (creo)) tiene que leer 
	//una entrada y enviar el pedido a logística

	//realizar conexion gRPC como client y enviar datos
	//hay que crear tres colas (se crean en client y server porsiaca)

	//tiene que ser capaz de pedir seguimiento de pedido, mediante el id de compra
	//una vez hecho esto tiene que recibir el mensaje de seguimiento e imprimir

}