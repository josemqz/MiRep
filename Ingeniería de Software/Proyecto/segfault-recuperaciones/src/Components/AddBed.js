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

export default function AddBed() {
  const classes = useStyles();
  const [firstLoad, setLoad] = React.useState(true);

  const [message, setMessage] = React.useState("Ningún cambio realizado en esta sesión");

  function Notification(){
    return NotificationManager.success('Cama añadida');
  }

  async function CreateEntry() {
    const response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/vacia", {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      redirect: "follow",
      body: JSON.stringify({})
    });
    Notification();
  }

  if (firstLoad) {
    setLoad(false);
  }

  return (
    <Container component="main" maxWidth="xs">
      <CssBaseline/>
      <div className={classes.paper}>
        <Typography component="h1" variant="h5">Sector Recuperaciones</Typography>
        <p></p><p></p>
        <Grid container spacing={2} justify="center">
          <Grid item xs justify="center">
            <Button
            type="submit" variant="contained" color="primary" preventDefault classname={classes.submit} onClick={CreateEntry}
              > Añadir una cama vacía
            </Button>
          </Grid>
          
          <Grid item xs={6} justify="center">
            <Link to='/form'>
            <Button 
            type="submit" variant="contained" color="primary" preventDefault classname={classes.submit}
                > Añadir una cama con un paciente
            </Button>
            </Link>
          </Grid>  
          <Grid item xs spacing={1} justify="center">
            <Link to='/view'>
                <Button variant="contained" color="primary">Ver camas en existencia</Button>
            </Link>
          </Grid>

          <Grid item xs={6} justify="center">
            <Link to='/recPac'>
            <Button 
            type="submit" variant="contained" color="primary" preventDefault classname={classes.submit}> 
              Ver pacientes en recuperación
            </Button>
            </Link>
          </Grid>  
          <Grid item xs spacing={1} justify="center">
            <Link to='/condition'>
              <Button variant="contained" color="primary">Obtener cama por condición</Button>
            </Link>
          </Grid>

          <Grid item xs spacing={1} justify="center">
            <Link to='/update'>
              <Button 
              variant="contained" color="primary" preventDefault classname={classes.submit}> 
                Actualizar datos de una cama
              </Button>
            </Link>
          </Grid>
        </Grid>
      </div>
    </Container>
  );
}