#include "create_media_visitor.h"

CreateItemVisitor::CreateItemVisitor(const QMap<QString, QString> &params) : params(params) {
    QString type = params["type"].toLower();
    if (type == "book") {
        Book dummy;
        dummy.accept(*this);
    } else if (type == "movie") {
        Movie dummy;
        dummy.accept(*this);
    } else if (type == "videogame") {
        Videogame dummy;
        dummy.accept(*this);
    }
}

void CreateItemVisitor::visit(Book &)
{
    created = std::make_unique<Book>(
        QUuid(params["id"]),
        params["name"],
        params["rating"].toFloat(),
        params["genre"],
        params["description"],
        params["comment"],
        QDate::fromString(params["dateRelease"], "yyyy-MM-dd"),
        params["author"],
        params["isbn"],
        params["bannerPath"]
    );
}

void CreateItemVisitor::visit(Movie &)
{
    created = std::make_unique<Movie>(
        QUuid(params["id"]),
        params["name"],
        params["rating"].toFloat(),
        params["genre"],
        params["description"],
        params["comment"],
        QDate::fromString(params["dateRelease"], "yyyy-MM-dd"),
        params["director"],
        params["language"],
        QTime::fromString(params["duration"], "hh:mm:ss"),
        params["bannerPath"]
    );
}

void CreateItemVisitor::visit(Videogame &)
{
    created = std::make_unique<Videogame>(
        QUuid(params["id"]),
        params["name"],
        params["rating"].toFloat(),
        params["genre"],
        params["description"],
        params["comment"],
        QDate::fromString(params["dateRelease"], "yyyy-MM-dd"),
        params["gameDirector"],
        params["publisher"],
        params["mode"],
        params["bannerPath"]
    );
}

std::unique_ptr<AbstractMedia> CreateItemVisitor::takeItem() { return std::move(created); }
