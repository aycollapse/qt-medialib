#ifndef CREATE_MEDIA_VISITOR
#define CREATE_MEDIA_VISITOR

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/videogame.h"

class CreateItemVisitor : public Visitor {
public:
    explicit CreateItemVisitor(const QMap<QString, QString> &params);

    void visit(Book &) override;
    void visit(Movie &) override;
    void visit(Videogame &) override;

    std::unique_ptr<AbstractMedia> takeItem();

private:
    QMap<QString, QString> params;
    std::unique_ptr<AbstractMedia> created;
};

#endif // CREATE_MEDIA_VISITOR