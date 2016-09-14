#ifndef NOTICIAVISITOR_H_
#define NOTICIAVISITOR_H_

class Articulo;
class Tuit;

class NoticiaVisitor {

public:
  NoticiaVisitor() {}
  virtual ~NoticiaVisitor() {}

  virtual void visit( Articulo *articulo) = 0;
  virtual void visit( Tuit *tuit) = 0;
};

#endif /* NOTICIAVISITOR_H_ */
