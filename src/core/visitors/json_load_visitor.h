#ifndef JSON_LOAD_VISITOR_H
#define JSON_LOAD_VISITOR_H

#include <QJsonArray>
#include <QJsonObject>
#include <QDate>
#include <QTime>
#include <memory>
#include <vector>

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/videogame.h"

class JsonLoadVisitor : public Visitor {
public:
    std::vector<std::unique_ptr<AbstractMedia>> loadedMedia;

    void loadFromJsonArray(const QJsonArray &array);

    void visit(Book& book) override;
    void visit(Movie& movie) override;
    void visit(Videogame& game) override;

private:
    QJsonObject currentObj;
};

#endif // JSON_LOAD_VISITOR_H
