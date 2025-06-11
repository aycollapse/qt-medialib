#ifndef ABSTRACT_MEDIA_H
#define ABSTRACT_MEDIA_H

#include <QString>
#include <QUuid>
#include <QDate>

class Visitor;

class AbstractMedia
{
public:
    AbstractMedia(
            const QString& name,
            float rating,
            const QString& genre,
            const QString& description,
            const QString& comment,
            const QDate& dateRelease,
            const QString& bannerPath);

    virtual ~AbstractMedia() = 0;
    virtual void accept(Visitor& visitor) = 0;

    //getters
    const QUuid& getId() const; //set with constructor
    const QString& getName() const;
    const float& getRating() const;
    const QString& getGenre() const;
    const QString& getDescription() const;
    const QString& getComment() const;
    const QDate& getDateRelease() const;
    const QDate& getDateAdded() const; //set with constructor
    const QString& getBannerPath() const;

    //setters
    void setName(const QString& name);
    void setRating(const float& rating);
    void setGenre(const QString& genre);
    void setDescription(const QString& description);
    void setComment(const QString& comment);
    void setDateRelease(const QDate& date);
    void setBannerPath(const QString& path);

protected:
    QUuid id;
    QString name;
    float rating;
    QString genre;
    QString description;
    QString comment;
    QDate dateReleased;
    QDate dateAdded;
    QString bannerPath;
};

#endif // ABSTRACT_MEDIA_H