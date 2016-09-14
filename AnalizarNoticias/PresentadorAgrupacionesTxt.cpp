#include "PresentadorAgrupacionesTxt.h"

PresentadorAgrupacionesTxt::PresentadorAgrupacionesTxt (std::ostream & os)
: PresentadorAgrupaciones(os)
{
}

PresentadorAgrupacionesTxt::~PresentadorAgrupacionesTxt ()
{
}

void PresentadorAgrupacionesTxt::presentar (Analizador::agrupacionEntidadFrecuente agrupacion)
{
  for (auto grupo : agrupacion) {
    os << "\n" << grupo.first << "\n";
    for (auto &noticia : grupo.second) {
      os << "*[" << noticia->getSummary() << "]\n";
    }
  }
}

void PresentadorAgrupacionesTxt::presentar (Analizador::agrupacionTematica agrupacion)
{
  for (auto grupo : agrupacion) {
    os << "[" << (*grupo.begin())->getSummary() << "]\n";
    auto it = grupo.begin();
    for (++it; it != grupo.end(); ++it) {
      os << "   *[" << (*it)->getSummary() << "]\n";
    }
    os << "\n";
  }
}

