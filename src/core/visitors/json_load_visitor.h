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

class JsonLoadVisitor {
public:
    std::vector<std::unique_ptr<AbstractMedia>> loadedMedia;

    void loadFromJsonArray(const QJsonArray &array) 
    {
        for (const auto &value : array) 
        {
            if (!value.isObject()) continue;
            QJsonObject obj = value.toObject();

            QString type = obj["type"].toString();

            if (type == "book") 
            {
                loadedMedia.push_back(std::make_unique<Book>(
                    obj["name"].toString(),
                    obj["rating"].toDouble(),
                    obj["genre"].toString(),
                    obj["description"].toString(),
                    obj["comment"].toString(),
                    QDate(obj["dateRelease"].toInt(), 1, 1),
                    obj["author"].toString(),
                    obj["isbn"].toString(),
                    obj["bannerPath"].toString()
                ));
            }
            else if (type == "movie") 
            {
                loadedMedia.push_back(std::make_unique<Movie>(
                    obj["name"].toString(),
                    static_cast<float>(obj["rating"].toDouble()),
                    obj["genre"].toString(),
                    obj["description"].toString(),
                    obj["comment"].toString(),
                    QDate(obj["dateRelease"].toInt(), 1, 1),
                    obj["director"].toString(),
                    obj["language"].toString(),
                    QTime::fromString(obj["duration"].toString(), "hh:mm:ss"),
                    obj["bannerPath"].toString()
                ));
            }
            else if (type == "videogame") 
            {
                loadedMedia.push_back(std::make_unique<Videogame>(
                    obj["name"].toString(),
                    static_cast<float>(obj["rating"].toDouble()),
                    obj["genre"].toString(),
                    obj["description"].toString(),
                    obj["comment"].toString(),
                    QDate(obj["dateRelease"].toInt(), 1, 1),
                    obj["gameDirector"].toString(),
                    obj["publisher"].toString(),
                    obj["mode"].toString(),
                    obj["bannerPath"].toString()
                ));
            }
        }
    }
};

#endif // JSON_LOAD_VISITOR_H
