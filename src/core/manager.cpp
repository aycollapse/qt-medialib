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
}

void Manager::setDefaultData(QString dataFolderPath)
{
    dataFolder = QDir(dataFolderPath);
    if (!dataFolder.exists()) {
        dataFolder.mkpath(".");
    }
    imagesPath = dataFolder.filePath("images");
    if (!QDir(imagesPath).exists()) {
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
    for (const auto &media : mediaVector) {
        if (media && media->getId() == id)
            return media.get();
    }
    return nullptr;
}

void Manager::saveData()
{
    qDebug() << "Saving data...";
    JsonSaveVisitor saveVisitor;
    for (const auto& media : mediaVector) {
        media->accept(saveVisitor);
    }

    QJsonDocument doc(saveVisitor.jsonArray);
    QFile file(userData);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << userData;
        return;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    qDebug() << "Saved data";
}

void Manager::loadData()
{
    qDebug() << "Loading data...";
    try 
    {
        // Ensure base and images directories exist
        if (!dataFolder.exists() && !dataFolder.mkpath(".")) {
            throw std::runtime_error("Failed to create directory: " + dataFolder.absolutePath().toStdString());
        }
        if (!QDir(imagesPath).exists() && !QDir().mkpath(imagesPath)) {
            throw std::runtime_error("Failed to create images directory: " + imagesPath.toStdString());
        }
        
        // If data.json doesn't exist, create it with empty array
        if (!QFile::exists(userData)) {
            QFile file(userData);
            if (!file.open(QIODevice::WriteOnly)) {
                throw std::runtime_error("Failed to create file: " + userData.toStdString());
            }

            QJsonDocument jsonDoc{QJsonArray()};
            if (file.write(jsonDoc.toJson()) == -1) {
                file.close();
                throw std::runtime_error("Failed to write to file: " + userData.toStdString());
            }

            file.close();
        }
        else
        {
            // Load existing data.json
            QFile file(userData);
            if (!file.open(QIODevice::ReadOnly)) {
                throw std::runtime_error("Failed to open file: " + userData.toStdString());
            }

            QJsonParseError error;
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
            file.close();

            if (error.error != QJsonParseError::NoError) {
                throw std::runtime_error("JSON parse error: " + error.errorString().toStdString());
            }
            if (!doc.isArray()) {
                throw std::runtime_error("JSON is not an array");
            }

            for (const auto &value : doc.array()) { // TODO: load with JsonLoadVisitor
                if (value.isObject()) {
                    qDebug() << "Loaded media object:" << value.toObject();
                }
            }
        }
    }
    catch (const std::exception &e) 
    {
        qWarning() << "Error:" << e.what();
    }

    qDebug() << "Loaded data";
}

bool Manager::exportData(const QString &destinationPath) const
{
    QDir srcDir(dataFolder.absolutePath());
    if (!srcDir.exists())
        return false;

    QDir dstDir(destinationPath);
    if (!dstDir.exists() && !dstDir.mkpath("."))
        return false;

    return copyDirectoryRecursively(srcDir, dstDir);
}

bool Manager::importData(const QString &sourcePath)
{
    QDir srcDir(sourcePath);
    if (!srcDir.exists())
        return false;

    QString validationError;
    if (!validateDataFolder(srcDir, &validationError)) {
        qWarning() << "Import failed:" << validationError;
        return false;
    }

    QDir dstDir(dataFolder.absolutePath());
    if (!dstDir.exists() && !dstDir.mkpath("."))
        return false;

    return copyDirectoryRecursively(srcDir, dstDir);
}

bool Manager::copyDirectoryRecursively(const QDir &src, const QDir &dst) const
{
    for (const QFileInfo &entry : src.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries)) {
        QString srcFilePath = entry.absoluteFilePath();
        QString dstFilePath = dst.filePath(entry.fileName());

        if (entry.isDir()) {
            if (!dst.mkpath(entry.fileName()))
                return false;
            if (!copyDirectoryRecursively(QDir(srcFilePath), QDir(dstFilePath)))
                return false;
        } else {
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

    if (!dataInfo.exists() || !dataInfo.isFile()) {
        if (errorOut) *errorOut = "Missing data.json file.";
        return false;
    }
    if (!imagesInfo.exists() || !imagesInfo.isDir()) {
        if (errorOut) *errorOut = "Missing images directory.";
        return false;
    }
    return true;
}
