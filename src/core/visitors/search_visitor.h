#ifndef SEARCH_VISITOR_H
#define SEARCH_VISITOR_H

#include <QString>
#include <QStringList>
#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/videogame.h"

class SearchVisitor : public Visitor {
public:
    explicit SearchVisitor(const QString& text);

    void visit(Book& book) override;
    void visit(Movie& movie) override;
    void visit(Videogame& game) override;

    bool isMatch() const;

private:
    bool checkCommonFields(AbstractMedia& media);

    QString searchText;
    bool matches;
};

#endif // SEARCH_VISITOR_H
