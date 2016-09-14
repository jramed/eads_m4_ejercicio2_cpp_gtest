#include <PresentadorNoticiasJson.h>
#include "Articulo.h"
#include "Tuit.h"
#include "../Json/json.h"

PresentadorNoticiasJson::PresentadorNoticiasJson (Noticia* noticia)
{
  resultado = Json::Value(Json::objectValue);
  noticia->accept(this);
}

PresentadorNoticiasJson::~PresentadorNoticiasJson ()
{
}

void PresentadorNoticiasJson::visit(Articulo *articulo){
  resultado["titulo"] = articulo->getTitulo();
  resultado["parrafos"] = Json::Value(Json::arrayValue);
  resultado["parrafos"].append(articulo->getCuerpo());
}

void PresentadorNoticiasJson::visit(Tuit *tuit){
  resultado["id"] = tuit->getId();
  resultado["usuario"] = tuit->getUser();
  resultado["tuit"] = tuit->getCuerpo();
}

Json::Value PresentadorNoticiasJson::operator()()
{
  return resultado;
}
