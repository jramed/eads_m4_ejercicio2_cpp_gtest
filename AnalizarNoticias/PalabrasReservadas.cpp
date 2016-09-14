/*
 * PalabrasReservadas.cpp
 *
 *  Created on: 4 de ago. de 2016
 *      Author: ECERAMM
 */

#include <Utilidades.h>
#include "PalabrasReservadas.h"
#include <fstream>
#include <algorithm>

std::string PalabrasReservadas::idioma ="ES";
std::string PalabrasReservadas::nombreFicheroRestricciones = "/ES_stopList.txt";

PalabrasReservadas::PalabrasReservadas(std::string &ruta) {
  setPalabrasReservadas(ruta);
}

std::list<std::string> PalabrasReservadas::getPalabrasReservadas(std::string &idioma)const {
  std::map<std::string, std::list<std::string>>::const_iterator it = palabrasReservadas.find(idioma);
  if (  it != palabrasReservadas.end())
    return it->second;
  else{
    std::list<std::string> palabrasReservadasAux;
    return palabrasReservadasAux;
  }
}

void PalabrasReservadas::setPalabrasReservadas(std::string &ruta) {
  std::ifstream f;
  f.open(ruta.c_str(), std::ofstream::in);
  if (!f.good())
  {
    return;
  }
  std::string palabra;
  std::list<std::string> palabrasReservadasAux;
  while (!f.eof()) {
    f >> palabra;
    palabrasReservadasAux.push_back(palabra);
  }
  palabrasReservadasAux.sort();
  palabrasReservadas[idioma] = palabrasReservadasAux;
}

bool PalabrasReservadas::contienePalabra(std::string &palabra, std::string &idioma) const{
  if (palabrasReservadas.empty())
    return false;

  std::setlocale(LC_ALL, utilidades::localeSpanish);
  std::string entidadMinusculas;
  std::transform(begin(palabra),end(palabra),std::back_inserter(entidadMinusculas),tolower);
  bool contenida = false;
  for (auto word:getPalabrasReservadas(idioma)) {
    if (word.compare(entidadMinusculas) > 0) {
      break;
    }
    else if (word.compare(entidadMinusculas) == 0) {
      contenida = true;
      break;
    }
  }
  return contenida;
}

