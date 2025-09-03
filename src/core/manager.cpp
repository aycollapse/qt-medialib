#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <QStandardPaths>
#include <QDebug>

#include "visitors/json_save_visitor.h"
#include "visitors/json_load_visitor.h"
#include "manager.h"

Manager& Manager::getInstance()
{
    static Manager managerInstance;
    return managerInstance;
}

Manager::Manager()
{
    // ~/.config/medialib/data on Linux
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    setDefaultData(QDir(configDir).filePath("data"));
    Manager::loadData();
}

void Manager::setDefaultData(QString dataFolderPath)
{
    dataFolder = QDir(dataFolderPath);
    if (!dataFolder.exists()) 
    {
        dataFolder.mkpath(".");
    }
    imagesPath = dataFolder.filePath("images");
    if (!QDir(imagesPath).exists()) 
    {
        QDir().mkpath(imagesPath);
    }
    userData = dataFolder.filePath("data.json");
}

void Manager::addMedia(std::unique_ptr<AbstractMedia> media) 
{
    mediaVector.push_back(std::move(media));
    qDebug() << "Added media object";
}

std::vector<std::unique_ptr<AbstractMedia>>& Manager::getMediaVector()
{
    return mediaVector;
}

AbstractMedia* Manager::getMedia(const QUuid &id) const
{
    for (const auto &media : mediaVector) 
    {
        if (media && media->getId() == id)
            return media.get();
    }
    return nullptr;
}

bool Manager::saveData()
{
    qDebug() << "Saving data...";
    JsonSaveVisitor saveVisitor;
    for (const auto& media : mediaVector) 
    {
        media->accept(saveVisitor);
    }

    QJsonDocument doc(saveVisitor.jsonArray);
    QFile file(userData);
    if (!file.open(QIODevice::WriteOnly)) 
    {
        qWarning() << "Failed to open file for writing:" << userData;
        return false;
    }

    if (file.write(doc.toJson(QJsonDocument::Indented)) == -1) 
    {
        qWarning() << "Failed to write to file:" << userData;
        file.close();
        return false;
    }

    file.close();
    qDebug() << "Saved data";
    return true;
}

bool Manager::loadData()
{
    qDebug() << "Loading data...";

    // Ensure base and images directories exist
    if (!dataFolder.exists() && !dataFolder.mkpath(".")) 
    {
        qWarning() << "Failed to create directory: " << dataFolder.absolutePath();
        return false;
    }
    if (!QDir(imagesPath).exists() && !QDir().mkpath(imagesPath)) 
    {
        qWarning() << "Failed to create images directory: " << imagesPath;
        return false;
    }
    
    // If data.json doesn't exist, create it with empty array
    if (!QFile::exists(userData)) 
    {
        QFile file(userData);
        if (!file.open(QIODevice::WriteOnly)) {
            qWarning() << "Failed to create file: " << userData;
            return false;
        }

        QJsonDocument jsonDoc{QJsonArray()};
        if (file.write(jsonDoc.toJson()) == -1) {
            file.close();
            qWarning() << "Failed to write to file: " << userData;
            return false;
        }

        file.close();
        return true;
    }
    else
    {
        // Load existing data.json
        QFile file(userData);
        if (!file.open(QIODevice::ReadOnly)) 
        {
            qWarning() << "Failed to open file: " << userData;
            return false;
        }

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
        file.close();

        if (error.error != QJsonParseError::NoError) 
        {
            qWarning() << "JSON parse error:" << error.errorString();
            return false;
        }

        if (!doc.isArray()) {
            qWarning() << "JSON is not an array";
            return false;
        }

        JsonLoadVisitor loadVisitor;
        loadVisitor.loadFromJsonArray(doc.array());

        for (auto &media : loadVisitor.loadedMedia) 
        {
            mediaVector.push_back(std::move(media));
        }

        qDebug() << "Loaded" << mediaVector.size() << "items into mediaVector";
    }

    qDebug() << "Data loaded successfully";
    return true;
}

bool Manager::exportData(const QString &destinationPath) const
{
    QDir srcDir(dataFolder.absolutePath());
    if (!srcDir.exists())
        return false;

    QDir dstDir(destinationPath);
    if (!dstDir.exists() && !dstDir.mkpath("."))
        return false;
    
    //without this the export only copies the items in data/ without the folder  itself
    QString folderName = srcDir.dirName();
    QString targetPath = dstDir.filePath(folderName);

    QDir targetDir(targetPath);
    if (!targetDir.exists() && !dstDir.mkpath(folderName))
        return false;

    return copyDirectoryRecursively(srcDir, targetDir);
}

bool Manager::importData(const QString &sourcePath)
{
    QDir srcDir(sourcePath);
    if (!srcDir.exists())
        return false;

    QString validationError;
    if (!validateDataFolder(srcDir, &validationError)) 
    {
        qWarning() << "Import failed:" << validationError;
        return false;
    }

    QDir dstDir(dataFolder.absolutePath());
    if (!dstDir.exists() && !dstDir.mkpath("."))
        return false;

    return copyDirectoryRecursively(srcDir, dstDir) && Manager::loadData();
}

bool Manager::copyDirectoryRecursively(const QDir &src, const QDir &dst) const
{
    for (const QFileInfo &entry : src.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries)) 
    {
        QString srcFilePath = entry.absoluteFilePath();
        QString dstFilePath = dst.filePath(entry.fileName());

        if (entry.isDir()) 
        {
            if (!dst.mkpath(entry.fileName()))
                return false;
            if (!copyDirectoryRecursively(QDir(srcFilePath), QDir(dstFilePath)))
                return false;
        } 
        else 
        {
            if (QFile::exists(dstFilePath))
                QFile::remove(dstFilePath);
            if (!QFile::copy(srcFilePath, dstFilePath))
                return false;
        }
    }
    return true;
}

bool Manager::validateDataFolder(const QDir &dir, QString *errorOut) const
{
    QFileInfo dataInfo(dir.filePath("data.json"));
    QFileInfo imagesInfo(dir.filePath("images"));

    if (!dataInfo.exists() || !dataInfo.isFile()) 
    {
        if (errorOut) *errorOut = "Missing data.json file.";
        return false;
    }
    if (!imagesInfo.exists() || !imagesInfo.isDir()) 
    {
        if (errorOut) *errorOut = "Missing images directory.";
        return false;
    }
    return true;
}