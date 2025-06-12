#include <QCoreApplication>
#include <QDebug>

#include "core/models/manager.h"
#include "core/models/book.h"
#include "core/models/movie.h"
#include "core/models/videogame.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Manager manager;

    // Create some media objects as unique_ptr
    auto book = std::make_unique<Book>("The Great Gatsby", 4.5f, "Novel", "Classic book", "No comment", QDate(1925,4,10), "F. Scott Fitzgerald", "9780743273565");
    auto movie = std::make_unique<Movie>("Inception", 4.8f, "Sci-Fi", "Mind-bending thriller", "Awesome", QDate(2010,7,16), "Christopher Nolan", "English", QTime(2,28));
    auto game = std::make_unique<Videogame>("The Legend of Zelda", 5.0f, "Adventure", "Epic quest", "Highly recommended", QDate(1986,2,21), "Shigeru Miyamoto", "Nintendo", "Single-player");

    manager.addMedia(std::move(book));
    manager.addMedia(std::move(movie));
    manager.addMedia(std::move(game));

    // Now save data
    manager.saveData();

    return 0;
}