package com.segfault.recuperaciones.repository;

import com.segfault.recuperaciones.model.BedList;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;
import java.util.List;

public interface BedListRepository extends JpaRepository<BedList, Long> {

	public abstract List<BedList> findByCondition(boolean condition);

	public abstract Optional<BedList> findByPaciente(long paciente);
}