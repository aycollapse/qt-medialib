#ifndef BOOK_H
#define BOOK_H

#include "abstract_media.h"
#include "../visitors/visitor.h"
#include <QString>

class Book : public AbstractMedia {
public:
    Book(
        const QString& name = "Book",
        float rating = 0.0f,
        const QString& genre = "None",
        const QString& description = "None",
        const QString& comment = "None",
        const QDate& dateRelease = QDate(1900,1,1),
        const QString& author = "None",
        const QString& isbn = "0000000000000",
        const QString& bannerPath = "");

    ~Book() override = default;

    void accept(Visitor& visitor) override;

    // getters
    const QString& getAuthor() const;
    const QString& getISBN() const;
    
    // setters
    void setAuthor(const QString& author);
    void setISBN(const QString& isbn);

private:
    QString author;
    QString isbn; // Internation Standard Book Number (ISBN-13) without dashes (-)
};

#endif // BOOK_H