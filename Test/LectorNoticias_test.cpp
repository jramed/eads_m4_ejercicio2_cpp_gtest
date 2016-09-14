#include "LectorNoticias.h"
#include "Tuit.h"
#include "Articulo.h"
#include "gmock/gmock.h"
#include "NoticiasTestingUtilities.h"

using namespace ::testing;

TEST(LectorNoticias, given_pathToADirectoryWithOneFile_when_requestedReadNews_then_returnOneNewInTheContainer)
{
  LectorNoticias lectorNoticias = LectorNoticias("Test/given_pathToADirectoryWithOneFile_when_requestedReadNews_then_returnOneNewInTheContainer");
  std::list <Noticia*> noticias = lectorNoticias.leerNoticias();

  Articulo* a1 = crearArticulo("titulo1", "cuerpo de Noticia con Entidad como Entidad mas nombrada");

  EXPECT_THAT(noticias.size(), Eq(1u));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a1)));

  delete a1;
}

TEST(LectorNoticias, given_pathToADirectoryWithFiveFiles_when_requestedReadNews_then_returnFiveNewsInTheContainer)
{
  LectorNoticias lectorNoticias = LectorNoticias("Test/given_pathToADirectoryWithFiveFiles_when_requestedReadNews_then_returnFiveNewsInTheContainer");
  std::list <Noticia*> noticias = lectorNoticias.leerNoticias();

  Articulo* a1 = crearArticulo("Titulo 1", "Cuerpo del artículo 1");
  Articulo* a2 = crearArticulo("Titulo 2", "Cuerpo del artículo 2");
  Articulo* a3 = crearArticulo("Titulo 3", "Cuerpo del artículo 3");
  Articulo* a4 = crearArticulo("Titulo 4", "Cuerpo del artículo 4");
  Articulo* a5 = crearArticulo("Titulo 5", "Cuerpo del artículo 5");


  EXPECT_THAT(noticias.size(), Eq(5u));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a1)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a2)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a3)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a4)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a5)));

}

TEST(LectorNoticias, given_pathToADirectoryWithDifferentFileformatName_when_requestedReadNews_then_returnAllNewsInTheContainer)
{
  LectorNoticias lectorNoticias = LectorNoticias("Test/given_pathToADirectoryWithDifferentFileformatName_when_requestedReadNews_then_returnAllNewsInTheContainer");
  std::list <Noticia*> noticias = lectorNoticias.leerNoticias();

  Articulo* a1 = crearArticulo("titulo1", "cuerpo de Noticia con Entidad como Entidad mas nombrada");
  Articulo* a2 = crearArticulo("titulo2", "otra Noticia con Noticia como Entidad mas nombrada.");

  EXPECT_THAT(noticias.size(), Eq(2u));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a1)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a2)));
}

TEST(LectorNoticias, given_pathToADirectoryWithOneJsonFile_when_requestedReadNews_then_returnOneNewInTheContainer)
{
  LectorNoticias lectorNoticias = LectorNoticias("Test/given_pathToADirectoryWithOneJsonFile_when_requestedReadNews_then_returnOneNewInTheContainer");
  std::list <Noticia*> noticias = lectorNoticias.leerNoticias();

  Articulo* a = crearArticulo("titulo1", "cuerpo de Noticia con Entidad como Entidad mas nombrada");

  EXPECT_THAT(noticias.size(), Eq(1u));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a)));
}

TEST(LectorNoticias, given_pathToADirectoryWithOneJsonFileWithMultipleParagraphs_when_requestedReadNews_then_returnOneNewInTheContainer)
{
  LectorNoticias lectorNoticias = LectorNoticias("Test/given_pathToADirectoryWithOneJsonFileWithMultipleParagraphs_when_requestedReadNews_then_returnOneNewInTheContainer");
  std::list <Noticia*> noticias = lectorNoticias.leerNoticias();

  Articulo* a = crearArticulo("titulo1",
                              "cuerpo de Noticia con Entidad como Entidad mas nombrada "
                              "Segundo parrafo de la noticia");

  EXPECT_THAT(noticias.size(), Eq(1u));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a)));
}

TEST(LectorNoticias, given_pathToADirectoryWithFiveJsonFile_when_requestedReadNews_then_returnFiveNewInTheContainer)
{
  LectorNoticias lectorNoticias = LectorNoticias("Test/given_pathToADirectoryWithFiveJsonFile_when_requestedReadNews_then_returnFiveNewInTheContainer");
  std::list <Noticia*> noticias = lectorNoticias.leerNoticias();

  Articulo* a1 = crearArticulo("titulo1", "cuerpo de Noticia con Entidad como Entidad mas nombrada");
  Articulo* a2 = crearArticulo("titulo2", "cuerpo de Noticia con Entidad como Entidad mas nombrada "
                              "Segundo parrafo de la noticia");
  Articulo* a3 = crearArticulo("titulo3", "Cuerpo del artículo 3");
  Articulo* a4 = crearArticulo("titulo4", "Cuerpo del artículo 4");
  Articulo* a5 = crearArticulo("titulo5", "Cuerpo del artículo 5 "
                              "Esta noticia tambien tiene dos parrafos");

  EXPECT_THAT(noticias.size(), Eq(5u));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a1)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a2)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a3)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a4)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a5)));
}

TEST(LectorNoticias, given_pathToADirectoryWithNewsInTxtAndJsonFormat_when_requestedReadNews_then_returnAllNews)
{
  LectorNoticias lectorNoticias = LectorNoticias("Test/given_pathToADirectoryWithNewsInTxtAndJsonFormat_when_requestedReadNews_then_returnAllNews");
  std::list <Noticia*> noticias = lectorNoticias.leerNoticias();

  Articulo* a1 = crearArticulo("titulo1", "cuerpo de Noticia con Entidad como Entidad mas nombrada");
  Articulo* a2 = crearArticulo("titulo2", "cuerpo de Noticia con Entidad como Entidad mas nombrada "
                              "Segundo parrafo de la noticia");
  Articulo* a3 = crearArticulo("titulo3", "Cuerpo del artículo 3");
  Articulo* a4 = crearArticulo("titulo4", "Cuerpo del artículo 4");
  Articulo* a5 = crearArticulo("titulo5", "Cuerpo del artículo 5 "
                              "Esta noticia tambien tiene dos parrafos");
  Articulo* a6 = crearArticulo("Titulo 21", "Cuerpo del artículo 21");
  Articulo* a7 = crearArticulo("Titulo 22", "Cuerpo del artículo 22");
  Articulo* a8 = crearArticulo("Titulo 23", "Cuerpo del artículo 23");
  Articulo* a9 = crearArticulo("Titulo 24", "Cuerpo del artículo 24");
  Articulo* a10 = crearArticulo("Titulo 25", "Cuerpo del artículo 25");

  EXPECT_THAT(noticias.size(), Eq(10u));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a1)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a2)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a3)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a4)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a5)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a6)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a7)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a8)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a9)));
  EXPECT_THAT(noticias, Contains(MatchArticulo(a10)));
}

TEST(LectorNoticias, given_pathToADirectoryWithOneFileAndOneTuit_when_requestedReadTuits_then_returnOneTuitInTheContainer)
{
  LectorNoticias lectorNoticias = LectorNoticias("Test/given_pathToADirectoryWithOneFileAndOneTuit_when_requestedReadTuits_then_returnOneTuitInTheContainer");
  std::list <Noticia*> noticias = lectorNoticias.leerTuits();

  Tuit* t1 = crearTuit (1, "@pepe_perez", "Liberan a los dos sospechosos detenidos por el asesinato de un niño de 11 años en Liverpool");

  EXPECT_THAT(noticias.size(), Eq(1u));
  EXPECT_THAT(noticias, Contains(MatchTuit(t1)));

  delete t1;
}

TEST(LectorNoticias, given_pathToADirectoryWithOneFileAndThreeTuits_when_requestedReadTuits_then_returnThreeTuitsInTheContainer)
{
  LectorNoticias lectorNoticias = LectorNoticias("Test/given_pathToADirectoryWithOneFileAndThreeTuits_when_requestedReadTuits_then_returnThreeTuitsInTheContainer");
  std::list <Noticia*> noticias = lectorNoticias.leerTuits();

  Tuit* t1 = crearTuit (123, "@pepe_perez", "Liberan a los dos sospechosos detenidos por el asesinato de un niño de 11 años en Liverpool");
  Tuit* t2 = crearTuit (1, "@juan_toqui", "Detienen a seis jóvenes más en relación con el asesinato de el niño de Liverpool");
  Tuit* t3 = crearTuit (2, "@pupulupu", "Siguen los interrogatorios a los detenidos por el asesinato de el niño de Liverpool");


  EXPECT_THAT(noticias.size(), Eq(3u));
  EXPECT_THAT(noticias, Contains(MatchTuit(t1)));
  EXPECT_THAT(noticias, Contains(MatchTuit(t2)));
  EXPECT_THAT(noticias, Contains(MatchTuit(t3)));

  delete t1;
  delete t2;
  delete t3;
}

TEST(LectorNoticias, given_pathToADirectoryWithNewsInTxtAndJsonFormatAndTuits_when_requestedReadNewsAndTuits_then_returnAllNewsAndTuits)
{
  LectorNoticias lectorNoticias = LectorNoticias("Test/given_pathToADirectoryWithNewsInTxtAndJsonFormatAndTuits_when_requestedReadNews_then_returnAllNewsAndTuits");
  std::list <Noticia*> noticias = lectorNoticias.leerNoticias();

  //As we are mixing Articulo and Tuit we cannot test on complete fields
  //because the casting on the matcher would throw a SEGFAULT
  //if we try to convert to the incorrect type. We must limit to comparing summaries.
  //The rest of the test cases already test that the rest of the fields are correctly read.
  std::string titulo1 = "titulo1";
  std::string titulo2 = "titulo2";
  std::string titulo3 = "titulo3";
  std::string titulo4 = "titulo4";
  std::string titulo5 = "titulo5";
  std::string titulo6 = "Titulo 21";
  std::string titulo7 = "Titulo 22";
  std::string titulo8 = "Titulo 23";
  std::string titulo9 = "Titulo 24";
  std::string titulo10 = "Titulo 25";
  std::string tuit1 = "Liberan a los dos sospechosos detenidos por el asesinato de un niño de 11 años en Liverpool";
  std::string tuit2 = "Detienen a seis jóvenes más en relación con el asesinato de el niño de Liverpool";
  std::string tuit3 = "Siguen los interrogatorios a los detenidos por el asesinato de el niño de Liverpool";

  EXPECT_THAT(noticias.size(), Eq(13u));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(titulo1)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(titulo2)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(titulo3)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(titulo4)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(titulo5)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(titulo6)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(titulo7)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(titulo8)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(titulo9)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(titulo10)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(tuit1)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(tuit2)));
  EXPECT_THAT(noticias, Contains(NoticiaSummary(tuit3)));
}
