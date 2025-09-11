#include "controller.h"
#include "../core/models/manager.h"
#include "../core/visitors/create_media_visitor.h"
#include "../gui/widgets/main_window.h"

MediaController::MediaController(Manager &manager, MainWindow &mainWindow, QObject *parent)
    : QObject(parent), manager(manager), mainWindow(mainWindow)
{
    setupConnections();
}

void MediaController::setupConnections()
{
    connect(&mainWindow, &MainWindow::saveMediaRequested,
            this, &MediaController::handleSaveRequested);
    connect(&mainWindow, &MainWindow::deleteMediaRequested,
            this, &MediaController::handleDeleteRequested);
}

void MediaController::handleSaveRequested(const QUuid &id, const QMap<QString, QString> &data)
{
    if (id.isNull()) {
        qDebug() << "Creating new media";
        
        QMap<QString, QString> dataWithId = data;
        dataWithId["id"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
        qDebug() << "Created new UUID for media:" << dataWithId["id"];
        
        CreateItemVisitor creator(dataWithId);
        auto newMedia = creator.takeItem();
        if (newMedia) {
            manager.addMedia(std::move(newMedia));
            manager.saveData();
        } else {
            qDebug() << "Error: Failed to create media item";
        }
    } else {
        qDebug() << "Updating existing media with ID:" << id.toString();

        AbstractMedia* existingMedia = manager.getMedia(id);
        if (!existingMedia) {
            qDebug() << "Error: Could not find existing media with ID:" << id.toString();
            return;
        }
        
        if (manager.editMedia(id, data)) {
            manager.saveData();
            qDebug() << "Changes saved successfully";
        } else {
            qDebug() << "Error: Failed to update media";
        }
    }
}

void MediaController::handleDeleteRequested(const QUuid &id)
{
    
    //delete the media from the manager
    if (manager.deleteMedia(id)) {
        manager.saveData();
        qDebug() << "Changes saved successfully";
    } else {
        qDebug() << "Error: Failed to delete media";
    }
}