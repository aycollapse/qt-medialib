#ifndef SEARCH_BAR_H
#define SEARCH_BAR_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include "../../core/search/media_filter.h"

class SearchBar : public QWidget {
    Q_OBJECT
public:
    explicit SearchBar(QWidget *parent = nullptr) : QWidget(parent) {
        auto *layout = new QHBoxLayout(this);
        layout->setContentsMargins(10, 5, 10, 5);

        searchInput = new QLineEdit(this);
        searchInput->setPlaceholderText("Search media...");
        searchInput->setClearButtonEnabled(true);

        booksCheckBox = new QCheckBox("Books", this);
        moviesCheckBox = new QCheckBox("Movies", this);
        gamesCheckBox = new QCheckBox("Games", this);

        booksCheckBox->setChecked(true);
        moviesCheckBox->setChecked(true);
        gamesCheckBox->setChecked(true);

        auto *separator = new QLabel("|", this);

        layout->addWidget(searchInput, 1); 
        layout->addWidget(separator);
        layout->addWidget(booksCheckBox);
        layout->addWidget(moviesCheckBox);
        layout->addWidget(gamesCheckBox);

        connect(searchInput, &QLineEdit::textChanged, this, &SearchBar::onFilterChanged);
        connect(booksCheckBox, &QCheckBox::toggled, this, &SearchBar::onFilterChanged);
        connect(moviesCheckBox, &QCheckBox::toggled, this, &SearchBar::onFilterChanged);
        connect(gamesCheckBox, &QCheckBox::toggled, this, &SearchBar::onFilterChanged);
    }

    MediaFilter::FilterSettings getCurrentFilter() const {
        MediaFilter::FilterSettings settings;
        settings.searchText = searchInput->text();
        settings.showBooks = booksCheckBox->isChecked();
        settings.showMovies = moviesCheckBox->isChecked();
        settings.showGames = gamesCheckBox->isChecked();
        return settings;
    }

    QLineEdit* getSearchInput() const { return searchInput; }

signals:
    void filterChanged(const MediaFilter::FilterSettings& settings);

private slots:
    void onFilterChanged() {
        emit filterChanged(getCurrentFilter());
    }

private:
    QLineEdit *searchInput;
    QCheckBox *booksCheckBox;
    QCheckBox *moviesCheckBox;
    QCheckBox *gamesCheckBox;
};

#endif // SEARCH_BAR_H
