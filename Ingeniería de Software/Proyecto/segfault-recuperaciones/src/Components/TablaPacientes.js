import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Table from "@material-ui/core/Table";
import TableBody from "@material-ui/core/TableBody";
import TableCell from "@material-ui/core/TableCell";
import TableContainer from "@material-ui/core/TableContainer";
import TableHead from "@material-ui/core/TableHead";
import TableRow from "@material-ui/core/TableRow";
import Paper from "@material-ui/core/Paper";
import Avatar from "@material-ui/core/Avatar";
import GroupIcon from "@material-ui/icons/Group";
import { Link } from "react-router-dom";
import Typography from "@material-ui/core/Typography";
import CircularProgress from "@material-ui/core/CircularProgress";


const useStyles = makeStyles((theme) => ({
  root: {
    '& .MuiTextField-root': {
      margin: theme.spacing(3),
      width: '25ch',
    },
  },
}));


export default function TablaPacientes() {
  const classes = useStyles();
  const [data, setData] = React.useState([]);         //recibirá lista de pacientes
  const [firstLoad, setLoad] = React.useState(true);  //primera carga de página
  let isLoading = true;  //para icono de carga

//obtener lista de pacientes en recuperación
  async function GetPaciente(paciente, condition) {
    const response = await fetch("https://ms-paciente.herokuapp.com/paciente/obtenerEstado/4");
    response.json().then(function(data){
      //actualizar data con lista de pacientes
      setData(data.res);
    });
  }

//primera carga de página
  if (firstLoad) {
    GetPaciente();
    setLoad(false);
  }

//si hay pacientes
  if (data.length > 0){
    isLoading = false;
  }

  return(
    <div className={classes.paper} align="center">
      <Avatar className={classes.avatar}>
        <GroupIcon />
      </Avatar>
      <Typography component="h1" variant="h5">
        Pacientes en recuperación
      </Typography>
      {isLoading ? (
        <CircularProgress />
      ) : (
        <TableContainer
          style={{ width: "80%", margin: "0 10px" }}
          component={Paper}
        >
          <Table className={classes.table} aria-label="simple table">
            <TableHead>
              <TableRow>
                <TableCell align="center">ID</TableCell>
              </TableRow>
            </TableHead>

            <TableBody>
              {data?.map(pac => (
                <TableRow>
                  <TableCell align="center">{pac}</TableCell>
                </TableRow>
              ))}

            </TableBody>
          </Table>
        </TableContainer>
      )}

      <Link className={classes.link} to="/">
        {" "}
        <Typography align="left">
          &#x2190; Menú principal
        </Typography>{" "}
      </Link>

    </div>
  );
}