#include "PalabrasReservadas.h"
#include "gmock/gmock.h"

using namespace ::testing;

TEST(PalabrasReservadas, given_BuildwithfileWithReservedWords_when_NoticiaIsBuilt_then_reservedWordsAreLoadedCorrectly)
{
  std::string file = "Test/reservedWordsTest.txt";

  PalabrasReservadas *SUT = new PalabrasReservadas(file);
  std::list<std::string> reservedWords = SUT->getPalabrasReservadas(PalabrasReservadas::idioma);
  delete SUT;

  EXPECT_THAT(reservedWords, SizeIs(4));
  EXPECT_THAT(reservedWords, Contains(Eq("una")));
  EXPECT_THAT(reservedWords, Contains(Eq("dos")));
  EXPECT_THAT(reservedWords, Contains(Eq("tres")));
  EXPECT_THAT(reservedWords, Contains(Eq("cuatro")));
}


TEST(PalabrasReservadas, given_SetfileWithReservedWords_when_NoticiaIsBuilt_then_reservedWordsAreLoadedCorrectly)
{
  std::string file = "";

  PalabrasReservadas *SUT = new PalabrasReservadas(file);
  std::list<std::string> reservedWords = SUT->getPalabrasReservadas(PalabrasReservadas::idioma);
  delete SUT;

  EXPECT_THAT(reservedWords, SizeIs(0));
}

TEST(PalabrasReservadas, given_wrongFileWithReservedWords_when_NoticiaIsBuilt_then_errorIsHandledAndNoWordsAreLoaded)
{
  std::string file = "wrongFileName.txt";

  PalabrasReservadas *SUT = new PalabrasReservadas(file);
  std::list<std::string> reservedWords = SUT->getPalabrasReservadas(PalabrasReservadas::idioma);
  delete SUT;

  EXPECT_THAT(reservedWords, SizeIs(0));
}


