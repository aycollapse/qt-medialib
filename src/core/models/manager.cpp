#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QFileInfo>
#include <QImage>

#include "../visitors/json_save_visitor.h"
#include "../visitors/json_load_visitor.h"
#include "manager.h"

Manager::Manager()
{
    loadData();
}

void Manager::addMedia(std::unique_ptr<AbstractMedia> media) {
    mediaVector.push_back(std::move(media));
}

std::vector<std::unique_ptr<AbstractMedia>>& Manager::getMediaVector(){return mediaVector;}


void Manager::saveData()
{
    JsonSaveVisitor saveVisitor;
    for (const auto& media : mediaVector)
    {
        media->accept(saveVisitor);
    }

    QJsonDocument doc(saveVisitor.jsonArray);
    QFile file(dataPath);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Failed to open file for writing:" << dataPath;
        return;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

void Manager::loadData()
{
    try 
    {
        // check if /data directory exists
        if (!rootDir.exists("data")) 
        {
            if (!rootDir.mkpath("data")) 
            {
                throw std::runtime_error("Failed to create directory: " + rootDir.filePath("data").toStdString());
            }
        }

        if (!rootDir.exists("data/images")) 
        {
            if (!rootDir.mkpath("data/images")) 
            {
                throw std::runtime_error("Failed to create directory: " + rootDir.filePath("data").toStdString());
            }
        }
        
        // if data.json doesn't exist create it with empty array
        if (!QFile::exists(dataPath)) 
        {
            QFile file(dataPath);
            if (!file.open(QIODevice::WriteOnly)) 
            {
                throw std::runtime_error("Failed to create file: " + dataPath.toStdString());
            }

            QJsonDocument jsonDoc{QJsonArray()};
            if (file.write(jsonDoc.toJson()) == -1) 
            {
                file.close();
                throw std::runtime_error("Failed to write to file: " + dataPath.toStdString());
            }

            file.close();
        }
        else
        {
            // if data.json exists open it and load data
            QFile file(dataPath);
            if (!file.open(QIODevice::ReadOnly)) {
                throw std::runtime_error("Failed to open file: " + dataPath.toStdString());
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

            for (const auto &value : doc.array()) { //TODO load with visitor
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
}

