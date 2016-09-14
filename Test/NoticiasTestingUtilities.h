#ifndef NOTICIASTESTINGUTILITIES_H_
#define NOTICIASTESTINGUTILITIES_H_

#include "Articulo.h"
#include "Tuit.h"
#include "gmock/gmock.h"


using namespace ::testing;


// ostream operations to ease testing error outputs
std::ostream& operator<<(std::ostream& os, const Noticia* noticia);
std::ostream& operator<<(std::ostream& os, const Tuit* tuit);
std::ostream& operator<<(std::ostream& os, const Articulo* articulo);

//SUT creation automation
Articulo* crearArticulo(std::string titulo, std::string cuerpo, std::string file);
Articulo* crearArticulo(std::string titulo, std::string cuerpo);
Tuit* crearTuit(int id, std::string user, std::string cuerpo, std::string file);
Tuit* crearTuit(int id, std::string user, std::string cuerpo);


//Matchers


/* Have to hack a little because dynamic_cast on nested macros gave errors */
struct ArticuloCaster {
    template <typename F>
    static Articulo* cast(F* from) {
        return dynamic_cast<Articulo*>(from);
    }
};

struct TuitCaster {
    template <typename F>
    static Tuit* cast(F* from) {
        return dynamic_cast<Tuit*>(from);
    }
};

//Checks the Summary of a Noticia
MATCHER_P(NoticiaSummary, summary,
    std::string("news summary ") + (negation ? "is not " : "is ") + PrintToString(summary))
{ return Matches(Eq(summary))(arg->getSummary()); }

//Checks the body of a Noticia
MATCHER_P(NoticiaBody, body,
    std::string("body ") + (negation ? "is not " : "is ") + PrintToString(body))
{ return Matches(Eq(body))(arg->getCuerpo()); }

//Checks the title of an Articulo
MATCHER_P(ArticuloTitle, title,
    std::string("título ") + (negation ? "is not " : "is ") + PrintToString(title))
{ return Matches(Eq(title))(ArticuloCaster::cast(arg)->getTitulo()); }

//Checks the complete fields of an Articulo (except entities)
MATCHER_P(MatchArticulo, articulo,
    std::string("articulo ") + (negation ? "is not " : "is ") + PrintToString(articulo))
{ return Matches(AllOf(ArticuloTitle(articulo->getTitulo()), NoticiaBody(articulo->getCuerpo())))(ArticuloCaster::cast(arg)); }

//Checks the ID of a Tuit
MATCHER_P(TuitId, id,
    std::string("ID ") + (negation ? "is not " : "is ") + PrintToString(id))
{ return Matches(Eq(id))(TuitCaster::cast(arg)->getId()); }

//Checks the user of a Tuit
MATCHER_P(TuitUser, user,
    std::string("user ") + (negation ? "is not " : "is ") + PrintToString(user))
{ return Matches(Eq(user))(TuitCaster::cast(arg)->getUser()); }

//Checks the complete fields of a Tuit (except entities)
MATCHER_P(MatchTuit, tuit,
    std::string("tuit ") + (negation ? "is not " : "is ") + PrintToString(tuit))
{ return Matches(AllOf(TuitId(tuit->getId()), TuitUser(tuit->getUser()), NoticiaBody(tuit->getCuerpo())))(TuitCaster::cast(arg)); }

//Checks the entity name
MATCHER_P(EntityName, name,
    std::string("entity name ") + (negation ? "is not " : "is ") + PrintToString(name))
{ return Matches(Eq(name))(arg.getEntidadNombrada()); }

//Checks the entity frequency
MATCHER_P(EntityFrequency, freq,
    std::string("entity frequency ") + (negation ? "is not " : "is ") + PrintToString(freq))
{ return Matches(Eq(freq))(arg.getFrecuencia()); }

//Checks the complete entity: name and frequency
MATCHER_P(MatchEntity, entity,
    std::string("entity ") + (negation ? "is not " : "is ") + PrintToString(entity))
{ return Matches(AllOf(EntityName(entity.getEntidadNombrada()), EntityFrequency(entity.getFrecuencia())))(arg); }


#endif //NOTICIASTESTINGUTILITIES_H_


