#ifndef ABSTRACT_MEDIA_H
#define ABSTRACT_MEDIA_H

#include <QString>
#include <QUuid>
#include <QDate>

class Visitor;

class AbstractMedia
{
public:
    AbstractMedia();
    virtual ~AbstractMedia() = 0;
    virtual void accept(Visitor& visitor) = 0;

    //getters
    const QUuid& getId() const; //set with constructor
    const QString& getName() const;
    const float& getRating() const;
    const QString getDescription() const;
    const QString getComment() const;
    const QDate& getDateRelease() const;
    const QDate& getDateAdded() const; //set with constructor

    //setters
    void setName(const QString& name);
    void setRating(const float& rating);
    void setDescription(const QString& description);
    void setComment(const QString& comment);
    void setDateRelease(const QDate& date);

protected:
    QUuid id;
    QString name;
    float rating;
    QString description;
    QString comment;
    QDate date_release;
    QDate date_added;
};

#endif // ABSTRACT_MEDIA_H