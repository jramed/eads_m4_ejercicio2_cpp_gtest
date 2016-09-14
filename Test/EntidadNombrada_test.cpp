#include "EntidadNombrada.h"
#include "gmock/gmock.h"

TEST(EntidadNombrada, given_EntidadIsConstructedWithFrequency_when_getFrecuencia_then_returnsGivenFrequency)
{
  std::string entidad = "Entidad";
  int frecuencia = 10;

  EntidadNombrada* SUT = new EntidadNombrada(entidad, frecuencia);
  EXPECT_EQ(frecuencia, SUT->getFrecuencia());
  delete SUT;
}


TEST(EntidadNombrada, given_EntidadIsConstructedWithEntity_when_getEntidad_then_returnsGivenEntity)
{
  std::string entidad = "Entidad";
  int frecuencia = 10;

  EntidadNombrada* SUT = new EntidadNombrada(entidad, frecuencia);
  EXPECT_EQ(entidad, SUT->getEntidadNombrada());
  delete SUT;
}

TEST(EntidadNombrada, given_FrequencyChangeInEntidad_when_getFrecuencia_then_returnsNewGivenFrequency)
{
  std::string entidad = "Entidad";
  int frecuencia = 10;
  int nuevaFrecuencia = 20;

  EntidadNombrada* SUT = new EntidadNombrada(entidad, frecuencia);
  SUT->setFrecuencia(nuevaFrecuencia);
  EXPECT_EQ(nuevaFrecuencia, SUT->getFrecuencia());
  delete SUT;
}

TEST(EntidadNombrada, given_EntityChangedInEntidad_when_getEntidad_then_returnsNewGivenEntity)
{
  std::string entidad = "Entidad";
  std::string nuevaEntidad = "nuevaEntidad";
  int frecuencia = 10;

  EntidadNombrada* SUT = new EntidadNombrada(entidad, frecuencia);
  SUT->setEntidadNombrada(nuevaEntidad);
  EXPECT_EQ(nuevaEntidad, SUT->getEntidadNombrada());
  delete SUT;
}

TEST(EntidadNombrada, given_EntidadDefaultConstructed_then_frequencyIsInitializedToZero)
{
  EntidadNombrada* SUT = new EntidadNombrada();
  EXPECT_EQ(0, SUT->getFrecuencia());
  delete SUT;
}

TEST(EntidadNombrada, given_EntidadDefaultConstructed_then_entityIsInitializedToEmptyString)
{
  EntidadNombrada* SUT = new EntidadNombrada();
  EXPECT_EQ(std::string(), SUT->getEntidadNombrada());
  delete SUT;
}

TEST(EntidadNombrada, given_twoEntidadWithSameEntity_when_esIgual_then_returnsTrue)
{
  std::string entidad = "Entidad";
  int frecuencia1 = 10;
  int frecuencia2 = 20;

  EntidadNombrada* SUT1 = new EntidadNombrada(entidad, frecuencia1);
  EntidadNombrada* SUT2 = new EntidadNombrada(entidad, frecuencia2);
  EXPECT_TRUE(*SUT1 == *SUT2);
  delete SUT1;
  delete SUT2;
}

TEST(EntidadNombrada, given_twoEntidadWithDifferentEntity_when_esIgual_then_returnsFalse)
{
  std::string entidad1 = "Entidad1";
  std::string entidad2 = "Entidad2";
  int frecuencia = 10;

  EntidadNombrada* SUT1 = new EntidadNombrada(entidad1, frecuencia);
  EntidadNombrada* SUT2 = new EntidadNombrada(entidad2, frecuencia);
  EXPECT_FALSE(*SUT1 == *SUT2);
  delete SUT1;
  delete SUT2;
}


