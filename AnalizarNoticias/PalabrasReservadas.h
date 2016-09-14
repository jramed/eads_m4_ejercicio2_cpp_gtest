/*
 * PalabrasReservadas.h
 *
 *  Created on: 4 de ago. de 2016
 *      Author: ECERAMM
 */

#ifndef PALABRASRESERVADAS_H_
#define PALABRASRESERVADAS_H_

#include <map>
#include <string>
#include <list>

class PalabrasReservadas {
  std::map<std::string, std::list<std::string>> palabrasReservadas;
public:
  PalabrasReservadas(std::string &ruta);
  std::list<std::string> getPalabrasReservadas(std::string &idioma)const;
  bool contienePalabra(std::string &palabra, std::string &idioma) const;

private:
  void setPalabrasReservadas(std::string &ruta);

public:
  static std::string nombreFicheroRestricciones;
  static std::string idioma;
};

#endif /* PALABRASRESERVADAS_H_ */
