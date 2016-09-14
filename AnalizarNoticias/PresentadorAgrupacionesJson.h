#ifndef PRESENTADORAGRUPACIONESJSON_H_
#define PRESENTADORAGRUPACIONESJSON_H_

#include "PresentadorAgrupaciones.h"

#include "../Json/json.h"

class PresentadorAgrupacionesJson : public PresentadorAgrupaciones
{
public:
  PresentadorAgrupacionesJson (std::ostream & os);
  virtual ~PresentadorAgrupacionesJson ();

  void presentar (Analizador::agrupacionEntidadFrecuente agrupacion) override;
  void presentar (Analizador::agrupacionTematica agrupacion) override;

private:
  Json::Value presentarGrupo (Analizador::grupoNoticias agrupacion);
};


#endif /* PRESENTADORAGRUPACIONESJSON_H_ */
