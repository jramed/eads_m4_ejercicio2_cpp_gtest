#include "Utilidades.h"
#include "gmock/gmock.h"

using namespace ::testing;

class UtilidadesFileNameFormat: public TestWithParam<std::string>
{

};

TEST_P(UtilidadesFileNameFormat, given_wrongFileNameFormat_when_checkedFileNameFormat_then_wrongFormat)
{
  std::string fileName = GetParam();

  EXPECT_THAT(utilidades::isFormatoNombreFicheroCorrecto(fileName), Eq(false));
  //EXPECT_THAT(true,Eq(false)) << "Fix this in Tarea3 or by generating an utility class for files or by using pimpl idiom";
}

TEST_P(UtilidadesFileNameFormat, given_correctFileNameFormat_when_checkedFormatCorrect_then_correctFormat)
{
  std::string fileName = "newC00001_001.ES.txt";

  EXPECT_THAT(utilidades::isFormatoNombreFicheroCorrecto(fileName), Eq(true));
}

INSTANTIATE_TEST_CASE_P(FileNames, UtilidadesFileNameFormat,
		::testing::Values(
			std::string("NewC00001_001.ES.txt"),
			std::string("nEwC00001_001.ES.txt"),
			std::string("neWc00001_001.ES.txt"),
			std::string("newc00001_001.ES.txt"),
			std::string("newCe00001_001.ES.txt"),
			std::string("newC0001_001.ES.txt"),
			std::string("newC000001_001.ES.txt"),
			std::string("newC00001-001.ES.txt"),
			std::string("newC00001_a01.ES.txt"),
			std::string("newC00001_01.ES.txt"),
			std::string("newC00101_9001.ES.txt"),
			std::string("newC00001_001.eS.txt"),
			std::string("newC00001_001.Es.txt"),
			std::string("newC00001_001.ES.Txt"),
			std::string("newC00001_001.ES.tXt"),
			std::string("newC00001_001.ES.txT")
		));
