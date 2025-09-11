#ifndef MANAGER_H
#define MANAGER_H

#include <QCoreApplication>
#include <QDir>
#include <QJsonDocument>
#include <memory>
#include <vector>

#include "abstract_media.h"

class Manager // singleton manager for all media
{   
public:
    Manager(const Manager&) = delete;
    ~Manager() = default;

    static Manager& getInstance();

    bool saveData();
    bool loadData();

    bool addMedia(std::unique_ptr<AbstractMedia> media);
    bool editMedia(const QUuid &id, const QMap<QString, QString> &changes);
    bool deleteMedia(const QUuid &id);

    void setDefaultData(QString dataFolderPath);
    QString getDefaultData(){return dataFolder.absolutePath();}

    AbstractMedia *getMedia(const QUuid &id) const;
    std::vector<std::unique_ptr<AbstractMedia>>& getMediaVector();

    bool exportData(const QString &destinationPath) const;
    bool importData(const QString &sourcePath);

private:
    Manager();

    bool copyDirectoryRecursively(const QDir &src, const QDir &dst) const;
    bool validateDataFolder(const QDir &dir, QString *errorOut = nullptr) const;

    std::vector<std::unique_ptr<AbstractMedia>> mediaVector;

    QDir dataFolder;
    QString userData;
    QString imagesPath;
};

#endif // MANAGER_H
