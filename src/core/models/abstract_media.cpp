#include "abstract_media.h"

AbstractMedia::AbstractMedia() : id(QUuid::createUuid()), date_added(QDate::currentDate()) {}
AbstractMedia::~AbstractMedia() {}

// getters
const QUuid& AbstractMedia::getId() const {return id;}
const QString& AbstractMedia::getName() const {return name;}
const float& AbstractMedia::getRating() const {return rating;}
const QString AbstractMedia::getDescription() const {return description;}
const QString AbstractMedia::getComment() const {return comment;}
const QDate& AbstractMedia::getDateRelease() const {return date_release;}
const QDate& AbstractMedia::getDateAdded() const {return date_added;}

//setters
void AbstractMedia::setName(const QString& name){this->name = name;}
void AbstractMedia::setRating(const float& rating){this->rating = rating;}
void AbstractMedia::setDescription(const QString& description){this->description = description;}
void AbstractMedia::setComment(const QString& comment){this->comment = comment;}
void AbstractMedia::setDateRelease(const QDate& date){this->date_release = date;}