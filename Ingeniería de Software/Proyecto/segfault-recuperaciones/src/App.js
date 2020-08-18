// Librerías
import React, { Component } from "react";
import axios from 'axios';
import { BrowserRouter as Router } from 'react-router-dom';
import { Route } from "react-router-dom";
import {NotificationContainer} from 'react-notifications';

import MenuContextos from "./Components/MenuContextos"
import AddBed from "./Components/AddBed";
import FormBedPatient from "./Components/FormBedPatient"
import Table from "./Components/Table";
import GetCama from "./Components/GetCama";
import UpdateBed from "./Components/UpdateBed"
import RemoveBed from "./Components/RemoveBed";
import TablaPacientes from "./Components/TablaPacientes";
import Condition from "./Components/Condition";



export default class App extends Component {

  render() {

    return (
      
      <div className="App">
        <MenuContextos/>
     
        <Router>
        
            <Route exact path="/" component={AddBed} />
            <Route exact path="/form" component={FormBedPatient} />
            <Route exact path="/view" component={Table} />
            <Route exact path="/condition" component={Condition} />

            <Route exact path="/" component={GetCama} />
            <Route exact path="/update" component={UpdateBed} />
            <Route exact path="/" component={RemoveBed} />
            <Route exact path="/recPac" component={TablaPacientes} />
          
          <NotificationContainer/>
        </Router>
      </div>
    );
  }
}