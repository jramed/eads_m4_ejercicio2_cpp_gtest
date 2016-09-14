#ifndef TUIT_H_
#define TUIT_H_

#include "Noticia.h"

class Tuit : public Noticia
{
private:
  int id;
  std::string user;

public:
  Tuit ();
  Tuit(int id, std::string user, std::string cuerpo, std::shared_ptr<PalabrasReservadas> palabrasReservadas);
  virtual ~Tuit ();

  void accept(NoticiaVisitor* visitor) override;
  std::string getSummary() const override;
  std::string toString() const override;

  int getId() const;
  std::string getUser() const;




};

#endif /* TUIT_H_ */
