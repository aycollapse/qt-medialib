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
    explicit SearchVisitor(const QString& searchText) 
        : searchText(searchText.toLower()), matches(false) {}

    void visit(Book& book) override {
        matches = checkCommonFields(book) ||
                 book.getAuthor().toLower().contains(searchText) ||
                 book.getISBN().toLower().contains(searchText);
    }

    void visit(Movie& movie) override {
        matches = checkCommonFields(movie) ||
                 movie.getDirector().toLower().contains(searchText) ||
                 movie.getLanguage().toLower().contains(searchText);
    }

    void visit(Videogame& game) override {
        matches = checkCommonFields(game) ||
                 game.getGameDirector().toLower().contains(searchText) ||
                 game.getPublisher().toLower().contains(searchText) ||
                 game.getMode().toLower().contains(searchText);
    }

    bool isMatch() const { return matches; }

private:
    bool checkCommonFields(AbstractMedia& media) {
        return media.getName().toLower().contains(searchText) ||
               media.getGenre().toLower().contains(searchText) ||
               media.getDescription().toLower().contains(searchText) ||
               media.getComment().toLower().contains(searchText);
    }

    QString searchText;
    bool matches;
};

#endif // SEARCH_VISITOR_H
