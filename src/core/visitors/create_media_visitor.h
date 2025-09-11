#ifndef CREATE_MEDIA_VISITOR
#define CREATE_MEDIA_VISITOR

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/videogame.h"

class CreateItemVisitor : public Visitor {
public:
    explicit CreateItemVisitor(const QMap<QString, QString> &params) : params(params) {
        //create the appropriate media type based on the type field
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

    void visit(Book &) override {
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

    void visit(Movie &) override {
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

    void visit(Videogame &) override {
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

    std::unique_ptr<AbstractMedia> takeItem() { return std::move(created); }

private:
    QMap<QString, QString> params;
    std::unique_ptr<AbstractMedia> created;
};


#endif // CREATE_MEDIA_VISITOR