import React from 'react';
import Button from '@material-ui/core/Button';
import Menu from '@material-ui/core/Menu';
import IconButton from '@material-ui/core/IconButton';
import ArrowBackIosIcon from '@material-ui/icons/ArrowBackIos';
import MenuItem from '@material-ui/core/MenuItem';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
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

export default function MenuContextos() {
    const classes = useStyles();

    return (  
        <>  
        <AppBar position="static">  
            <Toolbar>

                <IconButton edge="start" aria-controls="MenuContextos" aria-haspopup="true" 
                onClick={() => { window.location.replace("https://isw-hm.herokuapp.com")}}
                className={classes.menuButton} color="inherit" aria-label="menu">
                
                  <ArrowBackIosIcon /> 

                  <Typography variant="subtitle2">
                    Sitio principal
                  </Typography>
                
                </IconButton>
                
                <Button href="/" color="inherit" variant="contained" className={classes.title} align="center">
                  Sector Recuperaciones
                </Button>

            </Toolbar>
        </AppBar>
        </>  
    );
}