#ifndef EXTRACT_DETAILS_VISITOR
#define EXTRACT_DETAILS_VISITOR

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/videogame.h"

class ExtractDetailsVisitor : public Visitor {
public:
    explicit ExtractDetailsVisitor(QMap<QString, QString> &out);

    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Videogame &game) override;

private:
    QMap<QString, QString> &out;
};

#endif // EXTRACT_DETAILS_VISITOR