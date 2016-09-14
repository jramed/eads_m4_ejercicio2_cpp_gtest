#include "gmock/gmock.h"
#include "NoticiasTestingUtilities.h"
#include <Agrupador.h>

using namespace ::testing;

class AgrupadorTest : public ::testing::Test {
protected:
  Agrupador agrupador;
};

TEST_F(AgrupadorTest, given_FrequentEntityFromArticulo1IsInTitleFromArticulo2AndRelevantEntitiesOfArticulo1AreInArticulo2_when_esAgrupable_then_TrueIsReturned)
{
  std::string titulo1 = "Titulo";
  std::string cuerpo1 = "Entidad Entidad Entidad más nombrada. "
                        "Otras entidades Secundarias de relleno.";
  std::string titulo2 = "Titulo que contiene Entidad";
  std::string cuerpo2 = "Articulo Articulo Articulo con otra Entidad más nombrada. ";
  std::string file = "data/ES_stopList.txt";

  Articulo* SUT1 = crearArticulo(titulo1, cuerpo1, file);
  Articulo* SUT2 = crearArticulo(titulo2, cuerpo2, file);

  EXPECT_TRUE(agrupador.esAgrupable(SUT2,SUT1));
  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_FrequentEntityFromArticulo1IsInTitleFromArticulo2ButRelevantEntitiesOfArticulo1AreNotInArticulo2_when_esAgrupable_then_FalseIsReturned)
{
  std::string titulo1 = "Titulo";
  std::string cuerpo1 = "Entidades Relevantes del articulo. "
                        "la Entidad mas Nombrada es Entidad.";
  std::string titulo2 = "Titulo que contiene Entidad";
  std::string cuerpo2 = "Cuerpo del articulo. ";
  std::string file = "data/ES_stopList.txt";

  Articulo* SUT1 = crearArticulo(titulo1, cuerpo1, file);
  Articulo* SUT2 = crearArticulo(titulo2, cuerpo2, file);

  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));
  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_FrequentEntityFromArticulo1IsNotInTitleFromArticulo2ButRelevantEntitiesOfArticulo1AreInArticulo2_when_esAgrupable_then_FalseIsReturned)
{
  std::string titulo1 = "Titulo";
  std::string cuerpo1 = "Entidad Entidad Entidad más nombrada. "
                        "Otras entidades Secundarias de relleno.";
  std::string titulo2 = "Titulo de otra noticia";
  std::string cuerpo2 = "Articulo Articulo Articulo con otra Entidad más nombrada. ";
  std::string file = "data/ES_stopList.txt";

  Articulo* SUT1 = crearArticulo(titulo1, cuerpo1, file);
  Articulo* SUT2 = crearArticulo(titulo2, cuerpo2, file);

  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));
  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_FrequentEntityFromArticulo1IsNotInTitleFromArticulo2AndRelevantEntitiesOfArticulo1AreNotInArticulo2_when_esAgrupable_then_FalseIsReturned)
{
  std::string titulo1 = "Titulo";
  std::string cuerpo1 = "Entidad Entidad Entidad más nombrada. "
                        "Otras entidades Secundarias de relleno.";
  std::string titulo2 = "Titulo de otra noticia";
  std::string cuerpo2 = "Articulo Articulo Articulo. ";
  std::string file = "data/ES_stopList.txt";

  Articulo* SUT1 = crearArticulo(titulo1, cuerpo1, file);
  Articulo* SUT2 = crearArticulo(titulo2, cuerpo2, file);

  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));
  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_ArticuloWithoutEntities_when_esAgrupable_then_FalseIsReturned)
{
  std::string titulo1 = "Titulo";
  std::string cuerpo1 = "Entidad Entidad Entidad más nombrada. "
                        "Otras entidades Secundarias de relleno.";

  std::string titulo2 = "Titulo de otra noticia";
  std::string cuerpo2 = "noticia sin entidades. ";
  std::string file = "data/ES_stopList.txt";

  Articulo* SUT1 = crearArticulo(titulo1, cuerpo1, file);
  Articulo* SUT2 = crearArticulo(titulo2, cuerpo2, file);

  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));
  EXPECT_FALSE(agrupador.esAgrupable(SUT1,SUT2));
  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_twoTuitsWithSameEntity_when_esAgrupable_then_returnsTrue)
{
  Tuit *SUT1 = crearTuit(1, "@pepe", "tuit con Entidad");
  Tuit *SUT2 = crearTuit(2, "@Juan", "Entidad dentro de otro tuit");

  EXPECT_TRUE(agrupador.esAgrupable(SUT1,SUT2));
  EXPECT_TRUE(agrupador.esAgrupable(SUT2,SUT1));

  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_twoTuitsWithDifferentEntities_when_esAgrupable_then_returnsFalse)
{
  Tuit *SUT1 = crearTuit(1, "@pepe", "tuit con Entidad");
  Tuit *SUT2 = crearTuit(2, "@Juan", "otro tuit con entidades Diferentes");

  EXPECT_FALSE(agrupador.esAgrupable(SUT1,SUT2));
  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));

  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_aTuitWithNoEntities_when_esAgrupable_then_returnsFalse)
{
  Tuit *SUT1 = crearTuit(1, "@pepe", "tuit con Entidad");
  Tuit *SUT2 = crearTuit(2, "@Juan", "otro tuit sin entidades");

  EXPECT_FALSE(agrupador.esAgrupable(SUT1,SUT2));
  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));

  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_twoTuitsWithNoEntities_when_esAgrupable_then_returnsFalse)
{
  Tuit *SUT1 = crearTuit(1, "@pepe", "tuit sin entidades");
  Tuit *SUT2 = crearTuit(2, "@Juan", "otro tuit sin entidades");

  EXPECT_FALSE(agrupador.esAgrupable(SUT1,SUT2));
  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));

  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_aTuitWithTheMostFrequentEntityOfAnArticulo_when_esAgrupable_then_returnsTrue)
{
  Tuit *SUT1 = crearTuit(1, "@pepe", "tuit con Entidad");
  Articulo *SUT2 = crearArticulo("titulo", "Articulo con Entidad como Entidad mas nombrada");

  EXPECT_TRUE(agrupador.esAgrupable(SUT1,SUT2));
  EXPECT_TRUE(agrupador.esAgrupable(SUT2,SUT1));

  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_aTuitWithoutTheMostFrequentEntityOfAnArticulo_when_esAgrupable_then_returnsFalse)
{
  Tuit *SUT1 = crearTuit(1, "@pepe", "Tuit sin entidades Comunes con articulo");
  Articulo *SUT2 = crearArticulo("titulo", "Articulo con Entidad como Entidad mas nombrada");

  EXPECT_FALSE(agrupador.esAgrupable(SUT1,SUT2));
  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));

  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_aTuitWithSomeCommonEntitiesWithArticuloButTheMostFrequent_when_esAgrupable_then_returnsFalse)
{
  Tuit *SUT1 = crearTuit(1, "@pepe", "Tuit entidades Comunes con Articulo pero no la mas Nombrada");
  Articulo *SUT2 = crearArticulo("titulo", "Articulo con Entidad como Entidad mas nombrada");

  EXPECT_FALSE(agrupador.esAgrupable(SUT1,SUT2));
  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));

  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_aTuitWithoutEntitiesAndAnArticle_when_esAgrupable_then_returnsFalse)
{
  Tuit *SUT1 = crearTuit(1, "@pepe", "tuit sin entidades");
  Articulo *SUT2 = crearArticulo("titulo", "Articulo con Entidad como Entidad mas nombrada");

  EXPECT_FALSE(agrupador.esAgrupable(SUT1,SUT2));
  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));

  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_anArticuloWithoutEntitiesAndATuit_when_esAgrupable_then_returnsFalse)
{
  Tuit *SUT1 = crearTuit(1, "@pepe", "tuit con Entidad");
  Articulo *SUT2 = crearArticulo("titulo", "articulo sin entidades");

  EXPECT_FALSE(agrupador.esAgrupable(SUT1,SUT2));
  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));

  delete SUT1;
  delete SUT2;
}

TEST_F(AgrupadorTest, given_anArticuloAndATuitWithoutEntities_when_esAgrupable_then_returnsFalse)
{
  Tuit *SUT1 = crearTuit(1, "@pepe", "tuit sin entidades");
  Articulo *SUT2 = crearArticulo("titulo", "articulo sin entidades");

  EXPECT_FALSE(agrupador.esAgrupable(SUT1,SUT2));
  EXPECT_FALSE(agrupador.esAgrupable(SUT2,SUT1));

  delete SUT1;
  delete SUT2;
}

