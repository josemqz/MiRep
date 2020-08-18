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

        // Se quita a un paciente de una cama.
        if (resultado == 1) {
            if (paciente != -1) NotificationManager.success("Paciente " + paciente + " asignado a cama " + id + ".");
            else NotificationManager.success("Cama " + id + " ha sido desocupada.");
        }

        // Se quiere asignar un paciente a una cama no registrada
        else if (resultado == 0) NotificationManager.warning("La cama " + id + " no existe.");

        // Se mueve al paciente desde una cama a otra. Se considera "id" como 2-array [previo, nuevo].
        else if (resultado == 2) NotificationManager.success("El paciente se ha movido de la cama " + id[0] + " a la cama " + id[1] + ".");

        // Se Reemplaza al paciente de la cama por un paciente distinto.  En este caso se recibe "paciente" como 2-array [previo, nuevo].
        else if (resultado == 3) NotificationManager.success("Cama " + id + "\nSe ha quitado al paciente " + paciente[0] + " y se ha asignado al paciente " + paciente[1] + ".");

    }

    // Se asigna un paciente a la cama
    async function asignarPaciente(idCama, idPaciente) {
        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/?id=" + idCama + "&paciente=" + idPaciente, {
            method: "PUT",
            headers: {
                "Content-Type": "application/json",
            },
            redirect: "follow", // manual, *follow, error
        });

        if (response.ok) {
            // Se logró colocar al paciente en cama vacía
        }

    }

    // Se desocupa una cama
    async function desocuparCama(idCama) {
        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/?id=" + idCama + "&paciente=-1", {
            method: "PUT",
            headers: {
                "Content-Type": "application/json",
            },
            redirect: "follow", // manual, *follow, error
        });

        if (response.ok) {
            // Se eliminó al paciente de la cama
        }
    }

    // Se revisa que el paciente existe en la base de datos de los pacientes
    async function BDpacientes(paciente) {
        const response = await fetch("https://ms-paciente.herokuapp.com/paciente/obtenerId/" + paciente);
        if (!response.ok) return false;
        else {
            response.text().then(function (data) {
                if (data == "null") return false;
                else return true;
            });
        }
    }

    // Se revisa si la cama existe
    async function revisarCama(idCama) {
        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/show?id=" + idCama);
        return response.ok
    }

    // Retorna false si el paciente no está en cama. En caso que lo esté, retorna la id de la cama
    async function pacienteEnCama(idPaciente) {
        if (idPaciente == -1) { // Se busca vaciar una cama
            return false;
        } // Eliminar esta verificacion luego. No deberia ser necesaria.


        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/paciente?paciente=" + idPaciente)
        if (response.ok) { // Se logró encontrar una cama
            response.text().then(function (data) {
                return datosPaciente(data);  // Se retorna la id de la cama del paciente
            });
        } else return false;
    }

    // Retorna si la cama está ocupada
    async function camaOcupada(idCama){
        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/show?id=" + idCama);

        if (response.ok) {
            response.text().then(function (data) {
                return datosCama(data)[0]; // retorna true o false
            });
        }

    }

/* 
  async function getByID(idCama) {

      const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/show?id=" + idCama);
      return response.ok
  }


  //check BD pacientes 
  async function BDpacientes(paciente) {
      const response = await fetch("https://ms-paciente.herokuapp.com/paciente/obtenerId/" + paciente);
      if (!response.ok) return false;
      else {
          response.text().then(function (data) {
              if (data == "null") return false;
              else return true;
          });
      }
  }


  async function CamaClick(idCama, idPaciente){
    
      if (getByID(idCama)) {
          if (idPaciente >= -1) {
              if (BDpacientes(idPaciente)) {

                  // Verificar que el paciente no está en otra cama:

                  const used = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/paciente?paciente=" + idPaciente);

                  if (used.ok && idPaciente != "-1") { // Se encuentra una cama con el paciente que se quiere asignar.
                      used.text().then(function (data) {
                          var cama = datosPaciente(data)[0];
                          Notification(2, 0, cama);
                      });
                      return;
                  }


                  // Verificar si la cama ya está en uso:

                  const used = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/show?id=" + idCama);

                  if (response.ok) { // La cama está en uso
                      response.text().then(function (data) {

                          var parsed = datosCama(data); // parsed = [idcama, condition (, paciente  if condition == true)]
                          var mensaje = "ID Cama: " + idCama + "\nEstado: ";

                          if (parsed[0]) {
                              mensaje += "Ocupada\nID Paciente: " + parsed[1] + ".";
                          } else if (!parsed[0]) {
                              mensaje += "Desocupada.";
                          }

                          window.alert(mensaje);
                      });



                  const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/?id=" + idCama + "&paciente=" + idPaciente, {
                      method: "PUT",
                      headers: {
                          "Content-Type": "application/json",
                      },
                      redirect: "follow", // manual, *follow, error
                  });

                  if (response.ok) {
                      Notification(1, idPaciente, idCama);
                  }
                  else { // Paciente si existe pero no la cama
                      Notification(0, idPaciente, idCama);
                  }
              }

              else window.alert("Paciente no registrado");
          }
          else window.alert("ID de paciente inválido");
      }else  window.alert("Cama no registrada");
  }
  
  */
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
          value={idPaciente}
          onChange={handlePacienteChange}
          id="pacienteField"
          label="ID Paciente"
          type="number"
          helperText="-1 si se encuentra disponible"
        />

        <Link to='/'>
            <button 
                type="submit" 
                onClick={() => { CamaClick(id, idPaciente) }}>
                Actualizar cama 
            </button>
        </Link>

        <Link className={classes.link} to="/">
          {" "}
          <Typography align="left">
            &#x2190; Menú principal
          </Typography>{" "}
        </Link>

      </div>
    </form>
  );
}