import React from "react";
import Avatar from "@material-ui/core/Avatar";
import Button from "@material-ui/core/Button";
import CssBaseline from "@material-ui/core/CssBaseline";
import TextField from "@material-ui/core/TextField";
import { Link } from "react-router-dom";
import Grid from "@material-ui/core/Grid";
import GroupIcon from "@material-ui/icons/Group";
import Typography from "@material-ui/core/Typography";
import { makeStyles } from "@material-ui/core/styles";
import Container from "@material-ui/core/Container";
import { NotificationManager } from 'react-notifications';
import 'react-notifications/lib/notifications.css';

const useStyles = makeStyles(theme => ({
  paper: {
    marginTop: theme.spacing(7),
    display: "flex",
    flexDirection: "column",
    alignItems: "center"
  },
  avatar: {
    margin: theme.spacing(1),
    backgroundColor: theme.palette.secondary.main
  },
  form: {
    width: "100%", // Fix IE 11 issue.
    marginTop: theme.spacing(3)
  },
  submit: {
    margin: theme.spacing(3, 0, 2)
  },
  textField: {
    marginLeft: theme.spacing(1),
    marginRight: theme.spacing(1),
    width: "100%"
  }
}));

export default function RemoveBed() {
  const classes = useStyles();
  const [firstLoad, setLoad] = React.useState(true);
  const [paciente, setPaciente] = React.useState("");
  const [condition, setCondition] = React.useState("");
  const [id, setId] = React.useState("");

  
  const handleIdChange = event => setId(event.target.value);
  const handleConditionChange = event => setCondition(event.target.value);
  const handlePacienteChange = event => setPaciente(event.target.value);

  const [message, setMessage] = React.useState("Ningún cambio realizado en esta sesión");

    function Notification(idCama, correcto) {
        if (correcto) {
            return NotificationManager.success('Cama ' + idCama + ' Eliminada');
        } else {
            return NotificationManager.warning('La cama especificada no existe');
        }
  }

    async function removeButton() {
        // Revisar que la cama no tenga una persona xd
        const idCama = prompt('Ingrese ID de cama a eliminar');
        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/?id=" + idCama, {
            method: "DELETE",
            headers: {
                "Content-Type": "application/json"
            },
            redirect: "follow",
            body: JSON.stringify({})
        });

        if (response.ok) {
            Notification(idCama, true);
        } else {
            Notification(idCama, false);
        }
     }


  if (firstLoad) {
    // sampleFunc();
    setLoad(false);
  }

  return (
    <Container component="main" maxWidth="xs">
      <CssBaseline/>
      <div className={classes.paper}>
          <Grid item xs={6} justify="center">

            <Button
              type="submit" variant="contained" color="primary" preventDefault classname={classes.submit} onClick={removeButton}
            > Eliminar una cama
            </Button>
        
          </Grid>
      </div>
    </Container>
  );
}