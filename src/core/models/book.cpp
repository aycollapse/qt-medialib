#include "book.h"

Book::Book(const QString& name,float rating,const QString& description,const QString& comment,
        const QDate& dateReleased, const QString& author, const QString& isbn, const QString& bannerPath) 

        : AbstractMedia(name,rating,description,comment,dateReleased,bannerPath), 
        author(author), 
        isbn(isbn) {}

void Book::accept(Visitor& visitor) {visitor.visit(*this);}

// getters
const QString& Book::getAuthor() const {return author;}
const QString& Book::getISBN() const {return isbn;}

// setters
void Book::setAuthor(const QString& author) {this->author = author;}
void Book::setISBN(const QString& isbn) {this->isbn = isbn;}
