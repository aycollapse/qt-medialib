#include "abstract_media.h"

AbstractMedia::AbstractMedia() : id(QUuid::createUuid()) {}
AbstractMedia::~AbstractMedia() {}

// getters
const QUuid& AbstractMedia::getId() const {return id;}
const QString& AbstractMedia::getName() const {return name;}
const QDate& AbstractMedia::getDate() const {return date;}