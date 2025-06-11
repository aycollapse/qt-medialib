#ifndef VISITOR_H
#define VISITOR_H

class Book;
class Videogame;
class Movie;

class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visit(Book &book) = 0;
    virtual void visit(Videogame &Videogame) = 0;
    virtual void visit(Movie &movie) = 0;
};


#endif // VISITOR_H