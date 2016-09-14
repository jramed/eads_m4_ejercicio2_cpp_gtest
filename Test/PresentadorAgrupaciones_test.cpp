#include "PresentadorAgrupacionesTxt.h"
#include "Analizador.h"
#include "Articulo.h"
#include <sstream>
#include "gmock/gmock.h"
#include "NoticiasTestingUtilities.h"

using namespace ::testing;


TEST(PresentadorAgrupacionesTxt, given_agrupacionEntidadFrecuente_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string titulo{"titulo1"};
  std::string cuerpo{"Cuerpo de la noticia1"};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"Cuerpo de la noticia2"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"Cuerpo de la noticia3"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::string entidad {"Entidad"};

  Analizador::grupoNoticias grp;
  grp.insert(noticia1);
  grp.insert(noticia2);
  grp.insert(noticia3);

  Analizador::agrupacionEntidadFrecuente agrupacion;
  agrupacion[entidad] = grp;

  std::stringstream resultado;
  resultado << "\n" << entidad << "\n";
  for (auto n : grp) {
      resultado << "*[" << n->getSummary() << "]\n";
  }

  std::stringstream streamPresentacion;
  PresentadorAgrupacionesTxt SUT(streamPresentacion);

  SUT.presentar(agrupacion);

  EXPECT_THAT(streamPresentacion.str(), Eq(resultado.str()));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}

TEST(PresentadorAgrupacionesTxt, given_agrupacionTematica_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string titulo{"titulo1"};
  std::string cuerpo{"Cuerpo de la noticia1"};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"Cuerpo de la noticia2"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"Cuerpo de la noticia3"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  Analizador::grupoNoticias grp;
  grp.insert(noticia1);
  grp.insert(noticia2);
  grp.insert(noticia3);

  Analizador::agrupacionTematica agrupacion;
  agrupacion.push_back(grp);

  std::stringstream resultado;
  bool isFirst = true;
  for (auto n : grp) {
      if (isFirst) {
        resultado << "[" << n->getSummary() << "]\n";
        isFirst = false;
      }
      else {
        resultado << "   *[" << n->getSummary() << "]\n";
      }
  }
  resultado << "\n";

  std::stringstream streamPresentacion;
  PresentadorAgrupacionesTxt SUT(streamPresentacion);

  SUT.presentar(agrupacion);

  EXPECT_THAT(streamPresentacion.str(), Eq(resultado.str()));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}


TEST(PresentadorAgrupacionesTxt, given_variousAgrupacionEntidadFrecuente_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string titulo{"titulo1"};
  std::string cuerpo{"Cuerpo de la noticia1"};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"Cuerpo de la noticia2"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"Cuerpo de la noticia3"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::string entidad1 {"Entidad1"};
  std::string entidad2 {"Entidad2"};

  Analizador::grupoNoticias grp;
  grp.insert(noticia1);
  grp.insert(noticia2);

  Analizador::agrupacionEntidadFrecuente agrupacion;
  agrupacion[entidad1] = grp;

  std::stringstream resultado;
  resultado << "\n" << entidad1 << "\n";
  for (auto n : grp) {
      resultado << "*[" << n->getSummary() << "]\n";
  }

  grp.clear();
  grp.insert(noticia3);

  agrupacion[entidad2] = grp;

  resultado << "\n" << entidad2 << "\n";
  for (auto n : grp) {
      resultado << "*[" << n->getSummary() << "]\n";
  }


  std::stringstream streamPresentacion;
  PresentadorAgrupacionesTxt SUT(streamPresentacion);

  SUT.presentar(agrupacion);

  EXPECT_THAT(streamPresentacion.str(), Eq(resultado.str()));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}

TEST(PresentadorAgrupacionesTxt, given_variousAgrupacionTematica_when_presentar_then_groupIsCorrectlyPresented)
{
  std::string titulo{"titulo1"};
  std::string cuerpo{"Cuerpo de la noticia1"};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"Cuerpo de la noticia2"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"Cuerpo de la noticia3"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  Analizador::grupoNoticias grp;
  grp.insert(noticia1);
  grp.insert(noticia2);

  Analizador::agrupacionTematica agrupacion;
  agrupacion.push_back(grp);

  std::stringstream resultado;
  bool isFirst = true;
  for (auto n : grp) {
      if (isFirst) {
        resultado << "[" << n->getSummary() << "]\n";
        isFirst = false;
      }
      else {
        resultado << "   *[" << n->getSummary() << "]\n";
      }
  }
  resultado << "\n";

  grp.clear();
  grp.insert(noticia3);
  agrupacion.push_back(grp);
  resultado << "[" << noticia3->getSummary() << "]\n\n";


  std::stringstream streamPresentacion;
  PresentadorAgrupacionesTxt SUT(streamPresentacion);

  SUT.presentar(agrupacion);

  EXPECT_THAT(streamPresentacion.str(), Eq(resultado.str()));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}



