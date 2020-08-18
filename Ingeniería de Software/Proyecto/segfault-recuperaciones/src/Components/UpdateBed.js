import React from 'react';
import TextField from '@material-ui/core/TextField';
import { NotificationManager } from 'react-notifications';
import { Link } from "react-router-dom";
import Typography from "@material-ui/core/Typography";
import { makeStyles } from '@material-ui/core/styles';

import { datosCama, datosPaciente } from "./GetCama.js";


const useStyles = makeStyles((theme) => ({
  root: {
    '& .MuiTextField-root': {
      margin: theme.spacing(1),
      width: '25ch',
    },
  },
}));


export default function UpdateBed() {
    const classes = useStyles();
    const [paciente, setPaciente] = React.useState("");
    const [condition, setCondition] = React.useState("");
    const [id, setId] = React.useState("");

    const handleConditionChange = event => setCondition(event.target.value);
    const handlePacienteChange = event => setPaciente(event.target.value);
    const handleIdChange = event => setId(event.target.value);


    function Notification(resultado, paciente, id) {

        // Se asigna o desocupa una cama.
        if (resultado == 1) {
            if (paciente != -1) NotificationManager.success("Paciente " + paciente + " asignado a cama " + id + ".");
            else NotificationManager.success("Cama " + id + " ha sido desocupada.");
        }

        // Se quiere asignar un paciente a una cama no registrada
        else if (resultado == 0) NotificationManager.warning("La cama " + id + " no existe.");

        // Se mueve al paciente desde una cama a otra. Se considera "id" como 2-array [previo, nuevo].
        else if (resultado == 2) NotificationManager.success("El paciente se ha movido de la cama " + id[0] + " a la cama " + id[1] + ".");

        // La cama ya está ocupada.
        else if (resultado == 3) NotificationManager.warning("La cama " + id + " ya está ocupada.");

        // El paciente ya está en la cama
        else if (resultado == 4) NotificationManager.warning("El paciente " + paciente + " ya está en la cama " + id + ".");

        else if (resultado == 5) NotificationManager.warning("No hay paciente con la id " + paciente + ".");

        // Quitar a un paciente de la tabla de recuperaciones
        else if (resultado == 6) NotificationManager.success("El paciente " + paciente + " abandonó Recuperaciones.");
        else if (resultado == 7) NotificationManager.warning("No se ha podido mover al paciente " + paciente + ".");

        // El paciente no está en recuperaciones.
        else if (resultado == 8) NotificationManager.warning("El paciente " + paciente + " no se encuentra en Recuperaciones.");

    }


    async function PacienteEnRecuperacion(idPaciente) {
        if (idPaciente == -1) return true;

        const response = await fetch("https://ms-paciente.herokuapp.com/paciente/obtenerEstado/4");
        if (response.ok) {
            return response.json().then(function (data) {
                console.log("id" + idPaciente);
                console.log(data.res.includes(idPaciente));
                return (data.res.includes(idPaciente)); // El paciente está en recuperaciones
                //else return false; // El paciente no está en recuperaciones
            });
        } else return false; // Error de GET
    }


    // Se asigna un paciente a la cama

    async function asignarPaciente(idCama, idPaciente) {
        var response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/?id=" + idCama + "&paciente=" + idPaciente, {
            method: "PUT",
            headers: {
                "Content-Type": "application/json",
            },
            redirect: "follow", // manual, *follow, error
        });
    }


    // Se desocupa una cama
    // Reemplazo indica si al paciente se le está moviendo a otra cama, o se vá de Recuperaciones.

    async function desocuparCama(idCama, idPaciente) {
        await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/?id=" + idCama + "&paciente=-1", {
            method: "PUT",
            headers: {
                "Content-Type": "application/json",
            },
            redirect: "follow", // manual, *follow, error
        });

        if (idPaciente != -1) {
            const darAlta = await fetch("https://ms-paciente.herokuapp.com/paciente/actualizarEstado/" + idPaciente + "?estado=0", {
                method: "PUT",
                headers: {
                    "Content-Type": "application/json",
                },
                redirect: "follow", // manual, *follow, error
            });

            if (darAlta.ok) Notification(6, idPaciente, idCama);
            else Notification(7, idPaciente, idCama);
        }
    }


    // Se revisa que el paciente existe en la base de datos de los pacientes

    async function BDpacientes(idPaciente, idCama) {
        if (idPaciente == -1) return false;

        const response = await fetch("https://ms-paciente.herokuapp.com/paciente/obtenerId/" + idPaciente);

        if (response.ok == false) { // Paciente no existe
            Notification(5, idPaciente, idCama);
            return true;
        }
        else {
            return response.text().then(function (data) {
                if (data.toString().includes("null")) {
                    Notification(5, idPaciente, idCama);
                    return true;
                }else  return false;
            });
        }
    }



    // Se revisa si la cama existe
    async function revisarCama(idCama) {
        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/show?id=" + idCama);
        return response.ok;
    }


    // Acciones que requieren asignar camas

    async function AdministrarCamas(idPaciente, idCama) {
        if (idPaciente == -1) { // Se busca vaciar una cama
            desocuparCama(idCama, -1);
            return true;
        }

        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/paciente?paciente=" + idPaciente)
        if (response.ok) { // El paciente ya tiene una cama
            return response.text().then(function (data) {
                var datos = datosPaciente(data);  // Se retorna la id de la cama del paciente

                if (datos == idCama) { // Se quiere mover al paciente a la misma cama en la que ya está
                    Notification(4, idPaciente, idCama);
                    return true;

                } else { // Se mueve al paciente a otra cama
                    desocuparCama(datos, -1);
                    asignarPaciente(idCama, idPaciente);
                    Notification(2, idPaciente, [datos, idCama]);
                    return true;
                }                               
            });

        } else {
            asignarPaciente(idCama, idPaciente);
            Notification(1, idPaciente, idCama);
            return true;
        }
    }



    // Retorna si la cama está ocupada
    async function camaOcupada(idCama, idPaciente) {

        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/show?id=" + idCama);

        if (response.ok) {
            return response.text().then(function (data) {
                var datos = datosCama(data); // retorna [(true|false) (, id if true)]
                if (datos[0] == true) {
                    if (idPaciente != -1)  Notification(3, 0, idCama);
                    return [true, datos[1]]; // Retora true y el ID del paciente que usa la cama.
                }
                else {
                    return false;
                }
            });
        } else  return false;
    }



    async function CamaClick(idCama, idPaciente) {

        var estadoCama = async () => revisarCama(idCama);
        return estadoCama().then(function (data) {
            if (data == false) {
                Notification(0, idPaciente, idCama); // La cama no es valida
            }

            else {
                var existePaciente = async () => BDpacientes(idPaciente, idCama);
                return existePaciente().then(function (data) {
                    if (data == true) return;  // El paciente no existe
                    else {

                        var EnRecuperacion = async () => PacienteEnRecuperacion(idPaciente);
                        return EnRecuperacion().then(function (data) {

                            if (data == false) { // Se revisa que el paciente esté en recuperaciones
                                Notification(8, idPaciente, idCama);
                                return;
                            } else {

                                var ocupada = async () => camaOcupada(idCama, idPaciente);  // Se revisa si la cama que se está viendo está ocupada;
                                return ocupada().then(function (data) {
                                    if (data != false) { // La cama está en uso
                                        desocuparCama(idCama, data[1]); // Data[1] contiene al paciente que utiliza la cama ocupada.
                                        return;
                                    }
                                    else {
                                        if (idPaciente != -1) {
                                            var administrar = async () => AdministrarCamas(idPaciente, idCama); // Acciones a tomar con las camas
                                            return administrar().then(function (data) {
                                                if (data == true) return;
                                            });
                                        }
                                    }
                                });
                            }
                        });
                    }
                });
            }
        });
    }

  return (
    <form className={classes.root} noValidate autoComplete="off">
      
      <div>
        <h2> Actualizar datos de cama </h2>
      <div>

      </div>

        <TextField
          required
          value = {id}
          onChange={handleIdChange}
          id="idField"
          label="ID Cama"
          type="number"
        />

        <TextField
          required
          value={paciente}
          onChange={handlePacienteChange}
          id="pacienteField"
          label="ID Paciente"
          type="number"
          helperText="-1 si se encuentra disponible"
        />

        <Link to='/'>
            <button 
                type="submit" 
                onClick={() => { CamaClick(id, paciente) }}>
                Actualizar cama 
            </button>
        </Link>
      </div>
    </form>
  );
}