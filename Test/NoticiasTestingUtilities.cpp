#include "NoticiasTestingUtilities.h"
#include "gmock/gmock.h"


using namespace ::testing;


std::ostream& operator<<(std::ostream& os, const Noticia* noticia)
{
  os << "[" << noticia->getSummary() << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Tuit* tuit)
{
  os << "[ ID: " << tuit->getId() << "\n"
     << "  USUARIO: " << tuit->getUser() << "\n"
     << "  CUERPO: " << tuit->getCuerpo() << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Articulo* articulo)
{
  os << "[ TITULO: " << articulo->getTitulo() << "\n"
     << "  CUERPO: " << articulo->getCuerpo() << "]";
    return os;
}


std::string empty{""};

Articulo* crearArticulo(std::string titulo, std::string cuerpo, std::string file){
    std::shared_ptr<PalabrasReservadas> palabrasReservadas =
        std::make_shared<PalabrasReservadas>(file);
    Articulo * noticia = new Articulo(titulo, cuerpo, palabrasReservadas);
    return noticia;
}

Articulo* crearArticulo(std::string titulo, std::string cuerpo){
  return crearArticulo(titulo, cuerpo, empty);
}

Tuit* crearTuit(int id, std::string user, std::string cuerpo, std::string file){
    std::shared_ptr<PalabrasReservadas> palabrasReservadas =
        std::make_shared<PalabrasReservadas>(file);
    Tuit * noticia = new Tuit(id, user, cuerpo, palabrasReservadas);
    return noticia;
}

Tuit* crearTuit(int id, std::string user, std::string cuerpo){
  return crearTuit(id, user, cuerpo, empty);
}


