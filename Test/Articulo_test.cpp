#include "gmock/gmock.h"
#include "NoticiasTestingUtilities.h"

using namespace ::testing;


TEST(Articulo, given_articulo_when_getCuerpo_then_articleBodyIsReturned)
{
  std::string cuerpo = "Cuerpo de la Noticia";
  std::string titulo = "Titulo";

  Articulo *SUT = crearArticulo(titulo, cuerpo);
  EXPECT_THAT(SUT->getCuerpo(), Eq(cuerpo));
  delete SUT;
}

TEST(Articulo, given_articulo_when_getTitulo_then_articleTitleIsReturned)
{
  std::string cuerpo = "Cuerpo de la Noticia";
  std::string titulo = "Titulo";

  Articulo *SUT = crearArticulo(titulo, cuerpo);
  EXPECT_THAT(SUT->getTitulo(), Eq(titulo));
  delete SUT;
}

TEST(Articulo, given_articulo_when_getSummary_then_articleTitleIsReturned)
{
  std::string cuerpo = "Cuerpo de la Noticia";
  std::string titulo = "Titulo";

  Articulo *SUT = crearArticulo(titulo, cuerpo);
  EXPECT_THAT(SUT->getSummary(), Eq(titulo));
  delete SUT;
}




