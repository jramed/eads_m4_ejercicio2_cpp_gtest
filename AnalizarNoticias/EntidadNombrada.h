/*
 * EntidadNombrada.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef ENTIDADNOMBRADA_H_
#define ENTIDADNOMBRADA_H_
#include <string>

class EntidadNombrada {

  int frecuencia;
  std::string entidadNombrada;

public:

  EntidadNombrada();
  EntidadNombrada( std::string n, int f);
  int getFrecuencia() const;
  std::string getEntidadNombrada() const;
  void setFrecuencia(int const f);
  void setEntidadNombrada(std::string const& en);
  std::string toString() const;
};

inline bool operator< (const EntidadNombrada& lhs, const EntidadNombrada& rhs){
  if (lhs.getEntidadNombrada().compare(rhs.getEntidadNombrada()) < 0)
    return true;
  else
    return false;
}

inline bool operator== (const EntidadNombrada& lhs, const EntidadNombrada& rhs){
  if (lhs.getEntidadNombrada().compare(rhs.getEntidadNombrada()) == 0)
    return true;
  else
    return false;
}

bool compararEntidadesNombradas(const EntidadNombrada &lhs, const EntidadNombrada &rhs);
bool compararPorMasFrecuenteMayorMenor(const EntidadNombrada &lhs, const EntidadNombrada &rhs );
#endif /* ENTIDADNOMBRADA_H_ */
