#include <QApplication>
#include "gui/widgets/main_window.h"
#include "core/models/manager.h"
#include "controller/controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icons/library.png"));  
    
    MainWindow w;
    MediaController controller(Manager::getInstance(), w);
    
    w.show();
    return app.exec();
}