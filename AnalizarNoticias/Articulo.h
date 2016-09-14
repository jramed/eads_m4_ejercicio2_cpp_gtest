#ifndef ARTICULO_H_
#define ARTICULO_H_

#include <Noticia.h>

class Articulo : public Noticia
{

  std::string titulo;

public:
  Articulo ();
  Articulo(std::string titulo, std::string cuerpo, std::shared_ptr<PalabrasReservadas> palabrasReservadas);
  virtual ~Articulo ();

  void accept(NoticiaVisitor* visitor)  override;
  std::string getSummary() const override;
  std::string toString() const override;

  std::string getTitulo()const;
};

inline bool operator< (const Articulo& lhs, const Articulo& rhs){
  if (lhs.getTitulo().compare(rhs.getTitulo()) < 0)
    return true;
  else return false;
}

inline bool operator== (const Articulo& lhs, const Articulo& rhs){
  if (lhs.getTitulo().compare(rhs.getTitulo()) == 0)
    return true;
  else return false;
}

#endif /* ARTICULO_H_ */
