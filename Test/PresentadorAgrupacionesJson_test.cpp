#include "PresentadorAgrupacionesJson.h"
#include "Analizador.h"
#include "Articulo.h"
#include <sstream>
#include <string>
#include "gmock/gmock.h"

#include "../Json/json.h"
#include "NoticiasTestingUtilities.h"

using namespace ::testing;


Articulo* JsonToArticulo(Json::Value arg)
{
  EXPECT_TRUE(arg.isMember("titulo"));
  EXPECT_TRUE(arg.isMember("parrafos"));

  std::string titulo = arg.get("titulo", Json::Value()).asString();
  Json::Value parrafos = arg.get("parrafos", Json::Value());
  std::stringstream cuerpo;
  for (unsigned int j = 0; j < parrafos.size(); ++j) {
    cuerpo << parrafos[j].asString();
  }
  return crearArticulo(titulo, cuerpo.str());
}

Tuit* JsonToTuit(Json::Value arg)
{
  EXPECT_TRUE(arg.isMember("id"));
  EXPECT_TRUE(arg.isMember("usuario"));
  EXPECT_TRUE(arg.isMember("tuit"));

  int id = arg.get("id", Json::Value()).asInt();
  std::string usuario = arg.get("usuario", Json::Value()).asString();
  std::string cuerpo = arg.get("tuit", Json::Value()).asString();
  return crearTuit(id, usuario, cuerpo);
}

void getNoticiasFromJson(Json::Value arg, std::vector<Articulo*> &articulos, std::vector<Tuit*> &tuits)
{
  EXPECT_TRUE(arg.isArray());
  for (unsigned int i = 0; i < arg.size(); ++i) {
    Json::Value elemento = arg[i];
    if (elemento.isMember("titulo")) {
      articulos.push_back(JsonToArticulo(elemento));
    }
    else {
      tuits.push_back(JsonToTuit(elemento));
    }
  }
}

template <typename T>
T JsonToValue(Json::Value arg);

template <>
std::string JsonToValue(Json::Value arg)
{
  EXPECT_TRUE(arg.isString());
  return arg.asString();
}

template <>
Json::Value JsonToValue(Json::Value arg)
{
  return arg;
}

template <typename T>
std::vector<T> JsonToArray(Json::Value arg)
{
  EXPECT_TRUE(arg.isArray());
  std::vector<T> salida;
  for (unsigned int i = 0; i < arg.size(); ++i) {
    Json::Value elemento = arg[i];
    salida.push_back(JsonToValue<T>(elemento));
  }
  return salida;
}


MATCHER_P(ContainsKey, key,
    std::string("Json ") + (negation ? "doesn't contain " : "contains ") + PrintToString(key))
{ return arg.isMember(key); }

MATCHER_P(KeyValueIsString, key,
    std::string("Json value for key ") + PrintToString(key) + (negation ? " is not " : " is ") + std::string("a string"))
{ return arg.get(key, Json::Value()).isString(); }

MATCHER_P2(ContainsKeyValue, key, value,
    std::string("Json ") + (negation ? "doesn't contain " : "contains ") +
    std::string("key:value [") + PrintToString(key) + std::string(":") + PrintToString(value) + std::string("]"))
{
  return Matches(ContainsKey(key))(arg) and
         Matches(Eq(value))(arg.get(key, Json::Value()));
}

MATCHER_P(IsIn, values,
    std::string("") + (negation ? "doesn't match " : "matches ") + std::string("any of ") + PrintToString(values))
{
  for (auto value : values) {
    if (Matches(Eq(value))(arg)) {
      return true;
    }
  }
  return false;
}


void checkGroup (Json::Value group,
                 std::vector<std::string> titulos,
                 std::vector<std::string> entidades,
                 std::vector<Articulo*> articulos,
                 std::vector<Tuit*> tuits)
{
  EXPECT_THAT(group, ContainsKey("titulo"));
  auto tituloGrupo = JsonToValue<std::string>(group.get("titulo", Json::Value()));
  EXPECT_THAT(tituloGrupo, IsIn(titulos));

  EXPECT_THAT(group, ContainsKey("entidades"));
  auto entidadesGrupo = JsonToArray<std::string>(group.get("entidades", Json::Value()));
  EXPECT_THAT(entidadesGrupo, UnorderedElementsAreArray(entidades));

  EXPECT_THAT(group, ContainsKey("elementos"));
  std::vector<Articulo*> articulosGrupo;
  std::vector<Tuit*> tuitsGrupo;
  getNoticiasFromJson(group.get("elementos", Json::Value()),
                      articulosGrupo, tuitsGrupo);
  EXPECT_THAT(articulosGrupo.size(), Eq(articulos.size()));
  for (auto articulo : articulos) {
    EXPECT_THAT(articulosGrupo, Contains(MatchArticulo(articulo)));
  }
  EXPECT_THAT(tuitsGrupo.size(), Eq(tuits.size()));
  for (auto tuit : tuits) {
    EXPECT_THAT(tuitsGrupo, Contains(MatchTuit(tuit)));
  }

  for (auto articulo : articulosGrupo) {
    delete articulo;
  }
  for (auto tuit : tuitsGrupo) {
    delete tuit;
  }
}


TEST(PresentadorAgrupacionesJson, given_agrupacionEntidadFrecuente_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string titulo{"titulo1"};
  std::string cuerpo{"Cuerpo de la noticia1"};
  Articulo *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"Cuerpo de la noticia2"};
  Articulo *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"Cuerpo de la noticia3"};
  Articulo *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::string entidad {"Cuerpo"};

  Analizador::grupoNoticias grp;
  grp.insert(noticia1);
  grp.insert(noticia2);
  grp.insert(noticia3);

  Analizador::agrupacionEntidadFrecuente agrupacion;
  agrupacion[entidad] = grp;

  std::stringstream streamPresentacion;
  PresentadorAgrupacionesJson SUT(streamPresentacion);
  SUT.presentar(agrupacion);

  Json::Value raiz;
  streamPresentacion >> raiz;

  EXPECT_THAT(raiz, ContainsKey("grupos"));
  Json::Value gruposJson = raiz.get("grupos", Json::Value());
  EXPECT_TRUE(gruposJson.isArray());
  EXPECT_THAT(gruposJson.size(), Eq(1));

  //for each group
  Json::Value grupoJson = gruposJson[0];

  std::vector<std::string> expectedTitulos;
  expectedTitulos.push_back(titulo);
  expectedTitulos.push_back(titulo2);
  expectedTitulos.push_back(titulo3);

  std::vector<std::string> expectedEntidades;
  expectedEntidades.push_back(entidad);

  std::vector<Articulo*> expectedArticulos;
  expectedArticulos.push_back(noticia1);
  expectedArticulos.push_back(noticia2);
  expectedArticulos.push_back(noticia3);

  std::vector<Tuit*> expectedTuits;

  checkGroup (grupoJson,
              expectedTitulos,
              expectedEntidades,
              expectedArticulos,
              expectedTuits);

  delete noticia1;
  delete noticia2;
  delete noticia3;
}

TEST(PresentadorAgrupacionesJson, given_variousAgrupacionEntidadFrecuente_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string titulo{"titulo1"};
  std::string cuerpo{"Cuerpo de la noticia1"};
  Articulo *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"Cuerpo de la noticia2"};
  Articulo *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"Cuerpo de la noticia3 con Entidad como Entidad frecuente"};
  Articulo *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::string entidad1 {"Cuerpo"};
  std::string entidad2 {"Entidad"};

  Analizador::grupoNoticias grp;
  grp.insert(noticia1);
  grp.insert(noticia2);

  Analizador::agrupacionEntidadFrecuente agrupacion;
  agrupacion[entidad1] = grp;

  grp.clear();
  grp.insert(noticia3);
  agrupacion[entidad2] = grp;

  std::stringstream streamPresentacion;
  PresentadorAgrupacionesJson SUT(streamPresentacion);
  SUT.presentar(agrupacion);

  Json::Value raiz;
  streamPresentacion >> raiz;

  EXPECT_THAT(raiz, ContainsKey("grupos"));
  Json::Value gruposJson = raiz.get("grupos", Json::Value());
  EXPECT_TRUE(gruposJson.isArray());
  EXPECT_THAT(gruposJson.size(), Eq(2));

  //for each group
  Json::Value grupoJson = gruposJson[0];

  std::vector<std::string> expectedTitulos;
  expectedTitulos.push_back(titulo);
  expectedTitulos.push_back(titulo2);

  std::vector<std::string> expectedEntidades;
  expectedEntidades.push_back(entidad1);

  std::vector<Articulo*> expectedArticulos;
  expectedArticulos.push_back(noticia1);
  expectedArticulos.push_back(noticia2);

  std::vector<Tuit*> expectedTuits;

  checkGroup (grupoJson,
              expectedTitulos,
              expectedEntidades,
              expectedArticulos,
              expectedTuits);


  grupoJson = gruposJson[1];

  expectedTitulos.clear();
  expectedTitulos.push_back(titulo3);

  expectedEntidades.clear();
  expectedEntidades.push_back(entidad2);

  expectedArticulos.clear();
  expectedArticulos.push_back(noticia3);

  checkGroup (grupoJson,
              expectedTitulos,
              expectedEntidades,
              expectedArticulos,
              expectedTuits);

  delete noticia1;
  delete noticia2;
  delete noticia3;
}


TEST(PresentadorAgrupacionesJson, given_agrupacionEntidadFrecuenteWithArticuloAndTuit_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string titulo{"titulo1"};
  std::string cuerpo{"Cuerpo de la noticia1"};
  Articulo *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"Cuerpo de la noticia2"};
  Articulo *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string cuerpo3 {"Cuerpo del tuit"};
  int id = 34343;
  std::string user{"@pepe"};
  Tuit* tuit = crearTuit(id, user, cuerpo3);

  std::string entidad {"Cuerpo"};

  Analizador::grupoNoticias grp;
  grp.insert(noticia1);
  grp.insert(noticia2);
  grp.insert(tuit);

  Analizador::agrupacionEntidadFrecuente agrupacion;
  agrupacion[entidad] = grp;

  std::stringstream streamPresentacion;
  PresentadorAgrupacionesJson SUT(streamPresentacion);
  SUT.presentar(agrupacion);

  Json::Value raiz;
  streamPresentacion >> raiz;

  EXPECT_THAT(raiz, ContainsKey("grupos"));
  Json::Value gruposJson = raiz.get("grupos", Json::Value());
  EXPECT_TRUE(gruposJson.isArray());
  EXPECT_THAT(gruposJson.size(), Eq(1));

  //for each group
  Json::Value grupoJson = gruposJson[0];

  std::vector<std::string> expectedTitulos;
  expectedTitulos.push_back(titulo);
  expectedTitulos.push_back(titulo2);
  expectedTitulos.push_back(cuerpo3);

  std::vector<std::string> expectedEntidades;
  expectedEntidades.push_back(entidad);

  std::vector<Articulo*> expectedArticulos;
  expectedArticulos.push_back(noticia1);
  expectedArticulos.push_back(noticia2);

  std::vector<Tuit*> expectedTuits;
  expectedTuits.push_back(tuit);

  checkGroup (grupoJson,
              expectedTitulos,
              expectedEntidades,
              expectedArticulos,
              expectedTuits);

  delete noticia1;
  delete noticia2;
  delete tuit;
}

TEST(PresentadorAgrupacionesJson, given_agrupacionEntidadFrecuenteWithOnlyTuits_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string cuerpo1 {"Cuerpo del tuit1"};
  int id1 = 1111;
  std::string user1{"@pepe1"};
  Tuit* tuit1 = crearTuit(id1, user1, cuerpo1);

  std::string cuerpo2 {"Cuerpo del tuit2"};
  int id2 = 2222;
  std::string user2{"@pepe2"};
  Tuit* tuit2 = crearTuit(id2, user2, cuerpo2);

  std::string cuerpo3 {"Cuerpo del tuit3"};
  int id3 = 3333;
  std::string user3{"@pepe3"};
  Tuit* tuit3 = crearTuit(id3, user3, cuerpo3);

  std::string entidad {"Cuerpo"};

  Analizador::grupoNoticias grp;
  grp.insert(tuit1);
  grp.insert(tuit2);
  grp.insert(tuit3);

  Analizador::agrupacionEntidadFrecuente agrupacion;
  agrupacion[entidad] = grp;

  std::stringstream streamPresentacion;
  PresentadorAgrupacionesJson SUT(streamPresentacion);
  SUT.presentar(agrupacion);

  Json::Value raiz;
  streamPresentacion >> raiz;

  EXPECT_THAT(raiz, ContainsKey("grupos"));
  Json::Value gruposJson = raiz.get("grupos", Json::Value());
  EXPECT_TRUE(gruposJson.isArray());
  EXPECT_THAT(gruposJson.size(), Eq(1));

  //for each group
  Json::Value grupoJson = gruposJson[0];

  std::vector<std::string> expectedTitulos;
  expectedTitulos.push_back(cuerpo1);
  expectedTitulos.push_back(cuerpo2);
  expectedTitulos.push_back(cuerpo3);

  std::vector<std::string> expectedEntidades;
  expectedEntidades.push_back(entidad);

  std::vector<Articulo*> expectedArticulos;

  std::vector<Tuit*> expectedTuits;
  expectedTuits.push_back(tuit1);
  expectedTuits.push_back(tuit2);
  expectedTuits.push_back(tuit3);

  checkGroup (grupoJson,
              expectedTitulos,
              expectedEntidades,
              expectedArticulos,
              expectedTuits);

  delete tuit1;
  delete tuit2;
  delete tuit3;
}

TEST(PresentadorAgrupacionesJson, given_agrupacionTematica_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string titulo{"titulo1"};
  std::string cuerpo{"Cuerpo de la noticia1 con Cuerpo como entidad frecuente"};
  Articulo *articulo1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"Cuerpo de la noticia2 con Entidad como Entidad frecuente"};
  Articulo *articulo2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"Cuerpo de la noticia3 con otras entidades Secundarias"};
  Articulo *articulo3 = crearArticulo(titulo3, cuerpo3);

  Analizador::grupoNoticias grp;
  grp.insert(articulo1);
  grp.insert(articulo2);
  grp.insert(articulo3);

  Analizador::agrupacionTematica agrupacion;
  agrupacion.push_back(grp);

  std::stringstream streamPresentacion;
  PresentadorAgrupacionesJson SUT(streamPresentacion);
  SUT.presentar(agrupacion);

  Json::Value raiz;
  streamPresentacion >> raiz;

  EXPECT_THAT(raiz, ContainsKey("grupos"));
  Json::Value gruposJson = raiz.get("grupos", Json::Value());
  EXPECT_TRUE(gruposJson.isArray());
  EXPECT_THAT(gruposJson.size(), Eq(1));

  //for each group
  Json::Value grupoJson = gruposJson[0];

  std::vector<std::string> expectedTitulos;
  expectedTitulos.push_back(titulo);
  expectedTitulos.push_back(titulo2);
  expectedTitulos.push_back(titulo3);

  std::vector<std::string> expectedEntidades;
  expectedEntidades.push_back("Cuerpo");
  expectedEntidades.push_back("Entidad");

  std::vector<Articulo*> expectedArticulos;
  expectedArticulos.push_back(articulo1);
  expectedArticulos.push_back(articulo2);
  expectedArticulos.push_back(articulo3);

  std::vector<Tuit*> expectedTuits;

  checkGroup (grupoJson,
              expectedTitulos,
              expectedEntidades,
              expectedArticulos,
              expectedTuits);

  delete articulo1;
  delete articulo2;
  delete articulo3;
}

TEST(PresentadorAgrupacionesJson, given_variousAgrupacionTematica_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string titulo{"titulo1"};
  std::string cuerpo{"Cuerpo de la noticia1 con Cuerpo como entidad frecuente"};
  Articulo *articulo1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"Cuerpo de la noticia2 con Entidad como Entidad frecuente"};
  Articulo *articulo2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"Cuerpo de la noticia3 con Noticia como entidad frecuente de la Noticia"};
  Articulo *articulo3 = crearArticulo(titulo3, cuerpo3);

  Analizador::grupoNoticias grp;
  grp.insert(articulo1);
  grp.insert(articulo2);

  Analizador::agrupacionTematica agrupacion;
  agrupacion.push_back(grp);

  grp.clear();
  grp.insert(articulo3);
  agrupacion.push_back(grp);


  std::stringstream streamPresentacion;
  PresentadorAgrupacionesJson SUT(streamPresentacion);
  SUT.presentar(agrupacion);

  Json::Value raiz;
  streamPresentacion >> raiz;

  EXPECT_THAT(raiz, ContainsKey("grupos"));
  Json::Value gruposJson = raiz.get("grupos", Json::Value());
  EXPECT_TRUE(gruposJson.isArray());
  EXPECT_THAT(gruposJson.size(), Eq(2));

  //for each group
  Json::Value grupoJson = gruposJson[0];

  std::vector<std::string> expectedTitulos;
  expectedTitulos.push_back(titulo);
  expectedTitulos.push_back(titulo2);

  std::vector<std::string> expectedEntidades;
  expectedEntidades.push_back("Cuerpo");
  expectedEntidades.push_back("Entidad");

  std::vector<Articulo*> expectedArticulos;
  expectedArticulos.push_back(articulo1);
  expectedArticulos.push_back(articulo2);

  std::vector<Tuit*> expectedTuits;

  checkGroup (grupoJson,
              expectedTitulos,
              expectedEntidades,
              expectedArticulos,
              expectedTuits);


  grupoJson = gruposJson[1];

  expectedTitulos.clear();
  expectedTitulos.push_back(titulo3);

  expectedEntidades.clear();
  expectedEntidades.push_back("Noticia");

  expectedArticulos.clear();
  expectedArticulos.push_back(articulo3);

  checkGroup (grupoJson,
              expectedTitulos,
              expectedEntidades,
              expectedArticulos,
              expectedTuits);

  delete articulo1;
  delete articulo2;
  delete articulo3;
}

TEST(PresentadorAgrupacionesJson, given_AgrupacionTematicaWithArticuloAndTuit_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string titulo{"titulo1"};
  std::string cuerpo{"Cuerpo de la noticia1 con Cuerpo como entidad frecuente"};
  Articulo *articulo1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"Cuerpo de la noticia2 con Entidad como Entidad frecuente"};
  Articulo *articulo2 = crearArticulo(titulo2, cuerpo2);

  std::string cuerpo3 {"Cuerpo del tuit con Tuit como entidad frecuente del Tuit"};
  int id = 34343;
  std::string user{"@pepe"};
  Tuit* tuit = crearTuit(id, user, cuerpo3);

  Analizador::grupoNoticias grp;
  grp.insert(articulo1);
  grp.insert(articulo2);
  grp.insert(tuit);

  Analizador::agrupacionTematica agrupacion;
  agrupacion.push_back(grp);

  std::stringstream streamPresentacion;
  PresentadorAgrupacionesJson SUT(streamPresentacion);
  SUT.presentar(agrupacion);

  Json::Value raiz;
  streamPresentacion >> raiz;

  EXPECT_THAT(raiz, ContainsKey("grupos"));
  Json::Value gruposJson = raiz.get("grupos", Json::Value());
  EXPECT_TRUE(gruposJson.isArray());
  EXPECT_THAT(gruposJson.size(), Eq(1));

  //for each group
  Json::Value grupoJson = gruposJson[0];

  std::vector<std::string> expectedTitulos;
  expectedTitulos.push_back(titulo);
  expectedTitulos.push_back(titulo2);
  expectedTitulos.push_back(cuerpo3);

  std::vector<std::string> expectedEntidades;
  expectedEntidades.push_back("Cuerpo");
  expectedEntidades.push_back("Entidad");
  expectedEntidades.push_back("Tuit");

  std::vector<Articulo*> expectedArticulos;
  expectedArticulos.push_back(articulo1);
  expectedArticulos.push_back(articulo2);

  std::vector<Tuit*> expectedTuits;
  expectedTuits.push_back(tuit);

  checkGroup (grupoJson,
              expectedTitulos,
              expectedEntidades,
              expectedArticulos,
              expectedTuits);

  delete articulo1;
  delete articulo2;
  delete tuit;
}

TEST(PresentadorAgrupacionesJson, given_AgrupacionTematicaWithOnlyTuits_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string cuerpo1 {"Cuerpo del tuit1 con Cuerpo como entidad frecuente"};
  int id1 = 1111;
  std::string user1{"@pepe1"};
  Tuit* tuit1 = crearTuit(id1, user1, cuerpo1);

  std::string cuerpo2 {"Cuerpo del tuit2 con Entidad como Entidad frecuente"};
  int id2 = 2222;
  std::string user2{"@pepe2"};
  Tuit* tuit2 = crearTuit(id2, user2, cuerpo2);

  std::string cuerpo3 {"Cuerpo del tuit3 con Tuit como entidad frecuente del Tuit"};
  int id3 = 3333;
  std::string user3{"@pepe3"};
  Tuit* tuit3 = crearTuit(id3, user3, cuerpo3);

  Analizador::grupoNoticias grp;
  grp.insert(tuit1);
  grp.insert(tuit2);
  grp.insert(tuit3);

  Analizador::agrupacionTematica agrupacion;
  agrupacion.push_back(grp);

  std::stringstream streamPresentacion;
  PresentadorAgrupacionesJson SUT(streamPresentacion);
  SUT.presentar(agrupacion);

  Json::Value raiz;
  streamPresentacion >> raiz;

  EXPECT_THAT(raiz, ContainsKey("grupos"));
  Json::Value gruposJson = raiz.get("grupos", Json::Value());
  EXPECT_TRUE(gruposJson.isArray());
  EXPECT_THAT(gruposJson.size(), Eq(1));

  //for each group
  Json::Value grupoJson = gruposJson[0];

  std::vector<std::string> expectedTitulos;
  expectedTitulos.push_back(cuerpo1);
  expectedTitulos.push_back(cuerpo2);
  expectedTitulos.push_back(cuerpo3);

  std::vector<std::string> expectedEntidades;
  expectedEntidades.push_back("Entidad");
  expectedEntidades.push_back("Cuerpo");
  expectedEntidades.push_back("Tuit");

  std::vector<Articulo*> expectedArticulos;

  std::vector<Tuit*> expectedTuits;
  expectedTuits.push_back(tuit1);
  expectedTuits.push_back(tuit2);
  expectedTuits.push_back(tuit3);

  checkGroup (grupoJson,
              expectedTitulos,
              expectedEntidades,
              expectedArticulos,
              expectedTuits);

  delete tuit1;
  delete tuit2;
  delete tuit3;
}

