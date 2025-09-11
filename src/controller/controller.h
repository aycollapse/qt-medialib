#ifndef CONTROLLER
#define CONTROLLER

#include <QObject>
#include <QUuid>
#include <QMap>

//interface class between gui and core logic
//handles signals from main window and calls appropriate manager functions

class Manager;
class MainWindow;

class MediaController : public QObject {
    Q_OBJECT
public:
    MediaController(Manager &manager, MainWindow &mainWindow, QObject *parent = nullptr);

private slots:
    void handleSaveRequested(const QUuid &id, const QMap<QString, QString> &changes);
    void handleDeleteRequested(const QUuid &id);

private:
    void setupConnections();

private:
    Manager &manager;
    MainWindow &mainWindow;
};
#endif //CONTROLLER