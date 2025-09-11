#include "json_load_visitor.h"
#include <QJsonObject>

void JsonLoadVisitor::loadFromJsonArray(const QJsonArray &array)
{
    for (const auto &value : array) 
    {
        if (!value.isObject()) continue;
        currentObj = value.toObject();

        QString type = currentObj["type"].toString().toLower();

        if (type == "book") 
        {
            Book book;
            book.accept(*this);
        }
        else if (type == "movie") 
        {
            Movie movie; 
            movie.accept(*this);
        }
        else if (type == "videogame") 
        {
            Videogame game;
            game.accept(*this);
        }
    }
}

void JsonLoadVisitor::visit(Book &)
{
    QDate dateRelease = QDate::fromString(currentObj.value("dateRelease").toString(), "yyyy-MM-dd");
    if (!dateRelease.isValid()) dateRelease = QDate(1900,1,1);

    loadedMedia.push_back(std::make_unique<Book>(
        QUuid(currentObj["id"].toString()),
        currentObj["name"].toString(),
        static_cast<float>(currentObj["rating"].toDouble()),
        currentObj["genre"].toString(),
        currentObj["description"].toString(),
        currentObj["comment"].toString(),
        dateRelease,
        currentObj["author"].toString(),
        currentObj["isbn"].toString(),
        currentObj["bannerPath"].toString()
    ));
}

void JsonLoadVisitor::visit(Movie &)
{
    QDate dateRelease = QDate::fromString(currentObj.value("dateRelease").toString(), "yyyy-MM-dd");
    if (!dateRelease.isValid()) dateRelease = QDate(1900,1,1);

    loadedMedia.push_back(std::make_unique<Movie>(
        QUuid(currentObj["id"].toString()),
        currentObj["name"].toString(),
        static_cast<float>(currentObj["rating"].toDouble()),
        currentObj["genre"].toString(),
        currentObj["description"].toString(),
        currentObj["comment"].toString(),
        dateRelease,
        currentObj["director"].toString(),
        currentObj["language"].toString(),
        QTime::fromString(currentObj["duration"].toString(), "hh:mm:ss"),
        currentObj["bannerPath"].toString()
    ));
}

void JsonLoadVisitor::visit(Videogame &)
{
    QDate dateRelease = QDate::fromString(currentObj.value("dateRelease").toString(), "yyyy-MM-dd");
    if (!dateRelease.isValid()) dateRelease = QDate(1900,1,1);

    loadedMedia.push_back(std::make_unique<Videogame>(
        QUuid(currentObj["id"].toString()),
        currentObj["name"].toString(),
        static_cast<float>(currentObj["rating"].toDouble()),
        currentObj["genre"].toString(),
        currentObj["description"].toString(),
        currentObj["comment"].toString(),
        dateRelease,
        currentObj["gameDirector"].toString(),
        currentObj["publisher"].toString(),
        currentObj["mode"].toString(),
        currentObj["bannerPath"].toString()
    ));
}
