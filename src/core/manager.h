#ifndef MANAGER_H
#define MANAGER_H

#include <QCoreApplication>
#include <QDir>

#include "models/abstract_media.h"

class Manager //singleton manager for all media
{   
public:
    Manager(const Manager&) = delete;
    ~Manager() = default;

    static Manager& getInstance();

    void saveData();
    void loadData();

    void addMedia(std::unique_ptr<AbstractMedia> media);
    void editMedia(std::unique_ptr<AbstractMedia> media);
    void removeMedia(const QUuid &id);

    AbstractMedia *getMedia(const QUuid &id) const;
    std::vector<std::unique_ptr<AbstractMedia>>& getMediaVector();

private:
    Manager(){}

    std::vector<std::unique_ptr<AbstractMedia>> mediaVector;

    QDir rootDir = QCoreApplication::applicationDirPath();
    QString dataPath = rootDir.filePath("data/data.json");
    QString imagesPath = rootDir.filePath("data/images");
};


#endif 