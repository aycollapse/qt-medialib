#include "abstract_media.h"

AbstractMedia::AbstractMedia(const QString& name,float rating,const QString& genre,const QString& description,
    const QString& comment,const QDate& dateReleased,const QString& bannerPath)
        
        : id(QUuid::createUuid()),
        name(name),
        rating(rating),
        genre(genre),
        description(description),
        comment(comment),
        dateReleased(dateReleased),
        dateAdded(QDate::currentDate()),
        bannerPath(bannerPath){}

AbstractMedia::~AbstractMedia() {}

// getters
const QUuid& AbstractMedia::getId() const {return id;}
const QString& AbstractMedia::getName() const {return name;}
const float& AbstractMedia::getRating() const {return rating;}
const QString& AbstractMedia::getGenre() const {return genre;}
const QString& AbstractMedia::getDescription() const {return description;}
const QString& AbstractMedia::getComment() const {return comment;}
const QDate& AbstractMedia::getDateRelease() const {return dateReleased;}
const QDate& AbstractMedia::getDateAdded() const {return dateAdded;}
const QString& AbstractMedia::getBannerPath() const {return bannerPath;}

//setters
void AbstractMedia::setName(const QString& name){this->name = name;}
void AbstractMedia::setRating(const float& rating){this->rating = rating;}
void AbstractMedia::setGenre(const QString& genre){this->genre = genre;}
void AbstractMedia::setDescription(const QString& description){this->description = description;}
void AbstractMedia::setComment(const QString& comment){this->comment = comment;}
void AbstractMedia::setDateRelease(const QDate& date){dateReleased = date;}
void AbstractMedia::setBannerPath(const QString& path){bannerPath = path;}