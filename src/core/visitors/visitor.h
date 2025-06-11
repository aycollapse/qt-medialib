#ifndef VISITOR_H
#define VISITOR_H

class Book;
class Game;
class Movie;

class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visit(Book &book) = 0;
    virtual void visit(Game &game) = 0;
    virtual void visit(Movie &movie) = 0;
};


#endif // VISITOR_H