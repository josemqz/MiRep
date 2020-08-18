package com.segfault.recuperaciones.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.Optional;
import java.util.List;
import java.util.Arrays;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiResponse;
import io.swagger.annotations.ApiResponses;

import com.segfault.recuperaciones.model.BedList;
import com.segfault.recuperaciones.repository.BedListRepository;

@RestController
@RequestMapping("/bed")
@Api(value="Sala de recuperaciones")
public class BedListController {

    @Autowired
    BedListRepository bedRepository;


    @ApiOperation(value = "Lista de las camas en existencia", response = List.class)

    @GetMapping(value = "/list")
    public ResponseEntity index() {
        return ResponseEntity.ok(bedRepository.findAll());
    }


    @ApiOperation(value = "Buscar cama mediante un id", response = BedList.class)
    @ApiResponses(value = {
        @ApiResponse(code = 200, message="Encontrado con éxito"),
        @ApiResponse(code = 404, message="El recurso no se ha podido encontrar")
    })

    @GetMapping(value = "/show", params = "id")
    public ResponseEntity getBed(@RequestParam(value = "id") Long id) {
        Optional<BedList> foundBedList = bedRepository.findById(id);
        if(foundBedList.isPresent()){
            return ResponseEntity.ok(foundBedList.get());
        } else {
            return ResponseEntity.badRequest().body("No existe una cama con el id: " + id);
        }
    }


    @ApiOperation(value = "Buscar camas según su condicion", response = List.class)
    @ApiResponses(value = {
        @ApiResponse(code = 200, message = "Recursos encontrados con éxito"),
        @ApiResponse(code = 404, message = "No existen camas en esa condición")
    })

    @GetMapping(value = "/cond", params = "condition")
    public ResponseEntity getBed(@RequestParam(value="condition") boolean condition){

        List<BedList> foundBedListArr = bedRepository.findByCondition(condition);

    	if(!foundBedListArr.isEmpty()){
            return ResponseEntity.ok(foundBedListArr);
    	}
    	else {
            String conditionStatus = ((condition == true) ? "ocupadas" : "vacías");
    	    return ResponseEntity.badRequest().body("No existen camas " + conditionStatus);
    	}
    }


    @ApiOperation(value = "Buscar cama asociada a paciente", response = BedList.class)
    @ApiResponses(value = {
        @ApiResponse(code = 200, message = "Recurso encontrado con éxito"),
        @ApiResponse(code = 404, message = "No existen camas asociadas a paciente")
    })

    @GetMapping(value = "/paciente", params = "paciente")
    public ResponseEntity getBed(@RequestParam(value="paciente") long paciente){
        //if BD Pacientes contains paciente
        Optional<BedList> foundBedList = bedRepository.findByPaciente(paciente);
        if(foundBedList.isPresent()){
            return ResponseEntity.ok(foundBedList.get());
        } else {
            return ResponseEntity.badRequest().body("No existe una cama con el paciente: " + paciente);
        }
    }
    

    @ApiOperation(value = "Añadir una cama con una condición y paciente", response = BedList.class)
    @PostMapping(value = "/add")
    public ResponseEntity addToBedList(@RequestParam(value = "condition") boolean condition, @RequestParam(value = "paciente") Long paciente) {
        return ResponseEntity.ok(bedRepository.save(new BedList(paciente, condition)));
    }

    /*
    @ApiOperation(value = "Añadir una cama con la condición de esta", response = BedList.class)

    @PostMapping(value = "/add")
    public ResponseEntity addToBedList(@RequestParam(value = "condition") String condition) {
        return ResponseEntity.ok(bedRepository.save(new BedList(-1, condition)));
    }
    */

    @ApiOperation(value = "Añadir una cama vacía", response = BedList.class)
    @PostMapping(value = "/vacia")
    public ResponseEntity addToBedList() {
        return ResponseEntity.ok(bedRepository.save(new BedList(-1, false)));
    }


    @ApiOperation(value = "Actualizar los valores de una cama", response = BedList.class)
    @ApiResponses(value = {
        @ApiResponse(code = 200, message="Encontrado con éxito"),
        @ApiResponse(code = 404, message="El recurso no existe")
    })
    @PutMapping(value = "/")
    public ResponseEntity updateBedList(@RequestParam(value = "id") Long id, @RequestParam(value = "paciente") Long paciente){
        
        Optional<BedList> optionalBedList = bedRepository.findById(id);
        if (!optionalBedList.isPresent()) {
            return ResponseEntity.badRequest().body("No existe una cama con el id: " + id);
        }
        
        BedList foundBedList = optionalBedList.get();
        
        //condiciones correctas de actualización
        if(paciente == -1){
            foundBedList.setCondition(false);
            foundBedList.setPaciente(paciente);
        }
        else if(paciente > 0){
            foundBedList.setCondition(true);
            foundBedList.setPaciente(paciente);
        }
        else{
            return ResponseEntity.badRequest().body("No es posible realizar esa actualización de cama.");
        }
        
        return ResponseEntity.ok(bedRepository.save(foundBedList));
    }


    @ApiOperation(value = "Eliminar una cama", response = BedList.class)
    @DeleteMapping(value = "/")
    public ResponseEntity removeBedList(@RequestParam(value = "id") Long id) {
        bedRepository.deleteById(id);
        return ResponseEntity.noContent().build();
    }
}
