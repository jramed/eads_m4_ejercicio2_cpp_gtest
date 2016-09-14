#include "gmock/gmock.h"
#include "NoticiasTestingUtilities.h"

using namespace ::testing;

TEST(Noticia, given_bodyWithoutUppercase_when_getEntidades_then_noEntityIsReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "cuerpo del articulo sin palabras en mayuscula";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(0));
}

TEST(Noticia, given_bodyWithUppercaseInTheMiddleOfWord_when_getEntidades_then_wordIsNotReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "cuerpo de la noTicia coN paLABras con mAYUSCULAS eN meDio";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(0));
}

TEST(Noticia, given_bodyWithAllUppercaseWords_when_getEntidades_then_wordsAreReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "cuerpo del ARTICULO con PALABRAS completas en mayuscula";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(2));
  EXPECT_THAT(entidades, Contains(EntityName("ARTICULO")));
  EXPECT_THAT(entidades, Contains(EntityName("PALABRAS")));
}

TEST(Noticia, given_BodyWithUppercase_when_getEntidades_then_onlyEntitiesAreReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "Cuerpo del Articulo con palabras en Mayuscula";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(3));
  EXPECT_THAT(entidades, Contains(EntityName("Cuerpo")));
  EXPECT_THAT(entidades, Contains(EntityName("Articulo")));
  EXPECT_THAT(entidades, Contains(EntityName("Mayuscula")));
}

TEST(Noticia, given_numbersIntheBody_when_getEntidades_then_onlyEntitiesAreReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "1 Cuerpo del Articulo con 2 palabras en Mayuscula";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(3));
  EXPECT_THAT(entidades, Contains(EntityName("Cuerpo")));
  EXPECT_THAT(entidades, Contains(EntityName("Articulo")));
  EXPECT_THAT(entidades, Contains(EntityName("Mayuscula")));
}

TEST(Noticia, DISABLED_given_entitiesSeparatedByPunctuation_when_getEntidades_then_entitiesAreReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "este (Articulo) contiene ¡Entidades! separadas por ¿Puntuacion? \"Comillas\" y otros *Signos*";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(5));
  EXPECT_THAT(entidades, Contains(EntityName("Articulo")));
  EXPECT_THAT(entidades, Contains(EntityName("Entidades")));
  EXPECT_THAT(entidades, Contains(EntityName("Puntuacion")));
  EXPECT_THAT(entidades, Contains(EntityName("Signos")));
  EXPECT_THAT(entidades, Contains(EntityName("Comillas")));
}

TEST(Noticia, DISABLED_given_entitiesWithSpecialSpanishChar_when_getEntidades_then_entitiesAreReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "éste Articulo contiene Entidades acentuadas Camión separadas por especiales Españoles ADMIRACIÓN Útil";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(6));
  EXPECT_THAT(entidades, Contains(EntityName("Articulo")));
  EXPECT_THAT(entidades, Contains(EntityName("Entidades")));
  EXPECT_THAT(entidades, Contains(EntityName("Camión")));
  EXPECT_THAT(entidades, Contains(EntityName("Españoles")));
  EXPECT_THAT(entidades, Contains(EntityName("ADMIRACIÓN")));
  EXPECT_THAT(entidades, Contains(EntityName("Útil")));
}

TEST(Noticia, given_duplicateEntities_when_getEntidades_then_onlyOneCopyOfEntityIsReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "cuerpo del Articulo con Entidad duplicada. "
                       "el Articulo contiene la misma Entidad varias veces. ";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(2));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Articulo", 2))));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Entidad", 2))));
}

TEST(Noticia, given_repeatedEntities_when_getEntidades_then_everyEntityHasCorrectFrecuencyCount)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "Cuerpo del Articulo con Entidades duplicadas. "
                       "el Articulo contiene las mismas Entidades varias veces. "
                       "todas las Entidades deben tener la Frecuencia correcta. ";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(4));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Articulo", 2))));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Entidades", 3))));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Cuerpo", 1))));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Frecuencia", 1))));
}

TEST(Noticia, given_multipleEntities_when_getEntidadesRelevantes_then_onlyEntitiesOnFirstThirdAreReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "Primer tercio del Articulo con dos Entidades relevantes. "
                       "Segundo tercio del Articulo con Entidades no relevantes.  "
                       "Tercer tercio del Articulo con Entidades no relevantes.   ";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidadesRelevantes = SUT->getEntidadesRelevantes();
  delete SUT;

  //Primer is filtered out because it is in the forbiden words file
  EXPECT_THAT(entidadesRelevantes, SizeIs(2));
  EXPECT_THAT(entidadesRelevantes, Not(Contains(EntityName("Primer"))));
  EXPECT_THAT(entidadesRelevantes, Contains(EntityName("Articulo")));
  EXPECT_THAT(entidadesRelevantes, Contains(EntityName("Entidades")));
}

TEST(Noticia, given_Noticia_when_getMasFrecuente_then_mostRepeatedEntityIsReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "Primer tercio del articulo con dos Entidades relevantes. "
                       "Segundo tercio del articulo con dos Entidades relevantes "
                       "Tercer tercio del articulo con dos Entidades relevantes. ";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  EntidadNombrada entidadFrecuente = SUT->getMasFrecuente();
  delete SUT;

  EXPECT_THAT(entidadFrecuente, EntityName("Entidades"));
}

TEST(Noticia, given_NoticiaWhereFrequentEntityIsNotRelevant_when_getMasFrecuente_then_mostRepeatedEntityIsReturned)
{
  std::string titulo = "Titulo";
  std::string cuerpo = "Primer tercio del articulo con dos Entidades relevantes. "
                       "Segundo tercio del Articulo. Articulo no es relevante.    "
                       "Tercer tercio del Articulo. Pero es la más nombrada.     ";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  EntidadNombrada entidadFrecuente = SUT->getMasFrecuente();
  delete SUT;

  EXPECT_THAT(entidadFrecuente, EntityName("Articulo"));
}

TEST(Noticia, given_reservedEntities_when_getEntidades_then_onlyNonReservedEntitiesAreReturned)
{

  std::string titulo = "Titulo";
  std::string cuerpo = "Cuerpo de Un Articulo con Entidades reservadas. "
                       "el Articulo contiene Entidades repetidas Dos veces. ";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(3));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Articulo", 2))));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Entidades", 2))));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Cuerpo", 1))));
  EXPECT_THAT(entidades, Not(Contains(EntityName("Una"))));
  EXPECT_THAT(entidades, Not(Contains(EntityName("Dos"))));
}

TEST(Noticia, given_reservedEntitiesInUpperCase_when_getEntidades_then_onlyNonReservedEntitiesAreReturned)
{

  std::string titulo = "Titulo";
  std::string cuerpo = "Cuerpo de UN Articulo con Entidades reservadas. "
                       "el Articulo contiene Entidades repetidas DOS veces. ";
  std::string file = "data/ES_stopList.txt";

  Articulo *SUT = crearArticulo(titulo, cuerpo, file);
  std::list<EntidadNombrada> entidades = SUT->getEntidades();
  delete SUT;

  EXPECT_THAT(entidades, SizeIs(3));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Articulo", 2))));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Entidades", 2))));
  EXPECT_THAT(entidades, Contains(MatchEntity(EntidadNombrada("Cuerpo", 1))));
  EXPECT_THAT(entidades, Not(Contains(EntityName("Una"))));
  EXPECT_THAT(entidades, Not(Contains(EntityName("Dos"))));
}


