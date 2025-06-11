#include "movie.h"

Movie::Movie(
        const QString& name,
        float rating,
        const QString& genre,
        const QString& description,
        const QString& comment,
        const QDate& dateReleased, 
        const QString& director,
        const QString& language,
        const QTime& duration,
        const QString& bannerPath) 

        : AbstractMedia(name,rating,genre,description,comment,dateReleased,bannerPath), 
        director(director), 
        language(language),
        duration(duration) {}

void Movie::accept(Visitor& visitor) {visitor.visit(*this);}

// getters
const QString& Movie::getDirector() const {return director;}
const QString& Movie::getLanguage() const {return language;}
const QTime& Movie::getDuration() const {return duration;}

// setters
void Movie::setDirector(const QString& director) {this->director = director;}
void Movie::setLanguage(const QString& language) {this->language = language;}
void Movie::setDuration(const QTime& duration) {this->duration = duration;}
