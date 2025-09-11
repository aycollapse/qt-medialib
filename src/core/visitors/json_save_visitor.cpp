#include "json_save_visitor.h"

void JsonSaveVisitor::visit(Book& book) {
    QJsonObject obj;
    obj["id"] = book.getId().toString();
    obj["type"] = "book";
    obj["name"] = book.getName();
    obj["rating"] = book.getRating();
    obj["genre"] = book.getGenre();
    obj["description"] = book.getDescription();
    obj["comment"] = book.getComment();
    obj["dateRelease"] = book.getDateRelease().toString("yyyy-MM-dd");
    obj["author"] = book.getAuthor();
    obj["isbn"] = book.getISBN();
    obj["bannerPath"] = book.getBannerPath();
    jsonArray.append(obj);
}

void JsonSaveVisitor::visit(Movie& movie) {
    QJsonObject obj;
    obj["id"] = movie.getId().toString();
    obj["type"] = "movie";
    obj["name"] = movie.getName();
    obj["rating"] = movie.getRating();
    obj["genre"] = movie.getGenre();
    obj["description"] = movie.getDescription();
    obj["comment"] = movie.getComment();
    obj["dateRelease"] = movie.getDateRelease().toString("yyyy-MM-dd");
    obj["director"] = movie.getDirector();
    obj["language"] = movie.getLanguage();
    obj["duration"] = movie.getDuration().toString("hh:mm:ss");
    obj["bannerPath"] = movie.getBannerPath();
    jsonArray.append(obj);
}

void JsonSaveVisitor::visit(Videogame& game) {
    QJsonObject obj;
    obj["id"] = game.getId().toString();
    obj["type"] = "videogame";
    obj["name"] = game.getName();
    obj["rating"] = game.getRating();
    obj["genre"] = game.getGenre();
    obj["description"] = game.getDescription();
    obj["comment"] = game.getComment();
    obj["dateRelease"] = game.getDateRelease().toString("yyyy-MM-dd");
    obj["gameDirector"] = game.getGameDirector();
    obj["publisher"] = game.getPublisher();
    obj["mode"] = game.getMode();
    obj["bannerPath"] = game.getBannerPath();
    jsonArray.append(obj);
}
