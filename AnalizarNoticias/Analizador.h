/*
 * Analizador.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef ANALIZADOR_H_
#define ANALIZADOR_H_
#include "Noticia.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <memory>

class Agrupador;
class Analizador {

public:
  typedef std::set<Noticia*>                                    grupoNoticias;
  typedef std::map<std::string, grupoNoticias >                 agrupacionEntidadFrecuente;
  typedef std::list<grupoNoticias>                              agrupacionTematica;

private:
  std::list<Noticia*> noticias;
  Agrupador*agrupador;

public:
  Analizador();
  ~Analizador();

  std::list<Noticia*> getNoticias() const;
  void setNoticas(std::list <Noticia*> noticias);

  agrupacionEntidadFrecuente agruparNoticias();
  agrupacionTematica agruparNoticiasGeneral();

  std::string toString()const;

private:
  agrupacionEntidadFrecuente getGruposPorEntidadNombradaMasFrecuente();
  agrupacionTematica getGruposPorSimilitudTematica();
  void incluirNoticiasConMismaEntidadNombradaFrecuente(
      agrupacionTematica &gruposPorSimilitudTematica);
  void incluirNoticiasNoAgrupadas(
      agrupacionTematica &gruposPorSimilitudTematica);
  void eliminarGruposSimilitudTematicaRedundantes(
      agrupacionTematica& gruposPorSimilitudTematica);
};

#endif /* ANALIZADOR_H_ */
