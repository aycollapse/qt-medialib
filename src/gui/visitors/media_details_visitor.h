#ifndef MEDIA_DETAILS_VISITOR
#define MEDIA_DETAILS_VISITOR

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QPlainTextEdit>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSizePolicy>
#include "../../core/visitors/visitor.h"
#include "../../core/models/book.h"
#include "../../core/models/movie.h"
#include "../../core/models/videogame.h"

class MediaDetailsVisitor : public Visitor {
public:
    MediaDetailsVisitor() : widget(new QWidget) {}

    void visit(Book &book) override {
        auto *layout = new QFormLayout(widget);
        addBaseFields(layout, book.getName(), book.getRating(), book.getGenre(),
                      book.getDescription(), book.getComment(),
                      book.getDateRelease(), book.getBannerPath());

        auto *authorEdit = new QLineEdit(book.getAuthor());
        authorEdit->setObjectName("author");
        auto *isbnEdit = new QLineEdit(book.getISBN());
        isbnEdit->setObjectName("isbn");
        // Validator: allow empty or exactly 13 digits
        QRegularExpression re("(^$)|(^\\d{13}$)");
        auto *validator = new QRegularExpressionValidator(re, isbnEdit);
        isbnEdit->setValidator(validator);

        layout->addRow("Author:", authorEdit);
        //TODO add validation for isbn (13 digits, no dashes)
        layout->addRow("ISBN 13:", isbnEdit);
    }

    void visit(Movie &movie) override {
        auto *layout = new QFormLayout(widget);
        addBaseFields(layout, movie.getName(), movie.getRating(), movie.getGenre(),
                      movie.getDescription(), movie.getComment(),
                      movie.getDateRelease(), movie.getBannerPath());

        auto *directorEdit = new QLineEdit(movie.getDirector());
        directorEdit->setObjectName("director");
        
        auto *languageEdit = new QLineEdit(movie.getLanguage());
        languageEdit->setObjectName("language");
        
        // Replace QTimeEdit with two spin boxes: hours and minutes
        QWidget *durationContainer = new QWidget;
        QHBoxLayout *durationLayout = new QHBoxLayout(durationContainer);
        durationLayout->setContentsMargins(0,0,0,0);
        auto *hoursSpin = new QSpinBox;
        hoursSpin->setRange(0, 99);
        hoursSpin->setValue(movie.getDuration().hour());
        hoursSpin->setObjectName("durationHours");
        hoursSpin->setSuffix(" h");
        auto *minutesSpin = new QSpinBox;
        minutesSpin->setRange(0, 59);
        minutesSpin->setValue(movie.getDuration().minute());
        minutesSpin->setObjectName("durationMinutes");
        minutesSpin->setSuffix(" m");
        durationLayout->addWidget(hoursSpin);
        durationLayout->addWidget(minutesSpin);
        
        layout->addRow("Director:", directorEdit);
        layout->addRow("Language:", languageEdit);
        layout->addRow("Duration:", durationContainer);
    }

    void visit(Videogame &game) override {
        auto *layout = new QFormLayout(widget);
        addBaseFields(layout, game.getName(), game.getRating(), game.getGenre(),
                      game.getDescription(), game.getComment(),
                      game.getDateRelease(), game.getBannerPath());

        auto *gameDirectorEdit = new QLineEdit(game.getGameDirector());
        gameDirectorEdit->setObjectName("gameDirector");
        
        auto *publisherEdit = new QLineEdit(game.getPublisher());
        publisherEdit->setObjectName("publisher");
        
        // Mode as dropdown
        auto *modeCombo = new QComboBox;
        modeCombo->setObjectName("mode");
        modeCombo->addItems({"single-player", "multi-player", "co-op"});
        int idx = modeCombo->findText(game.getMode(), Qt::MatchFixedString | Qt::MatchCaseSensitive);
        if (idx >= 0) modeCombo->setCurrentIndex(idx);
        
        layout->addRow("Game Director:", gameDirectorEdit);
        layout->addRow("Publisher:", publisherEdit);
        layout->addRow("Mode:", modeCombo);
    }

    QWidget* getWidget() const { return widget; }

private:
    QWidget *widget;

    void addBaseFields(QFormLayout *layout,const QString &name,float rating,const QString &genre,
                       const QString &description,const QString &comment,const QDate &dateReleased,
                       const QString &bannerPath)
    {
        auto *nameEdit = new QLineEdit(name);
        nameEdit->setObjectName("name");
        
        auto *ratingContainer = new QWidget;
        auto *ratingLayout = new QHBoxLayout(ratingContainer);
        ratingLayout->setContentsMargins(0, 0, 0, 0);
        ratingLayout->setAlignment(Qt::AlignVCenter);
        ratingContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ratingContainer->setMaximumHeight(30);
        
        auto *ratingLineEdit = new QLineEdit(QString::number(rating, 'f', 1));
        ratingLineEdit->setObjectName("rating");
        ratingLineEdit->setReadOnly(true);
        ratingLineEdit->setMaximumWidth(50);  
        ratingLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        
        auto *ratingSlider = new QSlider(Qt::Horizontal);
        ratingSlider->setObjectName("ratingSlider");
        ratingSlider->setRange(0, 20);
        ratingSlider->setTickPosition(QSlider::TicksBelow);
        ratingSlider->setTickInterval(1);
        ratingSlider->setValue(static_cast<int>(rating * 2));
        ratingSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ratingSlider->setFixedHeight(24);
        
        QObject::connect(ratingSlider, &QSlider::valueChanged, [ratingLineEdit](int value) {
            float realValue = value / 2.0f;
            ratingLineEdit->setText(QString::number(realValue, 'f', 1));
        });
        
        ratingLayout->addWidget(ratingSlider, 3); 
        ratingLayout->addWidget(ratingLineEdit, 1); 

        auto *genreEdit = new QLineEdit(genre);
        genreEdit->setObjectName("genre");
        
        auto *descriptionEdit = new QPlainTextEdit;
        descriptionEdit->setObjectName("description");
        descriptionEdit->setPlainText(description);
        descriptionEdit->setMaximumHeight(60);
        descriptionEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        
        auto *commentEdit = new QPlainTextEdit;
        commentEdit->setObjectName("comment");
        commentEdit->setPlainText(comment);
        commentEdit->setMaximumHeight(60);
        commentEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        
        auto *dateEdit = new QDateEdit(dateReleased);
        dateEdit->setObjectName("dateRelease");
        dateEdit->setCalendarPopup(true);
        dateEdit->setDisplayFormat("dd MMM yyyy"); 
        
        auto *bannerPathEdit = new QLineEdit(bannerPath);
        bannerPathEdit->setObjectName("bannerPath");

        layout->addRow("Name:", nameEdit);
        layout->addRow("Rating:", ratingContainer);
        layout->addRow("Genre:", genreEdit);
        layout->addRow("Description:", descriptionEdit);
        layout->addRow("Comment:", commentEdit);
        layout->addRow("Release Date:", dateEdit);
        layout->addRow("Banner Path:", bannerPathEdit);
    }
};

#endif // MEDIA_DETAILS_VISITOR
