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

    void visit(Book& book) override 
    {
        QJsonObject obj;
        obj["id"] = book.getId().toString();
        obj["type"] = "book";
        obj["name"] = book.getName();
        obj["rating"] = book.getRating();
        obj["genre"] = book.getGenre();
        obj["description"] = book.getDescription();
        obj["comment"] = book.getComment();
        obj["dateRelease"] = book.getDateRelease().year();
        obj["author"] = book.getAuthor();
        obj["isbn"] = book.getISBN();
        obj["bannerPath"] = book.getBannerPath();
        jsonArray.append(obj);
    }

    void visit(Movie& movie) override 
    {
        QJsonObject obj;
        obj["id"] = movie.getId().toString();
        obj["type"] = "movie";
        obj["name"] = movie.getName();
        obj["rating"] = movie.getRating();
        obj["genre"] = movie.getGenre();
        obj["description"] = movie.getDescription();
        obj["comment"] = movie.getComment();
        obj["dateRelease"] = movie.getDateRelease().year();
        obj["director"] = movie.getDirector();
        obj["language"] = movie.getLanguage();
        obj["duration"] = movie.getDuration().toString("hh:mm:ss");
        obj["bannerPath"] = movie.getBannerPath();
        jsonArray.append(obj);
    }

    void visit(Videogame& game) override 
    {
        QJsonObject obj;
        obj["id"] = game.getId().toString();
        obj["type"] = "videogame";
        obj["name"] = game.getName();
        obj["rating"] = game.getRating();
        obj["genre"] = game.getGenre();
        obj["description"] = game.getDescription();
        obj["comment"] = game.getComment();
        obj["dateRelease"] = game.getDateRelease().year();
        obj["gameDirector"] = game.getGameDirector();
        obj["publisher"] = game.getPublisher();
        obj["mode"] = game.getMode();
        obj["bannerPath"] = game.getBannerPath();
        jsonArray.append(obj);
    }
};

#endif // JSON_SAVE_VISITOR_H
