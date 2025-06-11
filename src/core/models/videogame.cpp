#include "videogame.h"

Videogame::Videogame(
    const QString& name,
    float rating,
    const QString& genre,
    const QString& description,
    const QString& comment,
    const QDate& dateRelease,
    const QString& gameDirector,
    const QString& publisher,
    const QString& mode,
    const QString& bannerPath)
    : AbstractMedia(name, rating, genre, description, comment, dateRelease, bannerPath),
      gameDirector(gameDirector),
      publisher(publisher),
      mode(mode) {}

void Videogame::accept(Visitor& visitor) {
    visitor.visit(*this);
}

// Getters
const QString& Videogame::getGameDirector() const { return gameDirector; }
const QString& Videogame::getPublisher() const { return publisher; }
const QString& Videogame::getMode() const { return mode; }

// Setters
void Videogame::setGameDirector(const QString& director) { this->gameDirector = director; }
void Videogame::setPublisher(const QString& publisher) { this->publisher = publisher; }
void Videogame::setMode(const QString& mode) { this->mode = mode; }
