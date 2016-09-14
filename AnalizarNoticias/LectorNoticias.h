/*
 * LectorNoticias.h
 *
 *  Created on: 29 de ago. de 2016
 *      Author: ECERAMM
 */

#ifndef LECTORNOTICIAS_H_
#define LECTORNOTICIAS_H_

#include "Noticia.h"
#include "PalabrasReservadas.h"
#include <string>
#include <list>
#include <memory>

static constexpr const char *tuitId = "id";
static constexpr const char *tuitUsuario = "usuario";
static constexpr const char *tuitContenido = "tuit";
static constexpr const char *articuloTitulo = "titulo";
static constexpr const char *articuloContenido = "parrafos";

class LectorNoticias {
private:
  std::string ruta;
  std::shared_ptr<PalabrasReservadas> palabrasReservadas;

  const static std::string pathNoticiasTxt;
  const static std::string pathNoticiasJson;

public:
  LectorNoticias(std::string ruta);
  virtual ~LectorNoticias();

  std::list <Noticia*> leerNoticias();
  std::list <Noticia*> leerTuits();
  std::list <Noticia*> leerNoticiasTxt();
  std::list <Noticia*> leerNoticiasJson();

private:
  void leerNoticiasDeFichero(std::string &fileName, std::list <Noticia*>& noticias);
  void leerTuitsDeFichero(std::string &fileName, std::list <Noticia*>& noticias);
  void leerNoticiasDeFicheroJson(std::string &fileName, std::list <Noticia*>& noticias);

};

#endif /* LECTORNOTICIAS_H_ */
