/*
 * Aggregator.h
 *
 *  Created on: 5 de sept. de 2016
 *      Author: ECERAMM
 */
#ifndef AGRUPADOR_H_
#define AGRUPADOR_H_

#include "NoticiaVisitor.h"
#include <vector>


class Noticia;

static unsigned int const porcionCuerpoParaEntidadesRelevantes = 3;

class Agrupador : public NoticiaVisitor {


private:
  std::vector< Articulo*> articulos;
  std::vector< Tuit*> tuits;

public:
  Agrupador();

  bool esAgrupable(Noticia *noticia1, Noticia *noticia2);

  void visit( Articulo *articulo) override;
  void visit( Tuit *tuit) override;

private:
  bool esAgrupableArticuloTuit(Articulo *articulo1,Tuit *tuit);
  bool esAgrupableArticuloArticulo(Articulo *articulo1, Articulo *articulo2);
  bool esAgrupablePorEntidadEnTitulo(const Articulo *articulo1, const Articulo *articulo2) const;
  bool esAgrupablePorEntidadesRelevantes(const Articulo *articulo1, const Articulo *articulo2) const;
  bool esAgrupableTuitTuit(Tuit *tuit1, Tuit *tuit2);
};


#endif /* AGRUPADOR_H_ */
