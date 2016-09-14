#include "Analizador.h"
#include "Articulo.h"
#include "LectorNoticias.h"
#include "NoticiasTestingUtilities.h"
#include "gmock/gmock.h"


using namespace ::testing;

MATCHER_P(ContainsGroupForEntity, name,
    std::string("there ") + (negation ? "is not " : "is ") + std::string("a group for entity ")  + PrintToString(name))
{ return arg.find(name) != arg.end(); }


TEST(Analizador, given_oneNews_when_agruparNoticias_then_newsAreGrouped)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"cuerpo de Noticia con Entidad como Entidad mas nombrada"};
  Noticia * noticia1 = crearArticulo(titulo, cuerpo );

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto group = SUT.agruparNoticias();
  EXPECT_THAT(group, SizeIs(1));

  EXPECT_THAT(group, ContainsGroupForEntity("Entidad"));
  EXPECT_THAT(group["Entidad"], UnorderedElementsAre(ArticuloTitle(titulo)));

  delete noticia1;
}


TEST(Analizador, given_newsWithSameFrequentEntity_when_agruparNoticias_then_newsAreGrouped)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"cuerpo de Noticia con Entidad como Entidad mas nombrada"};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"otra noticia con Entidad como Entidad mas nombrada. Debe agruparse con noticia1"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto group = SUT.agruparNoticias();
  EXPECT_THAT(group, SizeIs(1));

  EXPECT_THAT(group, ContainsGroupForEntity("Entidad"));
  EXPECT_THAT(group["Entidad"], UnorderedElementsAre(
      ArticuloTitle(titulo),
      ArticuloTitle(titulo2)));

  delete noticia1;
  delete noticia2;
}


TEST(Analizador, given_newsWithDifferentFrequentEntity_when_agruparNoticias_then_newsAreNotGrouped)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"cuerpo de Noticia con Entidad como Entidad mas nombrada"};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"otra Noticia con Noticia como Entidad mas nombrada."};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto group = SUT.agruparNoticias();
  EXPECT_THAT(group, SizeIs(2));

  EXPECT_THAT(group, ContainsGroupForEntity("Entidad"));
  EXPECT_THAT(group["Entidad"], UnorderedElementsAre(
      ArticuloTitle(titulo)));

  EXPECT_THAT(group, ContainsGroupForEntity("Noticia"));
  EXPECT_THAT(group["Noticia"], UnorderedElementsAre(
      ArticuloTitle(titulo2)));

  delete noticia1;
  delete noticia2;
}

TEST(Analizador, given_newsWithSameAndDifferentFrequentEntity_when_agruparNoticias_then_newsWithSameFrequentEntitiesAreGrouped)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"cuerpo de Noticia con Entidad como Entidad mas nombrada"};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"otra noticia con Entidad como Entidad mas nombrada. Debe agruparse con noticia1"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"otra Noticia con Noticia como Entidad mas nombrada. Debe formar su propia agrupacion"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto group = SUT.agruparNoticias();
  EXPECT_THAT(group, SizeIs(2));

  EXPECT_THAT(group, ContainsGroupForEntity("Entidad"));
  EXPECT_THAT(group["Entidad"], UnorderedElementsAre(
      ArticuloTitle(titulo),
      ArticuloTitle(titulo2)));

  EXPECT_THAT(group, ContainsGroupForEntity("Noticia"));
  EXPECT_THAT(group["Noticia"], UnorderedElementsAre(
      ArticuloTitle(titulo3)));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}

TEST(Analizador, given_unorderedNewsWithSameAndDifferentFrequentEntity_when_agruparNoticias_then_newsWithSameFrequentEntitiesAreGrouped)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"cuerpo de Noticia con Entidad como Entidad mas nombrada"};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"otra Noticia con Noticia como Entidad mas nombrada."};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"otra Noticia con Noticia como Entidad mas nombrada. Debe agruparse con noticia2"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::string titulo4{"titulo4"};
  std::string cuerpo4{"otra noticia con Entidad como Entidad mas nombrada. Debe agruparse con noticia1"};
  Noticia *noticia4 = crearArticulo(titulo4, cuerpo4);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);
  noticias.push_back(noticia4);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto group = SUT.agruparNoticias();
  EXPECT_THAT(group, SizeIs(2));

  EXPECT_THAT(group, ContainsGroupForEntity("Entidad"));
  EXPECT_THAT(group["Entidad"], UnorderedElementsAre(
      ArticuloTitle(titulo),
      ArticuloTitle(titulo4)));

  EXPECT_THAT(group, ContainsGroupForEntity("Noticia"));
  EXPECT_THAT(group["Noticia"], UnorderedElementsAre(
      ArticuloTitle(titulo2),
      ArticuloTitle(titulo3)));

  delete noticia1;
  delete noticia2;
  delete noticia3;
  delete noticia4;
}

TEST(Analizador, given_oneNews_when_agruparNoticiasGeneral_then_newsAreGrouped)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(1));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(ArticuloTitle("titulo1"))));

  delete noticia1;
}


TEST(Analizador, given_newsWhereFrequentEntityFromFirstIsNotInArticuloTitleFromSecond_when_agruparNoticiasGeneral_then_newsAreNotGrouped)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene las entidades relevantes de la primera: "
                      "Entidad1 Entidad2 Entidad3"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);

  Analizador SUT;
  SUT.setNoticas(noticias);


  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(2));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo1"))));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
       ArticuloTitle("titulo2"))));

  delete noticia1;
  delete noticia2;
}

TEST(Analizador, given_newsThatMatchGroupingCriteria2_when_agruparNoticiasGeneral_then_newsAreGrouped)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene las entidades relevantes de la primera: "
                      "Entidad1 Entidad2 Entidad3"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(1));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo1"),
      ArticuloTitle("titulo2 con Entidad6"))));

  delete noticia1;
  delete noticia2;
}

TEST(Analizador, given_newsWhereThirdOfRelevantEntitiesFromFirstAreNotOnSecond_when_agruparNoticiasGeneral_then_newsAreNotGrouped)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas no contiene las entidades relevantes de la primera "};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(2));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo1"))));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo2 con Entidad6"))));

  delete noticia1;
  delete noticia2;
}

TEST(Analizador, given_moreNewsThatMatchGroupingCriteria2_when_agruparNoticiasGeneral_then_newsAreGrouped)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene un tercio de las entidades relevantes de la primera: "
                      "Entidad1"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"entidades relevantes: Noticia1 Noticia2 Noticia3    "
                      "entidades no relevantes: Noticia4 Noticia5 Noticia6 "
                      "entidad mas nombrada: Noticia6                      "};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::string titulo4{"titulo4 con Noticia6"};
  std::string cuerpo4{"entidad mas nombrada: Noticia8 Noticia8 Noticia8 "
                      "ademas contiene un tercio de las entidades relevantes de la primera: "
                      "Noticia1"};
  Noticia *noticia4 = crearArticulo(titulo4, cuerpo4);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);
  noticias.push_back(noticia4);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(2));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo1"),
      ArticuloTitle("titulo2 con Entidad6"))));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
       ArticuloTitle("titulo3"),
       ArticuloTitle("titulo4 con Noticia6"))));


  delete noticia1;
  delete noticia2;
  delete noticia3;
  delete noticia4;
}


TEST(Analizador, given_someNewsMatchGroupingCriteria2AndOtherNot_when_agruparNoticiasGeneral_then_nonconformingNewsAreOnTheirOwnGroup)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene un tercio de las entidades relevantes de la primera: "
                      "Entidad1"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"esta Noticia no debe Agruparse con las demas"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(2));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo1"),
      ArticuloTitle("titulo2 con Entidad6"))));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
       ArticuloTitle("titulo3"))));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}

TEST(Analizador, given_noticiaWithoutEntities_when_agruparNoticiasGeneral_then_noticiaIsOnItsOwnGroup)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene un tercio de las entidades relevantes de la primera: "
                      "Entidad1"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"esta noticia no debe agruparse con ninguna"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(2));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo1"),
      ArticuloTitle("titulo2 con Entidad6"))));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
       ArticuloTitle("titulo3"))));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}

TEST(Analizador, given_someNewsWithoutEntities_when_agruparNoticiasGeneral_then_theyFormTheirOwnGroup)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene un tercio de las entidades relevantes de la primera: "
                      "Entidad1"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"esta noticia no debe agruparse con ninguna"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::string titulo4{"titulo4"};
  std::string cuerpo4{"otra noticia sin entidades"};
  Noticia *noticia4 = crearArticulo(titulo4, cuerpo4);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);
  noticias.push_back(noticia4);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(3));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo1"),
      ArticuloTitle("titulo2 con Entidad6"))));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
       ArticuloTitle("titulo3"))));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
       ArticuloTitle("titulo4"))));

  delete noticia1;
  delete noticia2;
  delete noticia3;
  delete noticia4;
}

TEST(Analizador, given_N2withN3ByFrequentEntity_N1withN2_N3withN1N2ByN3SameLabelThanN2_when_agruparNoticiasGeneral_then_newsAreGroupedTogether)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene las entidades relevantes de la primera: "
                      "Entidad1 Entidad2 Entidad3"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3"};
  std::string cuerpo3{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                     "deberia agruparse junto con la segunda noticia"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(1));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo1"),
      ArticuloTitle("titulo2 con Entidad6"),
      ArticuloTitle("titulo3"))));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}


TEST(Analizador, given_given_N2withN1AndN3withN2_when_agruparNoticiasGeneral_then_twoGroupsAreGenerated)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene las entidades relevantes de la primera: "
                      "Entidad1 Entidad2 Entidad3"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3 con Entidad8"};
  std::string cuerpo3{"entidad mas nombrada: Entidad9 Entidad9 Entidad9 "
                      "deberia agruparse junto con la segunda noticia "
                      "porque tambien nombra la Entidad8"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(2));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo1"),
      ArticuloTitle("titulo2 con Entidad6"))));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
       ArticuloTitle("titulo3 con Entidad8"),
       ArticuloTitle("titulo2 con Entidad6"))));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}

TEST(Analizador, given_twoNewsAreGroupableWithAnother_when_agruparNoticiasGeneral_then_allAreGroupedTogether)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene las entidades relevantes de la primera: "
                      "Entidad1 Entidad2 Entidad3"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3 con Entidad6"};
  std::string cuerpo3{"entidad mas nombrada: Entidad9 Entidad9 Entidad9 "
                      "deberia agruparse junto con la primera noticia "
                      "porque tambien nombra la Entidad1"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(1));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle("titulo1"),
      ArticuloTitle("titulo2 con Entidad6"),
      ArticuloTitle("titulo3 con Entidad6"))));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}

TEST(Analizador, given_newsReadFromFileRelatedWithChavez_when_agruparNoticias_then_justOneGroupIsGenerated)
{
  LectorNoticias lectorNoticias{"Test/given_newsReadFromFile_when_agruparNoticias_then_justOneGroupIsGenerated"};
  Analizador SUT{};
  SUT.setNoticas(lectorNoticias.leerNoticias());

  std::string noticia1 = "Chávez anuncia ante Álvaro Uribe que recibirá en Venezuela a un enviado de las FARC ";
  std::string noticia2 = "Chávez se reunirá en Caracas con delegados de las FARC ";
  std::string noticia3 = "Las FARC rechazan el ofrecimiento de Chávez de liberar rehenes en Venezuela ";
  std::string noticia4 = "Chávez llega a Bogotá para entrevistar se con Uribe sobre los secuestrados de las FARC ";
  std::string noticia5 = "Chávez llega a Bogotá para mediar en la liberación de secuestrados por las FARC ";

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(1));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle(noticia1),
      ArticuloTitle(noticia2),
      ArticuloTitle(noticia3),
      ArticuloTitle(noticia4),
      ArticuloTitle(noticia5))));

}

TEST(Analizador, given_newsReadFromFileRelatedWithHuracanDean_when_agruparNoticias_then_justOneGroupIsGenerated)
{

  LectorNoticias lectorNoticias{"Test/given_newsReadFromFileRelatedWithHuracanDean_when_agruparNoticias_then_justOneGroupIsGenerated"};
  Analizador SUT{};
  SUT.setNoticas(lectorNoticias.leerNoticias());

  std::string noticia1 = "Dean pasa a ser tormenta tropical ";
  std::string noticia2 = "' Dean ' deja Yucatán debilitado pero podría fortalecerse en el Golfo de México ";
  std::string noticia3 = "El huracán Dean podría cobrar fuerza a el volver a las aguas cálidas de el Golfo de México ";
  std::string noticia4 = "Más de 400.000 evacuados en Cuba ante la amenaza de inundaciones por el ' Dean ' ";
  std::string noticia5 = "' Dean ' llega a el Caribe mexicano convertido en un huracán ' potencialmente catastrófico ' ";
  std::string noticia6 = "Las lluvias y vientos devastadores de el Dean se sienten ya en la costa oeste de México ";
  std::string noticia7 = "El ' Dean ' se debilita y en las próximas horas podría convertir se en tormenta tropical ";
  std::string noticia8 = "El huracán Dean baja a categoría 1 tras atravesar el Yucatán mexicano ";
  std::string noticia9 = "' Dean ' provoca otros tres muertos antes de extinguir se en el interior de México ";
  std::string noticia10= "Dean pierde fuerza a el adentrar se en México ";

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(1));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle(noticia1),
      ArticuloTitle(noticia2),
      ArticuloTitle(noticia3),
      ArticuloTitle(noticia4),
      ArticuloTitle(noticia5),
      ArticuloTitle(noticia6),
      ArticuloTitle(noticia7),
      ArticuloTitle(noticia8),
      ArticuloTitle(noticia9),
      ArticuloTitle(noticia10))));
}

TEST(Analizador, given_2gruposDeNoticiasAgrupadas_when_unGrupoNoContieneLasNoticiasAgrupadasDeOtro_then_quedanLosDosGrupos)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene las entidades relevantes de la primera: "
                      "Entidad1 Entidad2 Entidad3"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3 con Entidad8"};
  std::string cuerpo3{"entidad mas nombrada: Entidad9 Entidad9 Entidad9 "
                      "deberia agruparse junto con la segunda noticia "
                      "porque tambien nombra la Entidad8"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(2));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle(titulo),
      ArticuloTitle(titulo2))));
    EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle(titulo2),
      ArticuloTitle(titulo3))));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}

TEST(Analizador, given_2gruposDeNoticiasAgrupadas_when_unGrupoContieneLasNoticiasAgrupadasDeOtro_then_soloQuedanElGrupoConMasNoticias)
{

  std::string titulo{"titulo1"};
  std::string cuerpo{"entidades relevantes: Entidad1 Entidad2 Entidad3    "
                     "entidades no relevantes: Entidad4 Entidad5 Entidad6 "
                     "entidad mas nombrada: Entidad6                      "};
  Noticia *noticia1 = crearArticulo(titulo, cuerpo);

  std::string titulo2{"titulo2 con Entidad6"};
  std::string cuerpo2{"entidad mas nombrada: Entidad8 Entidad8 Entidad8 "
                      "ademas contiene las entidades relevantes de la primera: "
                      "Entidad1 Entidad2 Entidad3"};
  Noticia *noticia2 = crearArticulo(titulo2, cuerpo2);

  std::string titulo3{"titulo3 con Entidad8 y Entidad6"};
  std::string cuerpo3{"entidad mas nombrada: Entidad9 Entidad9 Entidad9 "
                      "deberia agruparse junto con la primera y segunda noticia "
                      "porque tambien contiene las entidade lelevantes"
                      "la Entidad8 y Entidad1, Entidad2 y Entidad3"};
  Noticia *noticia3 = crearArticulo(titulo3, cuerpo3);

  std::list<Noticia*> noticias;
  noticias.push_back(noticia1);
  noticias.push_back(noticia2);
  noticias.push_back(noticia3);

  Analizador SUT;
  SUT.setNoticas(noticias);

  auto groups = SUT.agruparNoticiasGeneral();
  EXPECT_THAT(groups, SizeIs(1));
  EXPECT_THAT(groups, Contains(UnorderedElementsAre(
      ArticuloTitle(titulo),
      ArticuloTitle(titulo2),
      ArticuloTitle(titulo3))));

  delete noticia1;
  delete noticia2;
  delete noticia3;
}

