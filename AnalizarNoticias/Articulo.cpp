#include "Articulo.h"
#include "Agrupador.h"
#include <algorithm>


Articulo::Articulo ()
: Noticia(), titulo{""}
{ }

Articulo::Articulo(std::string titulo, std::string cuerpo, std::shared_ptr<PalabrasReservadas> palabrasReservadas)
: Noticia(cuerpo, palabrasReservadas),
  titulo(titulo)
{ }


Articulo::~Articulo ()
{ }

std::string Articulo::getTitulo() const {
  return titulo;
}

std::string Articulo::getSummary() const {
  return titulo;
}

void Articulo::accept( NoticiaVisitor* visitor) {
  visitor->visit(this);
}

std::string Articulo::toString() const {

  std::string salida;
  salida = "TITULO: " + getTitulo() + "\n" + "CUERPO: " + getCuerpo() + "\n"
      + "ENTIDADES: ";

  for (auto &entidadNombrada: getEntidades()) {
    salida += entidadNombrada.toString();
    salida += " ";
  }

  salida = salida + "\n" + "MAS FRECUENTE: " + getMasFrecuente().toString();
  return salida;
}

