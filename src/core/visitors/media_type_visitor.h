#ifndef MEDIA_TYPE_VISITOR_H
#define MEDIA_TYPE_VISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/videogame.h"

class MediaTypeVisitor : public Visitor {
public:
    enum class MediaType {
        Book,
        Movie,
        Videogame
    };

    void visit(Book&) override { type = MediaType::Book; }
    void visit(Movie&) override { type = MediaType::Movie; }
    void visit(Videogame&) override { type = MediaType::Videogame; }

    MediaType getType() const { return type; }

private:
    MediaType type;
};

#endif // MEDIA_TYPE_VISITOR_H
