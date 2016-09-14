#include "Tuit.h"
#include "Agrupador.h"
#include <algorithm>

Tuit::Tuit ():
Noticia("",nullptr), id{0}, user{""}
{
}

Tuit::Tuit (int id, std::string user, std::string cuerpo, std::shared_ptr<PalabrasReservadas> palabrasReservadas)
: Noticia(cuerpo, palabrasReservadas), id(id), user(user)
{
}

Tuit::~Tuit ()
{
}

std::string Tuit::getSummary() const
{ return getCuerpo(); }


int Tuit::getId() const
{
  return id;
}

std::string Tuit::getUser() const
{
  return user;
}

void Tuit::accept(NoticiaVisitor* visitor) {
  visitor->visit(this);
}

std::string Tuit::toString() const {

  std::string salida;
  salida = "ID: " + std::to_string(getId()) + "\n" +
      "USUARIO: " + getUser() + "\n" +
      "CUERPO: " + getCuerpo() + "\n" +
      "ENTIDADES: ";

  for (auto &entidadNombrada: getEntidades()) {
    salida += entidadNombrada.toString();
    salida += " ";
  }

  salida = salida + "\n" + "MAS FRECUENTE: " + getMasFrecuente().toString();
  return salida;
}
