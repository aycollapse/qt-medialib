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
    const QUuid& getId() const;
    const QString& getName() const;
    const QDate& getDate() const;

protected:
    QUuid id;
    QString name;
    QDate date;
};

#endif // ABSTRACT_MEDIA_H