/*
 * Noticia.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */


#include "Noticia.h"
#include "EntidadNombrada.h"
#include "Agrupador.h"
#include "Utilidades.h"
#include <list>
#include <cassert>
#include <algorithm>
#include <sstream>

Noticia::Noticia():
cuerpo{""},
entidadesNombradas{}, entidadesRelevantes{},
entidadMasFrecuente{}{
  std::string empty{""};
  palabrasReservadas = std::make_shared<PalabrasReservadas>(empty);
}

Noticia::Noticia(std::string cuerpo,
    std::shared_ptr<PalabrasReservadas> palabrasReservadas):
    cuerpo{cuerpo}, palabrasReservadas{palabrasReservadas} {
    setEntidades();
    setMasFrecuente();
    setEntidadesRelevantes();
  }

  Noticia::~Noticia() {}

  std::string Noticia::getCuerpo() const {
    return cuerpo;
  }

  EntidadNombrada Noticia::getMasFrecuente() const {
    return entidadMasFrecuente;
  }

  std::list<EntidadNombrada> Noticia::getEntidades() const {
    return entidadesNombradas;
  }

  std::list<EntidadNombrada> Noticia::getEntidadesRelevantes() const {
    return entidadesRelevantes;
  }


  void Noticia::setEntidadesRelevantes() {
    entidadesRelevantes.clear();

    std::string primerTercioCuerpoNoticia;
    primerTercioCuerpoNoticia = cuerpo.substr(0, (cuerpo.size() / porcionCuerpoParaEntidadesRelevantes));
    for (auto &entidadNombrada: entidadesNombradas){
      if (primerTercioCuerpoNoticia.find(entidadNombrada.getEntidadNombrada()) != std::string::npos) {
        entidadesRelevantes.push_back(entidadNombrada);
      }
    }

    entidadesRelevantes.sort();
  }

  void Noticia::insertarEntidadNombradaOrIncrementarFrecuenciaEntidadNombrada(
      const std::string& nombre) {
    bool add = true;
    for (auto &entidadNombrada : entidadesNombradas) {
      if (entidadNombrada.getEntidadNombrada().compare(nombre) == 0) {
        entidadNombrada.setFrecuencia(entidadNombrada.getFrecuencia() + 1);
        add = false;
        break;
      }
    }

    if (add){
      EntidadNombrada aux(nombre, 1);
      entidadesNombradas.push_back(aux);
    }
  }

  void Noticia::siEntidadNoReservadaAlmacenar(std::string nombre) {

    if (palabrasReservadas == nullptr)
      assert(false);

    if (!palabrasReservadas->contienePalabra(nombre, PalabrasReservadas::idioma)) {
      insertarEntidadNombradaOrIncrementarFrecuenciaEntidadNombrada(nombre);
    }
  }

  void Noticia::siEntidadNombradaAlmacenar(const std::vector<std::string>& words) {
    for (auto &entidad : words) {
      if (!entidad.empty() && utilidades::esMayuscula(entidad.at(0))) {
        siEntidadNoReservadaAlmacenar(entidad);
      }
    }
  }

  void Noticia::setEntidades() {
    entidadesNombradas.clear();

    cuerpo = utilidades::removePuctuationFromText(cuerpo);
    std::vector<std::string> words = utilidades::splitTextInWords(cuerpo);
    siEntidadNombradaAlmacenar(words);

    entidadesNombradas.sort();
  }

  void Noticia::setMasFrecuente() {
    std::list<EntidadNombrada> entidadesNombradasCopia = entidadesNombradas;
    entidadesNombradasCopia.sort(compararPorMasFrecuenteMayorMenor);

    if (!entidadesNombradasCopia.empty()){
      entidadMasFrecuente = entidadesNombradasCopia.front();
    }
  }

