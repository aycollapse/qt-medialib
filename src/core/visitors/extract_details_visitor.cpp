#include "extract_details_visitor.h"

ExtractDetailsVisitor::ExtractDetailsVisitor(QMap<QString, QString> &out) : out(out) {}

void ExtractDetailsVisitor::visit(Book &book) {
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

void ExtractDetailsVisitor::visit(Movie &movie) {
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

void ExtractDetailsVisitor::visit(Videogame &game) {
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
