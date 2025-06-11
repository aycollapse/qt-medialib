#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include "abstract_media.h"
#include "../visitors/visitor.h"
#include <QString>

class Videogame : public AbstractMedia {
public:
    Videogame(
        const QString& name = "Videogame",
        float rating = 0.0f,
        const QString& genre = "None",
        const QString& description = "None",
        const QString& comment = "None",
        const QDate& dateRelease = QDate(1900, 1, 1),
        const QString& gameDirector = "Unknown",
        const QString& publisher = "Unknown",
        const QString& mode = "None",
        const QString& bannerPath = "");

    ~Videogame() override = default;

    void accept(Visitor& visitor) override;

    // getters
    const QString& getGameDirector() const;
    const QString& getPublisher() const;
    const QString& getMode() const;

    // setters
    void setGameDirector(const QString& director);
    void setPublisher(const QString& publisher);
    void setMode(const QString& mode);

private:
    QString gameDirector;
    QString publisher;
    QString mode; // single-player, co-op, multiplayer
};

#endif // VIDEOGAME_H
