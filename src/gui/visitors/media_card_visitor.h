#ifndef MEDIA_CARD_VISITOR_H
#define MEDIA_CARD_VISITOR_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "../../core/visitors/visitor.h"
#include "../../core/models/book.h"
#include "../../core/models/movie.h"
#include "../../core/models/videogame.h"

class MediaCardVisitor : public Visitor {
public:
    MediaCardVisitor() : widget(new QPushButton) {
        widget->setFixedSize(150, 200);
        auto *layout = new QVBoxLayout(widget);
        layout->setContentsMargins(5, 5, 5, 5);
        
        titleLabel = new QLabel(widget);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setWordWrap(true);
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        layout->addWidget(titleLabel);
        
        genreLabel = new QLabel(widget);
        genreLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(genreLabel);
        
        ratingLabel = new QLabel(widget);
        ratingLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(ratingLabel);

        layout->addStretch();
    }

    void visit(Book &book) override {
        widget->setStyleSheet("QPushButton { background-color: #90EE90; border-radius: 10px; padding: 5px; }");  // Light green
        titleLabel->setText(book.getName());
        genreLabel->setText(book.getGenre());
        ratingLabel->setText(QString::number(book.getRating(), 'f', 1) + "/10");
    }

    void visit(Movie &movie) override {
        widget->setStyleSheet("QPushButton { background-color: #FFB347; border-radius: 10px; padding: 5px; }");  // Light orange
        titleLabel->setText(movie.getName());
        genreLabel->setText(movie.getGenre());
        ratingLabel->setText(QString::number(movie.getRating(), 'f', 1) + "/10");
    }

    void visit(Videogame &game) override {
        widget->setStyleSheet("QPushButton { background-color: #87CEEB; border-radius: 10px; padding: 5px; }");  // Light blue
        titleLabel->setText(game.getName());
        genreLabel->setText(game.getGenre());
        ratingLabel->setText(QString::number(game.getRating(), 'f', 1) + "/10");
    }

    QPushButton* getWidget() const { return widget; }

private:
    QPushButton *widget;
    QLabel *titleLabel;
    QLabel *genreLabel;
    QLabel *ratingLabel;
};

#endif // MEDIA_CARD_VISITOR_H