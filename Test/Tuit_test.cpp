#include "Tuit.h"
#include "gmock/gmock.h"
#include "NoticiasTestingUtilities.h"

using namespace ::testing;

TEST(Tuit, given_tuit_when_getCuerpo_then_tuitTextIsReturned)
{
  std::string cuerpo = "cuerpo del tuit";
  int id = 3434;
  std::string user = "@pepe";

  Tuit *SUT = crearTuit(id, user, cuerpo);
  EXPECT_THAT(SUT->getCuerpo(), Eq(cuerpo));
  delete SUT;

}

TEST(Tuit, given_tuit_when_getSummary_then_tuitTextIsReturned)
{
  std::string cuerpo = "cuerpo del tuit";
  int id = 34343;
  std::string user = "@pepe";

  Tuit *SUT = crearTuit(id, user, cuerpo);
  EXPECT_THAT(SUT->getSummary(), Eq(cuerpo));
  delete SUT;

}

TEST(Tuit, given_tuit_when_getId_then_tuitIdReturned)
{
  std::string cuerpo = "cuerpo del tuit";
  int id = 34343;
  std::string user = "@pepe";

  Tuit *SUT = crearTuit(id, user, cuerpo);
  EXPECT_THAT(SUT->getId(), Eq(id));
  delete SUT;

}

TEST(Tuit, given_tuit_when_getUser_then_tuitUserReturned)
{
  std::string cuerpo = "cuerpo del tuit";
  int id = 34343;
  std::string user = "@pepe";

  Tuit *SUT = crearTuit(id, user, cuerpo);
  EXPECT_THAT(SUT->getUser(), Eq(user));
  delete SUT;
}


