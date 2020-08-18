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

export function datosCama(data) {
    
    var respuesta = (data.replace("{", "").replace("}", "").replace('"', "")).split(",");
    var condition = respuesta[1].split(":");
    var paciente = respuesta[2].split(":");
    // condicion / paciente

    if (condition[1] == "true") {
        return [true, paciente[1]];
    } else if (condition[1] == "false") {
        return [false];
    }
}

export function datosPaciente(data){
    var respuesta = (data.replace("{", "").replace("}", "").replace('"', "")).split(",");
    var id = respuesta[0].split(":"); // id de la cama

    return id[1];  // idcama
}


export default function GetCama() {
    const classes = useStyles();
    const [firstLoad, setLoad] = React.useState(true);
    const [paciente, setPaciente] = React.useState("");
    const [condition, setCondition] = React.useState("");
    const [id, setId] = React.useState("");

  
    const handleIdChange = event => setId(event.target.value);
    const handleConditionChange = event => setCondition(event.target.value);
    const handlePacienteChange = event => setPaciente(event.target.value);

    const [message, setMessage] = React.useState("Ningún cambio realizado en esta sesión");

    function Notification(resultado, parametro) {
        if (resultado == "idC_F") {
            NotificationManager.warning("No existe cama con id: " + parametro); // placeholder id cama no encontrada
        }
        else if (resultado == "idP_F") {
            NotificationManager.warning("No existe cama con paciente: " + parametro); // placeholder id cama no encontrada
        }

    }

    async function getByID() {

        const idCama = prompt('Ingrese ID de cama');
        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/show?id=" + idCama);

        if (response.ok) {
            response.text().then(function (data) {

                var parsed = datosCama(data); // parsed = [idcama, condition (, paciente  if condition == true)]
                var mensaje = "ID Cama: " + idCama + "\nEstado: ";

                if (parsed[0]) {
                    mensaje += "Ocupada\nID Paciente: " + parsed[1] + ".";
                } else if (!parsed[0]){
                    mensaje += "Desocupada.";
                }

                window.alert(mensaje);
            });
        } else {
            Notification("idC_F", idCama);
        }
    }

    async function getByPaciente() {

        const idPaciente = prompt('Ingrese ID de paciente');
        const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/paciente?paciente=" + idPaciente);

        if (response.ok && idPaciente != "-1") {
            response.text().then(function (data) {

                var parsed = datosPaciente(data);
                window.alert("ID Cama: " + parsed + "\nEstado: Ocupada\nPaciente: " + idPaciente + ".");
            });

        } else {
            Notification("idP_F", idPaciente);
        }
    }


    if (firstLoad) {
        setLoad(false);
    }

    return (
        <Container component="main" maxWidth="xs">
            <CssBaseline/>
            <div className={classes.paper}>
                <Grid container spacing={2} justify="center">
                    <Grid item xs spacing={1} justify="center">
                        <Button
                        type="submit" variant="contained" color="primary" fullWidth="true" preventDefault classname={classes.submit} onClick={getByID}> 
                            Obtener cama por ID
                        </Button>
                    </Grid>
                    <Grid item xs spacing={1} justify="center">
                        <Button
                        type="submit" variant="contained" color="primary" fullWidth="true" preventDefault classname={classes.submit} onClick={getByPaciente}> 
                            Obtener cama por paciente
                        </Button>
                    </Grid>
                </Grid>
            </div>
        </Container>
    );
}