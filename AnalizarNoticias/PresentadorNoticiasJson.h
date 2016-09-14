#ifndef PRESENTADORNOTICIASJSON_H_
#define PRESENTADORNOTICIASJSON_H_

#include "NoticiaVisitor.h"

#include "../Json/json.h"

class Noticia;
class PresentadorNoticiasJson : public NoticiaVisitor
{
private:
  Json::Value resultado;

public:
  PresentadorNoticiasJson (Noticia* noticia);
  virtual ~PresentadorNoticiasJson ();

  void visit( Articulo *articulo) override;
  void visit( Tuit *tuit) override;

  Json::Value operator()();

};

#endif /* PRESENTADORNOTICIASJSON_H_ */
