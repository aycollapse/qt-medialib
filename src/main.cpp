#include <QApplication>
#include <QDebug>

#include "core/manager.h"
#include "core/models/book.h"
#include "core/models/movie.h"
#include "core/models/videogame.h"
#include "gui/widgets/main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Manager& manager = Manager::getInstance();

    // Create some media objects as unique_ptr
    
    //auto book = std::make_unique<Book>("minghie", 4.5f, "Novel", "asdadasd", "No comment", QDate(1925,4,10), "Fr", "9780743273565");
    //auto movie = std::make_unique<Movie>("hello", 4.8f, "Sci-Fi", "Mind-bending thriller", "Awesome", QDate(2010,7,16), "Christopher Nolan", "English", QTime(2,28));
    //auto game = std::make_unique<Videogame>("asdasdasdad", 5.0f, "Adventure", "Epic quest", "Highly recommended", QDate(1986,2,21), "Shigeru Miyamoto", "Nintendo", "Single-player");

    qDebug() << "Number of items in vector:" << manager.getMediaVector().size();
    //manager.addMedia(std::move(book));
    //manager.addMedia(std::move(movie));
    //manager.addMedia(std::move(game));
    
    qDebug() << "Dumping loaded items:";
    for (size_t i = 0; i < manager.getMediaVector().size(); ++i) {
        auto &ptr = manager.getMediaVector()[i];
        if (!ptr) {
            qDebug() << "Index" << i << "is nullptr";
        } else {
            qDebug() << "Index" << i << ptr->getId().toString() << ptr->getName();
        }
    }
    // all this stuff is for debug, ill delete later obviously
    manager.deleteMedia(QUuid("{c5b80cfd-1495-417b-b05b-21bbd2173fa4}"));
    manager.saveData();

    qDebug() << "Dumping loaded items:";
    for (size_t i = 0; i < manager.getMediaVector().size(); ++i) {
        auto &ptr = manager.getMediaVector()[i];
        if (!ptr) {
            qDebug() << "Index" << i << "is nullptr";
        } else {
            qDebug() << "Index" << i << ptr->getId().toString() << ptr->getName();
        }
    }

    MainWindow w;
    w.show();
    
    return app.exec();
}