/*
 * utilidades.h
 *
 *  Created on: 11 de ago. de 2016
 *      Author: ECERAMM
 */

#ifndef UTILIDADES_H_
#define UTILIDADES_H_

#include <vector>
#include <string>

namespace utilidades {
  static constexpr const char *localeSpanish = "es_ES.iso88591";
  static constexpr const char *spanishNewsFileNameFormat = "newC[0-9]{5}_[0-9]{3}\\.ES\\.(txt|json)";

  bool esMayuscula(char c);
  std::vector<std::string> splitTextInWords(const std::string &text);
  std::string removePuctuationFromText(const std::string &text);

  std::vector<std::string> obtenerNombreFicherosDesdeDirectorio(std::string &pathNews);
  bool isFormatoNombreFicheroCorrecto(std::string &fileName);
}



#endif /* UTILIDADES_H_ */
