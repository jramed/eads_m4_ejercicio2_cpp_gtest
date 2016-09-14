#include <PresentadorAgrupacionesJson.h>
#include <PresentadorNoticiasJson.h>

#include "../Json/json.h"


PresentadorAgrupacionesJson::PresentadorAgrupacionesJson (std::ostream & os)
: PresentadorAgrupaciones(os)
{
}

PresentadorAgrupacionesJson::~PresentadorAgrupacionesJson ()
{
}

Json::Value PresentadorAgrupacionesJson::presentarGrupo (Analizador::grupoNoticias agrupacion) {
  Json::Value grupo = Json::Value(Json::objectValue);
  grupo["titulo"] = (*agrupacion.begin())->getSummary();

  Json::Value elementos = Json::Value(Json::arrayValue);
  std::set<std::string> conjuntoEntidades;
  for (auto &noticia : agrupacion) {
    PresentadorNoticiasJson noticiaJson (noticia);
    elementos.append(noticiaJson());
    conjuntoEntidades.insert(noticia->getMasFrecuente().getEntidadNombrada());
  }
  grupo["elementos"] = elementos;

  Json::Value entidades = Json::Value(Json::arrayValue);
  for (auto &entidad : conjuntoEntidades) {
    entidades.append(entidad);
  }
  grupo["entidades"] = entidades;
  return grupo;
}

void PresentadorAgrupacionesJson::presentar (Analizador::agrupacionEntidadFrecuente agrupacion)
{
  Json::Value grupos = Json::Value(Json::arrayValue);
  for (auto grp : agrupacion) {
     grupos.append(presentarGrupo(grp.second));
  }
  Json::Value raiz = Json::Value(Json::objectValue);
  raiz["grupos"] = grupos;

  os << raiz;
}


void PresentadorAgrupacionesJson::presentar (Analizador::agrupacionTematica agrupacion) {
  Json::Value grupos = Json::Value(Json::arrayValue);
  for (auto grp : agrupacion) {
     grupos.append(presentarGrupo(grp));
  }
  Json::Value raiz = Json::Value(Json::objectValue);
  raiz["grupos"] = grupos;

  os << raiz;

}

