#ifndef EXTRACT_DETAILS_VISITOR
#define EXTRACT_DETAILS_VISITOR

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/videogame.h"

class ExtractDetailsVisitor : public Visitor {
public:
    explicit ExtractDetailsVisitor(QMap<QString, QString> &out) : out(out) {}

    void visit(Book &book) override {
        out["type"] = "book";
        out["name"] = book.getName();
        out["rating"] = QString::number(book.getRating());
        out["genre"] = book.getGenre();
        out["description"] = book.getDescription();
        out["comment"] = book.getComment();
        out["dateRelease"] = book.getDateRelease().toString("yyyy-MM-dd");
        out["bannerPath"] = book.getBannerPath();
        out["author"] = book.getAuthor();
        out["isbn"] = book.getISBN();
    }

    void visit(Movie &movie) override {
        out["type"] = "movie";
        out["name"] = movie.getName();
        out["rating"] = QString::number(movie.getRating());
        out["genre"] = movie.getGenre();
        out["description"] = movie.getDescription();
        out["comment"] = movie.getComment();
        out["dateRelease"] = movie.getDateRelease().toString("yyyy-MM-dd");
        out["bannerPath"] = movie.getBannerPath();
        out["director"] = movie.getDirector();
        out["language"] = movie.getLanguage();
        out["duration"] = movie.getDuration().toString("hh:mm:ss");
    }

    void visit(Videogame &game) override {
        out["type"] = "videogame";
        out["name"] = game.getName();
        out["rating"] = QString::number(game.getRating());
        out["genre"] = game.getGenre();
        out["description"] = game.getDescription();
        out["comment"] = game.getComment();
        out["dateRelease"] = game.getDateRelease().toString("yyyy-MM-dd");
        out["bannerPath"] = game.getBannerPath();
        out["gameDirector"] = game.getGameDirector();
        out["publisher"] = game.getPublisher();
        out["mode"] = game.getMode();
    }

private:
    QMap<QString, QString> &out;
};

#endif // EXTRACT_DETAILS_VISITOR