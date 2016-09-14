/*
 * LectorNoticias.cpp
 *
 *  Created on: 29 de ago. de 2016
 *      Author: ECERAMM
 */

#include "LectorNoticias.h"
#include "Articulo.h"
#include "Tuit.h"
#include "Utilidades.h"
#include <fstream>
#include "../Json/json.h"

const std::string LectorNoticias::pathNoticiasTxt = "/news/";
const std::string LectorNoticias::pathNoticiasJson = "/news_json/";

LectorNoticias::LectorNoticias(std::string ruta)
: ruta(ruta), palabrasReservadas(nullptr)
{
  std::string rutaRestricciones = ruta + PalabrasReservadas::nombreFicheroRestricciones;;
  palabrasReservadas = std::make_shared<PalabrasReservadas>(rutaRestricciones);
}

LectorNoticias::~LectorNoticias() {
}

std::list <Noticia*>  LectorNoticias::leerNoticias(){

  auto noticiasTxt = leerNoticiasTxt();
  auto noticiasJson = leerNoticiasJson();
  auto tuits = leerTuits();

  std::list <Noticia*> noticias{};
  noticias.merge(noticiasTxt);
  noticias.merge(noticiasJson);
  noticias.merge(tuits);
  return noticias;
}

std::list <Noticia*> LectorNoticias::leerNoticiasTxt(){
  std::list <Noticia*> noticias{};

  std::string rutaNoticias = ruta + LectorNoticias::pathNoticiasTxt;
  std::vector<std::string> ficheros = utilidades::obtenerNombreFicherosDesdeDirectorio(rutaNoticias);
  for (auto &fichero: ficheros) {
    leerNoticiasDeFichero(fichero,noticias);
  }

  noticias.sort();
  return noticias;
}

std::list <Noticia*> LectorNoticias::leerNoticiasJson(){
  std::list <Noticia*> noticias{};

  std::string rutaNoticias = ruta + LectorNoticias::pathNoticiasJson;
  std::vector<std::string> ficheros = utilidades::obtenerNombreFicherosDesdeDirectorio(rutaNoticias);
  for (auto &fichero: ficheros) {
    leerNoticiasDeFicheroJson(fichero,noticias);
  }

  noticias.sort();
  return noticias;
}

std::list <Noticia*> LectorNoticias::leerTuits(){
  std::list <Noticia*> noticias{};

  std::string fichero = ruta + "/tuits.json";
  leerTuitsDeFichero(fichero,noticias);
  noticias.sort();

  noticias.sort();
  return noticias;
}

void LectorNoticias::leerNoticiasDeFichero(std::string &fileName, std::list <Noticia*>& noticias){
  std::ifstream f;
  f.open(fileName.c_str(), std::ofstream::in);
  if (f.is_open()) {
    std::string linea = "";
    std::string titulo = "";
    std::stringstream cuerpo;
    while (!f.eof()) {
      getline(f, linea, '\n');
      if (titulo.empty()) {
        while (linea.at(linea.size()-1) == '\r') {
          linea.resize(linea.size()-1);
        }
        titulo = linea;
      } else {
        if (!cuerpo.str().empty()) {
          cuerpo << " ";
        }
        cuerpo << linea;
      }
    }
    Noticia *noticia = new Articulo (titulo, cuerpo.str(), palabrasReservadas);
    noticias.push_front(noticia);
  }
}

void LectorNoticias::leerTuitsDeFichero(std::string &fileName, std::list <Noticia*>& noticias){
  std::ifstream f;
  f.open(fileName.c_str(), std::ofstream::in);

  if (f.is_open()) {
    Json::Value raiz;
    f >> raiz;

    for ( unsigned int index = 0; index < raiz.size(); ++index ){
      unsigned id = raiz[index].get(tuitId,"0").asInt();
      std::string usuario = raiz[index].get(tuitUsuario, "").asString();
      std::string cuerpo = raiz[index].get(tuitContenido, "").asString();
      Noticia *noticia = new Tuit (id, usuario, cuerpo, palabrasReservadas);
      noticias.push_front(noticia);
    }
  } else {
  }
}

void LectorNoticias::leerNoticiasDeFicheroJson(std::string &fileName, std::list <Noticia*>& noticias){
  std::ifstream f;
  f.open(fileName.c_str(), std::ofstream::in);

  if (f.is_open()) {
    Json::Value raiz;
    f >> raiz;

    std::string titulo = raiz.get(articuloTitulo, "").asString();
    Json::Value contenido = raiz.get(articuloContenido, "");
    std::stringstream cuerpo;
    for ( unsigned int index = 0; index < contenido.size(); ++index ){
      if (!cuerpo.str().empty()) {
        cuerpo << " ";
      }
      cuerpo << contenido[index].asString();
    }

    Noticia *noticia = new Articulo (titulo, cuerpo.str(), palabrasReservadas);
    noticias.push_front(noticia);
  }
}



