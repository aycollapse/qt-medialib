#ifndef JSON_SAVE_VISITOR_H
#define JSON_SAVE_VISITOR_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/videogame.h"

class JsonSaveVisitor : public Visitor {
public:
    QJsonArray jsonArray;

    void visit(Book& book) override;
    void visit(Movie& movie) override;
    void visit(Videogame& game) override;
};

#endif // JSON_SAVE_VISITOR_H
