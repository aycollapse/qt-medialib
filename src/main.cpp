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
    //manager.loadData();

    // Create some media objects as unique_ptr
    
    //auto book = std::make_unique<Book>("no", 4.5f, "Novel", "asdadasd", "No comment", QDate(1925,4,10), "F. Scott Fitzgerald", "9780743273565");
    //auto movie = std::make_unique<Movie>("IASODIASODIA", 4.8f, "Sci-Fi", "Mind-bending thriller", "Awesome", QDate(2010,7,16), "Christopher Nolan", "English", QTime(2,28));
    //auto game = std::make_unique<Videogame>("The Legend of Zelda", 5.0f, "Adventure", "Epic quest", "Highly recommended", QDate(1986,2,21), "Shigeru Miyamoto", "Nintendo", "Single-player");

    //qDebug() << "Number of items in vector:" << manager.getMediaVector().size();
    //manager.addMedia(std::move(book));
    //manager.addMedia(std::move(movie));
    //manager.addMedia(std::move(game));
    
    //qDebug() << "Number of items in vector:" << manager.getMediaVector().size();
    //manager.saveData();

    MainWindow w;
    w.show();
    
    return app.exec();
}