#ifndef PRESENTADORAGRUPACIONESTXT_H_
#define PRESENTADORAGRUPACIONESTXT_H_

#include "PresentadorAgrupaciones.h"

class PresentadorAgrupacionesTxt : public PresentadorAgrupaciones
{

public:
  PresentadorAgrupacionesTxt (std::ostream & os);
  virtual ~PresentadorAgrupacionesTxt ();

  void presentar (Analizador::agrupacionEntidadFrecuente agrupacion) override;
  void presentar (Analizador::agrupacionTematica agrupacion) override;

};

#endif /* PRESENTADORAGRUPACIONESTXT_H_ */
