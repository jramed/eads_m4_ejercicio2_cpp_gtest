#ifndef PRESENTADORAGRUPACIONES_H_
#define PRESENTADORAGRUPACIONES_H_

#include "Analizador.h"
#include <ostream>

class PresentadorAgrupaciones
{
protected:
  std::ostream& os;

public:
  inline PresentadorAgrupaciones (std::ostream & os)
  : os(os)
  {}
  inline virtual ~PresentadorAgrupaciones () {}

  virtual void presentar (Analizador::agrupacionEntidadFrecuente agrupacion) = 0;
  virtual void presentar (Analizador::agrupacionTematica agrupacion) = 0;

};

#endif /* PRESENTADORAGRUPACIONES_H_ */
