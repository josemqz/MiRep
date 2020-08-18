import React from "react";
import { makeStyles } from "@material-ui/core/styles";
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
import { NotificationManager } from 'react-notifications';
import 'react-notifications/lib/notifications.css';

const useStyles = makeStyles(theme => ({
  table: {
    minWidth: 600
  },
  avatar: {
    margin: theme.spacing(1),
    backgroundColor: theme.palette.secondary.main
  },
  paper: {
    display: "flex",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
    margin: `10px`,
    height: "100%",
    width: "99%",
    marginTop: theme.spacing(7)
  },
  link: {
    color: "rgba(0,0,0,0.65)",
    textDecoration: "none",
    marginLeft: "10%",
    alignSelf: "flex-start",
    "&:hover": {
      color: "rgba(0,0,0,1)"
    }
  }
}));

function Notification(status) {
    if (status == 0) return NotificationManager.warning('La condición no es válida.');
}

export default function Condition() {
    const classes = useStyles();

    const [data, upDateData] = React.useState([]);
    const [firstLoad, setLoad] = React.useState(true);
    let isLoading = true;
    
    async function getBeds() {

        const input = prompt('Ingrese condición (0 = Desocupadas, 1 = Ocupadas)');
        var condition = "";

        if (input + "" == "0") {
            condition = "false";
        } else if (input + "" == 1) {
            condition = "true";
        } else {
            Notification(0);
        }

        let response = await fetch("https://segfault-rest-alpha0.herokuapp.com/bed/cond?condition="+condition);
        let body = await response.json();
        upDateData(body);
    }

    if (firstLoad) {
        getBeds();
        setLoad(false);
    }

  if (data.length > 0) isLoading = false;

  return (
    <div className={classes.paper}>
      <Avatar className={classes.avatar}>
        <GroupIcon />
      </Avatar>
      <Typography component="h1" variant="h5">
        Directorio de Camas
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
                <TableCell align="center">Id cama</TableCell>
                <TableCell align="center">Condición</TableCell>
                <TableCell align="center">Id paciente</TableCell>
              </TableRow>
            </TableHead>
            <TableBody>
              {data?.map(row => (
                <TableRow key={row.name}>
                  <TableCell align="center">{row.id}</TableCell>
                      <TableCell align="center">{row.condition ? "Ocupada" : "Desocupada"}</TableCell>
                      <TableCell align="center">{row.paciente == -1 ? "" : row.paciente}</TableCell>
                </TableRow>
              ))}
            </TableBody>
          </Table>
        </TableContainer>
      )}
      <Link className={classes.link} to="/">
        {" "}
        <Typography align="left">
          &#x2190; Volver a modificar datos
        </Typography>{" "}
      </Link>
    </div>
  );
}