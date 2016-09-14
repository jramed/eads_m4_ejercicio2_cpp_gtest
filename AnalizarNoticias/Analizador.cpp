/*
 * Analizador.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "Analizador.h"
#include "Noticia.h"
#include "Agrupador.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <sstream>

Analizador::Analizador()
:noticias{} {
  agrupador = new Agrupador();
}

Analizador::~Analizador(){
  delete agrupador;
}

std::list<Noticia*> Analizador::getNoticias() const {
  return noticias;
}

void Analizador::setNoticas(std::list <Noticia*> noticias)
{
  this->noticias = noticias;
  this->noticias.sort();
}

Analizador::agrupacionEntidadFrecuente Analizador::agruparNoticias() {

  return getGruposPorEntidadNombradaMasFrecuente();
}

Analizador::agrupacionEntidadFrecuente Analizador::getGruposPorEntidadNombradaMasFrecuente() {
  agrupacionEntidadFrecuente agrupacionPorEntidad;
  for (auto &noticia: noticias) {
    if (noticia->getMasFrecuente().getEntidadNombrada() != "") {
      agrupacionPorEntidad[noticia->getMasFrecuente().getEntidadNombrada()].insert(noticia);
    }
  }

  return agrupacionPorEntidad;
}

Analizador::agrupacionTematica Analizador::agruparNoticiasGeneral() {

  agrupacionTematica gruposPorSimilitudTematica = getGruposPorSimilitudTematica();
  incluirNoticiasConMismaEntidadNombradaFrecuente(gruposPorSimilitudTematica);
  eliminarGruposSimilitudTematicaRedundantes(gruposPorSimilitudTematica);
  incluirNoticiasNoAgrupadas(gruposPorSimilitudTematica);

  return gruposPorSimilitudTematica;
}

Analizador::agrupacionTematica Analizador::getGruposPorSimilitudTematica() {

  agrupacionTematica gruposPorSimilitudTematica;
  for (std::list<Noticia*>::iterator it1 = noticias.begin();
      it1 != noticias.end(); ++it1) {

    grupoNoticias grp;
    for (std::list<Noticia*>::iterator it2 = noticias.begin();
        it2 != noticias.end(); ++it2) {

      if (it1 == it2)
        continue;

      if (agrupador->esAgrupable(*it2,*it1)){
        grp.insert(*it2);
      }
    }
    if (!grp.empty()) {
      grp.insert(*it1);
      gruposPorSimilitudTematica.push_back(grp);
    }
  }
  return gruposPorSimilitudTematica;
}

void Analizador::eliminarGruposSimilitudTematicaRedundantes(
    agrupacionTematica& gruposPorSimilitudTematica) {

  for (agrupacionTematica::iterator it1 = gruposPorSimilitudTematica.begin();
      it1 != gruposPorSimilitudTematica.end();
      ++it1) {

    agrupacionTematica::iterator it2 = gruposPorSimilitudTematica.begin();
    while (it2 != gruposPorSimilitudTematica.end()) {
      if (it1 == it2 or it1->size() < it2->size()) {
        ++it2;
        continue;
      }

      std::vector<Noticia*> intersection;
      std::set_intersection(it1->begin(), it1->end(),
          it2->begin(), it2->end(),
          std::back_inserter(intersection));

      if (it2->size() == intersection.size()) {
          it2 = gruposPorSimilitudTematica.erase(it2);
      }
      else {
        ++it2;
      }
    }
  }
}

void Analizador::incluirNoticiasConMismaEntidadNombradaFrecuente(
    agrupacionTematica &gruposPorSimilitudTematica) {

  agrupacionEntidadFrecuente gruposPorEntidadMasFrecuente = getGruposPorEntidadNombradaMasFrecuente();

  for (auto &grupoST : gruposPorSimilitudTematica) {
    for (auto noticia : grupoST) {
      agrupacionEntidadFrecuente::iterator gruposNoticiaselacionadas =
          gruposPorEntidadMasFrecuente.find(noticia->getMasFrecuente().getEntidadNombrada());
      if ( gruposNoticiaselacionadas != gruposPorEntidadMasFrecuente.end()) {
        grupoST.insert(gruposNoticiaselacionadas->second.begin(), gruposNoticiaselacionadas->second.end());
      }
    }
  }
}

void Analizador::incluirNoticiasNoAgrupadas(agrupacionTematica &gruposPorSimilitudTematica) {

  grupoNoticias yaAgrupadas;
  for (auto &grp : gruposPorSimilitudTematica) {
    for (auto noticia : grp) {
      yaAgrupadas.insert(noticia);
    }
  }

  for (auto &noticia : noticias) {
    if (yaAgrupadas.find(noticia) == yaAgrupadas.end()) {
      grupoNoticias grp;
      grp.insert(noticia);
      gruposPorSimilitudTematica.push_back(grp);
    }
  }
}

std::string Analizador::toString() const {
  std::string salida;
  for (auto &noticia: noticias) {
    salida += "Titulo: " + noticia->getSummary() + "\n";
  }
  return salida;
}
