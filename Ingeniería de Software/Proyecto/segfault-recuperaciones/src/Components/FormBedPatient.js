import React from 'react';
import TextField from '@material-ui/core/TextField';
import { NotificationManager } from 'react-notifications';
import { Link } from "react-router-dom";
import Grid from "@material-ui/core/Grid";
import Typography from "@material-ui/core/Typography";
import { makeStyles } from '@material-ui/core/styles';

const useStyles = makeStyles((theme) => ({
  root: {
    '& .MuiTextField-root': {
      margin: theme.spacing(3),
      width: '25ch',
    },
  },
}));


export default function FormBedPatient() {
  const classes = useStyles();
  const [paciente, setPaciente] = React.useState("");
  const [condition, setCondition] = React.useState("");
  const [help, setHelp] = React.useState("");

  const handleConditionChange = event => setCondition(event.target.value);
  const handlePacienteChange = event => setPaciente(event.target.value);
  const handleHelpChange = event => setHelp(event.target.value);


  function Notification(resultado) {
      if (resultado == "success") {
          NotificationManager.success("Cama añadida con éxito");
      }
      else if (resultado == "noPaciente") {
          NotificationManager.warning("Paciente no registrado");
      }
      else if (resultado == "pacienteInvalido") {
          NotificationManager.warning("ID de paciente inválido");
      }
      else if (resultado == "noBed") {
          NotificationManager.warning("Cama no registrada");
      }
      else if (resultado == "error") {
          NotificationManager.warning("No se pudo ingresar la cama");
      }
      else if (resultado == "noRecuperacion") {
          NotificationManager.warning("El paciente no está en recuperación.");
      }
  }

    async function PacienteEnRecuperacion(idPaciente) {
        if (idPaciente == -1) return true;

        const response = await fetch("https://ms-paciente.herokuapp.com/paciente/obtenerEstado/4");
        if (response.ok) {
            return response.json().then(function (data) {
                if (data.res.includes(idPaciente)) return 1;
                else return 0;
            });
        } else return false; // Error de GET
    }

  //POST cama con paciente
  async function addBedPatient(paciente, condition) {
      const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/add?condition="+condition+"&paciente="+paciente, {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          redirect: "follow", // manual, *follow, error
      });

      if(response.ok)
          Notification("success");
      else Notification("error");
  }

  //check BD pacientes 
    async function BDpacientes(paciente) {
        const response = await fetch("https://ms-paciente.herokuapp.com/paciente/obtenerId/" + paciente);

        if (response.ok == false) return false;

        else {
            return response.text().then(function (data) {
                if (!data.toString().includes("null")) return true;
                else return false;
            });
        }
    }


    async function CamaClick(paciente) {

        if (paciente == -1) addBedPatient(paciente, false);

        else {
            var existe = async () => BDpacientes(paciente);
            existe().then(function (data) {
                if (data) { // Paciente existe en la base de datos

                    var enRecuperacion = async () => PacienteEnRecuperacion(paciente);
                    enRecuperacion().then(function (data) {
                        if (data == 1) addBedPatient(paciente, true); // Paciente está en recuperacion
                        else if (data == 0) addBedPatient(paciente, false);

                        else Notification("noRecuperacion"); // Paciente no está en recuperacion
                    });

                } else Notification("noPaciente");

                //else Notification("pacienteInvalido");
            });
        }
    }
  

  return (
    <form className={classes.root} noValidate autoComplete="off">
      
      <div>
        <Typography variant="h6"> Añadir cama con paciente </Typography>
      <div>

      </div>

          <TextField
            required
            value = {paciente}
            onChange={handlePacienteChange}
            label="ID Paciente"
            type="number"
          />

          <Link to='/'>
            <button 
            type="submit" 
            onClick={() => { CamaClick(paciente) }}>
              Ingresar cama
            </button>
          </Link>

      </div>
    </form>
  );
}