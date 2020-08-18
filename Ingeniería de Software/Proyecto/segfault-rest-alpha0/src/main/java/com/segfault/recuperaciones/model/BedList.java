package com.segfault.recuperaciones.model;

import javax.persistence.*;

import io.swagger.annotations.ApiModelProperty;

@Entity
public class BedList {

    @Id
    @Column(name = "id", unique = true, nullable = false)
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @ApiModelProperty(notes = "ID autogenerado por cama")
    private long id;

    @Column(name = "condition", nullable = false)
    @ApiModelProperty(notes = "Condición de la cama")
    private boolean condition;

    @Column
    @ApiModelProperty(notes = "ID del paciente en la cama, en caso de estar vacía es un -1")
    private long paciente;

    BedList() {

    }

    public BedList(long paciente, boolean condition){
        this.paciente = paciente;
        this.condition = condition;
    }

    public BedList(long id, long paciente, boolean condition){
        this.id = id;
        this.paciente = paciente;
        this.condition = condition;
    }

    public long getId(){
        return id;
    }

    public void setId(long id){
        this.id = id;
    }

    public boolean getCondition(){
        return condition;
    }

    public void setCondition(boolean condition){
        this.condition = condition;
    }

    public long getPaciente(){
        return paciente;
    }

    public void setPaciente(long paciente){
        this.paciente = paciente;
    }

    @Override
    public String toString() {
        return "BedList{" + "id=" + id + ", condition=" + condition + ", paciente=" + paciente + "}";
    }
}