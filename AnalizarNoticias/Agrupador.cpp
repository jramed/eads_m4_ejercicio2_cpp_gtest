/*
 * Aggregator.cpp
 *
 *  Created on: 5 de sept. de 2016
 *      Author: ECERAMM
 */

#include "Agrupador.h"
#include "Articulo.h"
#include "Tuit.h"
#include <algorithm>


Agrupador::Agrupador()
{
}

bool Agrupador::esAgrupable(Noticia *noticia1, Noticia *noticia2){
  noticia1->accept(this);
  noticia2->accept(this);
  bool result = false;

  if (articulos.size() == 2){
    result = esAgrupableArticuloArticulo(articulos[0], articulos[1]);
  } else if (tuits.size() == 2) {
    result = esAgrupableTuitTuit(tuits[0], tuits[1]);
  } else {
    result = esAgrupableArticuloTuit(articulos[0],tuits[0]);
  }

  articulos.clear();
  tuits.clear();
  return result;
}

void Agrupador::visit( Articulo *articulo) {
  articulos.push_back(articulo);
}

void Agrupador::visit( Tuit *tuit)  {
  tuits.push_back(tuit);
 }


bool Agrupador::esAgrupableArticuloTuit(Articulo *articulo,Tuit *tuit){
  auto entidades = tuit->getEntidades();
  auto entidadMasNombrada = articulo->getMasFrecuente();

  auto pos = std::find(entidades.begin(), entidades.end(), entidadMasNombrada);
  if (pos == entidades.end()) {
    return false;
  }
  return true;
}

bool Agrupador::esAgrupableArticuloArticulo(Articulo *articulo1, Articulo *articulo2) {
  if (!esAgrupablePorEntidadEnTitulo(articulo1, articulo2))
    return false;

  if (!esAgrupablePorEntidadesRelevantes(articulo1, articulo2))
    return false;

  return true;
}

bool Agrupador::esAgrupablePorEntidadEnTitulo(const Articulo *articulo1, const Articulo *articulo2) const {
  if (articulo1->getTitulo().find(articulo2->getMasFrecuente().getEntidadNombrada())
      == std::string::npos) {
    return false;
  }
  return true;
}

bool Agrupador::esAgrupablePorEntidadesRelevantes(const Articulo *articulo1, const Articulo *articulo2) const{
  std::list<EntidadNombrada> entidadesRelevantesComprobar = articulo2->getEntidadesRelevantes();
  std::vector<EntidadNombrada> interseccion;


  std::list<EntidadNombrada> entidades = articulo1->getEntidades();
  std::set_intersection(entidadesRelevantesComprobar.begin(), entidadesRelevantesComprobar.end(),
      entidades.begin(), entidades.end(),
      std::back_inserter(interseccion),
      compararEntidadesNombradas);

  if (interseccion.empty() ||
      interseccion.size() < (entidadesRelevantesComprobar.size() / porcionCuerpoParaEntidadesRelevantes)) {
    return false;
  }

  return true;
}

bool Agrupador::esAgrupableTuitTuit(Tuit *tuit1, Tuit *tuit2){
  auto entidades = tuit1->getEntidades();
  auto entidades2 = tuit2->getEntidades();

  auto pos = std::find_first_of(entidades.begin(), entidades.end(),
      entidades2.begin(), entidades2.end());
  if (pos == entidades.end()) {
    return false;
  }
  return true;
}
