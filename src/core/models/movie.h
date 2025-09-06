#ifndef MOVIE_H
#define MOVIE_H


#include "abstract_media.h"
#include "../visitors/visitor.h"
#include <QString>

class Movie : public AbstractMedia {
public:
    Movie(
        const QString& name = "Movie",
        float rating = 0.0f,
        const QString& genre = "None",
        const QString& description = "None",
        const QString& comment = "None",
        const QDate& dateRelease = QDate(1900,1,1),
        const QString& director = "Unknown",
        const QString& language = "None",
        const QTime& duration = QTime(0, 0),
        const QString& bannerPath = "");

    Movie(
        const QUuid& id,
        const QString& name = "Movie",
        float rating = 0.0f,
        const QString& genre = "None",
        const QString& description = "None",
        const QString& comment = "None",
        const QDate& dateRelease = QDate(1900,1,1),
        const QString& director = "Unknown",
        const QString& language = "None",
        const QTime& duration = QTime(0, 0),
        const QString& bannerPath = "");

    ~Movie() override = default;

    void accept(Visitor& visitor) override;

    // getters
    const QString& getDirector() const;
    const QString& getLanguage() const;
    const QTime& getDuration() const;

    // setters
    void setDirector(const QString& director);
    void setLanguage(const QString& language);
    void setDuration(const QTime& duration);

private:
    QString director;
    QString language;
    QTime duration;
};

#endif // MOVIE_H