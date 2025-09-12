#ifndef MEDIA_CARD_VISITOR_H
#define MEDIA_CARD_VISITOR_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileInfo>
#include <QFile>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include "../../core/visitors/visitor.h"
#include "../../core/models/book.h"
#include "../../core/models/movie.h"
#include "../../core/models/videogame.h"

class MediaCardVisitor : public Visitor {
public:
    MediaCardVisitor() : widget(new QWidget) {
        widget->setFixedSize(150, 300); // Adjusted for taller banner
        widget->setObjectName("MediaCard");

        auto *layout = new QVBoxLayout(widget);
        layout->setContentsMargins(5, 5, 5, 5);
        layout->setSpacing(4);

        imageButton = new QPushButton(widget);
        imageButton->setObjectName("imageButton");
        imageButton->setFixedSize(140, 210); // Changed to 2:3 aspect ratio
        imageButton->setFlat(true);
        layout->addWidget(imageButton, 0, Qt::AlignCenter);

        titleLabel = new QLabel(widget);
        titleLabel->setObjectName("cardTitle");
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setWordWrap(true);
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        layout->addWidget(titleLabel);

        genreLabel = new QLabel(widget);
        genreLabel->setObjectName("cardGenre");
        genreLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(genreLabel);

        ratingLabel = new QLabel(widget);
        ratingLabel->setObjectName("cardRating");
        ratingLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(ratingLabel);

        typeLabel = new QLabel(widget);
        typeLabel->setObjectName("cardType");
        typeLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(typeLabel);

        layout->addStretch();
    }

    void visit(Book &book) override {
        applyCommon("book");
        titleLabel->setText(book.getName());
        genreLabel->setText(book.getGenre());
        ratingLabel->setText(QString::number(book.getRating(), 'f', 1) + "/10");
        typeLabel->setText("Book");
        
        if (!book.getBannerPath().isEmpty() && QFileInfo::exists(book.getBannerPath())) {
            applyBanner(book.getBannerPath());
        }
    }

    void visit(Movie &movie) override {
        applyCommon("movie");
        titleLabel->setText(movie.getName());
        genreLabel->setText(movie.getGenre());
        ratingLabel->setText(QString::number(movie.getRating(), 'f', 1) + "/10");
        typeLabel->setText("Movie");
        
        if (!movie.getBannerPath().isEmpty() && QFileInfo::exists(movie.getBannerPath())) {
            applyBanner(movie.getBannerPath());
        }
    }

    void visit(Videogame &game) override {
        applyCommon("videogame");
        titleLabel->setText(game.getName());
        genreLabel->setText(game.getGenre());
        ratingLabel->setText(QString::number(game.getRating(), 'f', 1) + "/10");
        typeLabel->setText("Video Game");
        
        if (!game.getBannerPath().isEmpty() && QFileInfo::exists(game.getBannerPath())) {
            applyBanner(game.getBannerPath());
        }
    }

    QWidget* getWidget() const { return widget; }

private:
    QWidget *widget;
    QPushButton *imageButton;
    QLabel *titleLabel;
    QLabel *genreLabel;
    QLabel *ratingLabel;
    QLabel *typeLabel;

    void applyCommon(const QString &typeName) {
        imageButton->setProperty("mediaType", typeName);
        widget->setProperty("mediaType", typeName);
        imageButton->setIcon(QIcon());
        imageButton->setStyleSheet("");
    }

    void applyBanner(const QString &bannerPath) {
        QPixmap pixmap(bannerPath);
        if (!pixmap.isNull()) {
            // Scale and crop to fit while maintaining aspect ratio
            pixmap = pixmap.scaled(140, 210, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            if (pixmap.width() > 140 || pixmap.height() > 210) {
                int x = pixmap.width() > 140 ? (pixmap.width() - 140) / 2 : 0;
                int y = pixmap.height() > 210 ? (pixmap.height() - 210) / 2 : 0;
                pixmap = pixmap.copy(x, y, 140, 210);
            }

            // Create a rounded version of the image
            QPixmap rounded(pixmap.size());
            rounded.fill(Qt::transparent);

            QPainter painter(&rounded);
            painter.setRenderHint(QPainter::Antialiasing);
            
            QPainterPath path;
            path.addRoundedRect(0, 0, 140, 210, 10, 10);
            painter.setClipPath(path);
            painter.drawPixmap(0, 0, pixmap);

            imageButton->setIcon(QIcon(rounded));
            imageButton->setIconSize(QSize(140, 210));
            imageButton->setStyleSheet("QPushButton#imageButton { background: transparent; }");
        }
    }
};

#endif // MEDIA_CARD_VISITOR_H