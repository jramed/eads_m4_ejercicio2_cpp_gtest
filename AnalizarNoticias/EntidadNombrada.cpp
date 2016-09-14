/*
 * EntidadNombrada.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "EntidadNombrada.h"
#include <sstream>

EntidadNombrada::EntidadNombrada() :
  frecuencia(0), entidadNombrada("") {
}

EntidadNombrada::EntidadNombrada(std::string n, int f) :
  frecuencia(f), entidadNombrada(n) {
}

int EntidadNombrada::getFrecuencia() const {
  return frecuencia;
}

std::string EntidadNombrada::getEntidadNombrada() const {
  return entidadNombrada;
}

void EntidadNombrada::setFrecuencia(int const f) {
  frecuencia = f;
}

void EntidadNombrada::setEntidadNombrada(std::string const& en) {
  entidadNombrada = en;
}

std::string EntidadNombrada::toString() const {
  std::stringstream s;
  s << entidadNombrada << " [" << frecuencia << "]";
  return s.str();
}

bool compararEntidadesNombradas(const EntidadNombrada &lhs, const EntidadNombrada &rhs)
{
  return lhs < rhs;
}

bool compararPorMasFrecuenteMayorMenor(const EntidadNombrada &lhs, const EntidadNombrada &rhs ) {
  return lhs.getFrecuencia() > rhs.getFrecuencia();
}

