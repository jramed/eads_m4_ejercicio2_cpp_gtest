#include "Utilidades.h"
#include <vector>
#include "gmock/gmock.h"

using namespace ::testing;

TEST(Utilidades, given_character_when_upperCase_then_returnTrue)
{
  EXPECT_THAT(utilidades::esMayuscula('N'), Eq(true));
  EXPECT_THAT(utilidades::esMayuscula('O'), Eq(true));
  EXPECT_THAT(utilidades::esMayuscula('J'), Eq(true));
  EXPECT_THAT(utilidades::esMayuscula('A'), Eq(true));
}

TEST(Utilidades, DISABLED_given_spanishCharacter_when_upperCase_then_returnTrue)
{
  EXPECT_THAT(utilidades::esMayuscula('Ñ'), Eq(true));
  EXPECT_THAT(utilidades::esMayuscula('Ó'), Eq(true));
  EXPECT_THAT(utilidades::esMayuscula('Á'), Eq(true));
  EXPECT_THAT(utilidades::esMayuscula('Í'), Eq(true));
}

TEST(Utilidades, given_character_when_lowerCase_then_returnFalse)
{
  EXPECT_THAT(utilidades::esMayuscula('m'), Eq(false));
  EXPECT_THAT(utilidades::esMayuscula('i'), Eq(false));
  EXPECT_THAT(utilidades::esMayuscula('b'), Eq(false));
  EXPECT_THAT(utilidades::esMayuscula('e'), Eq(false));
}

TEST(Utilidades, given_spanishCharacter_when_lowerCase_then_returnTrue)
{
  EXPECT_THAT(utilidades::esMayuscula('ñ'), Eq(false));
  EXPECT_THAT(utilidades::esMayuscula('ó'), Eq(false));
  EXPECT_THAT(utilidades::esMayuscula('é'), Eq(false));
  EXPECT_THAT(utilidades::esMayuscula('ú'), Eq(false));
}

TEST(Utilidades, given_aText_when_WordsSeparatedWithWhiteSpaces_then_SeparedTheWords)
{
  std::string text = "This is a test to check if these words are separated";
  std::vector<std::string> wordsSeparated = utilidades::splitTextInWords(text);

  EXPECT_THAT(wordsSeparated, SizeIs(11));
  EXPECT_THAT(wordsSeparated, Contains(Eq("This")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("is")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("a")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("test")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("to")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("check")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("if")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("these")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("words")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("are")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("separated")));
}

TEST(Utilidades, given_aText_when_WordsSeparatedWithTabs_then_SeparedTheWords)
{
  std::string text = "This	is	a	test	to	check	if	these	words	are	separated";
  std::vector<std::string> wordsSeparated = utilidades::splitTextInWords(text);

  EXPECT_THAT(wordsSeparated, SizeIs(11));
  EXPECT_THAT(wordsSeparated, Contains(Eq("This")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("is")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("a")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("test")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("to")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("check")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("if")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("these")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("words")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("are")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("separated")));
}

TEST(Utilidades, given_aText_when_WordsSeparatedWithFeedLine_then_SeparedTheWords)
{
  std::string text = "This\ris\ra\rtest\rto\rcheck\rif\rthese\rwords\rare\rseparated";
  std::vector<std::string> wordsSeparated = utilidades::splitTextInWords(text);

  EXPECT_THAT(wordsSeparated, SizeIs(11));
  EXPECT_THAT(wordsSeparated, Contains(Eq("This")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("is")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("a")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("test")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("to")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("check")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("if")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("these")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("words")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("are")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("separated")));
}

TEST(Utilidades, given_aText_when_WordsSeparatedWithNewLine_then_SeparedTheWords)
{
  std::string text = "This\nis\na\ntest\nto\ncheck\nif\nthese\nwords\nare\nseparated";
  std::vector<std::string> wordsSeparated = utilidades::splitTextInWords(text);

  EXPECT_THAT(wordsSeparated, SizeIs(11));
  EXPECT_THAT(wordsSeparated, Contains(Eq("This")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("is")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("a")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("test")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("to")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("check")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("if")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("these")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("words")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("are")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("separated")));
}

TEST(Utilidades, given_aText_when_WordsSeparatedWithNewLineAndFeedLine_then_SeparedTheWords)
{
  std::string text = "This\r\nis\r\na\r\ntest\r\nto\r\ncheck\r\nif\r\nthese\r\nwords\r\nare\r\nseparated";
  std::vector<std::string> wordsSeparated = utilidades::splitTextInWords(text);

  EXPECT_THAT(wordsSeparated, SizeIs(11));
  EXPECT_THAT(wordsSeparated, Contains(Eq("This")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("is")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("a")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("test")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("to")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("check")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("if")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("these")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("words")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("are")));
  EXPECT_THAT(wordsSeparated, Contains(Eq("separated")));
}

TEST(Utilidades, DISABLED_given_aText_when_containsPunctuation_then_punctuationIsRemoved)
{
  std::string text = "Esta es \"una prueba\". ¡Consiste! en  eliminar	¿signos de puntuación?";
  std::string newText = utilidades::removePuctuationFromText(text);

  EXPECT_THAT(newText, Eq("Esta es una prueba Consiste en  eliminar	signos de puntuación"));
}


