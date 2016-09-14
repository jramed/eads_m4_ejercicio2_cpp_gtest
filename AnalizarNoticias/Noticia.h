/*
 * Noticia.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef NOTICIA_H_
#define NOTICIA_H_

#include "EntidadNombrada.h"
#include "PalabrasReservadas.h"
#include <string>
#include <vector>
#include <list>
#include <memory>

class NoticiaVisitor;

class Noticia {

  std::string cuerpo;
  std::list<EntidadNombrada> entidadesNombradas;
  std::list<EntidadNombrada> entidadesRelevantes;
  EntidadNombrada entidadMasFrecuente;
  std::shared_ptr<PalabrasReservadas> palabrasReservadas;

public:
  Noticia();
  Noticia(std::string cuerpo, std::shared_ptr<PalabrasReservadas> palabrasReservadas);
  virtual ~Noticia();

  std::string getCuerpo() const;
  EntidadNombrada getMasFrecuente()const;
  std::list<EntidadNombrada> getEntidades()const;
  std::list<EntidadNombrada> getEntidadesRelevantes()const;
  virtual std::string getSummary() const = 0;
  virtual std::string toString()const = 0;
  virtual void accept(NoticiaVisitor* visitor) = 0;

private:
  void setEntidades();
  void setMasFrecuente();
  void setEntidadesRelevantes();
  void siEntidadNombradaAlmacenar(const std::vector<std::string>& words);
  void insertarEntidadNombradaOrIncrementarFrecuenciaEntidadNombrada(const std::string& nombre);
  void siEntidadNoReservadaAlmacenar(std::string nombre);
};

#endif /* NOTICIA_H_ */
