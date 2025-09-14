#include "search_visitor.h"

SearchVisitor::SearchVisitor(const QString& text)
    : searchText(text.trimmed().toLower()), matches(false)
{
}

static inline bool containsLower(const QString &haystack, const QString &needle)
{
    if (needle.isEmpty()) return true; // empty search matches
    return haystack.toLower().contains(needle);
}

void SearchVisitor::visit(Book &book)
{
    // check common fields first
    matches = checkCommonFields(book);
    if (matches) return;

    // book-specific fields
    if (containsLower(book.getAuthor(), searchText)) {
        matches = true;
        return;
    }

    if (containsLower(book.getISBN(), searchText)) {
        matches = true;
        return;
    }
}

void SearchVisitor::visit(Movie &movie)
{
    matches = checkCommonFields(movie);
    if (matches) return;

    if (containsLower(movie.getDirector(), searchText)) {
        matches = true;
        return;
    }

    if (containsLower(movie.getLanguage(), searchText)) {
        matches = true;
        return;
    }

    QString dur = movie.getDuration().toString("hh:mm");
    if (containsLower(dur, searchText)) {
        matches = true;
        return;
    }
    if (!searchText.isEmpty()) {
        QString ratingStr = QString::number(movie.getRating(), 'f', 1);
        if (ratingStr.contains(searchText)) {
            matches = true;
            return;
        }
    }
}

void SearchVisitor::visit(Videogame &game)
{
    matches = checkCommonFields(game);
    if (matches) return;

    if (containsLower(game.getGameDirector(), searchText)) {
        matches = true;
        return;
    }
    if (containsLower(game.getPublisher(), searchText)) {
        matches = true;
        return;
    }
    if (containsLower(game.getMode(), searchText)) {
        matches = true;
        return;
    }
}

bool SearchVisitor::checkCommonFields(AbstractMedia &media)
{
    if (searchText.isEmpty()) return true;
    if (containsLower(media.getName(), searchText)) return true;
    QString ratingStr = QString::number(media.getRating(), 'f', 1);
    if (ratingStr.contains(searchText)) return true;
    if (containsLower(media.getGenre(), searchText)) return true;
    if (containsLower(media.getDescription(), searchText)) return true;
    if (containsLower(media.getComment(), searchText)) return true;
    if (containsLower(media.getBannerPath(), searchText)) return true;
    QString dateStr = media.getDateRelease().toString("yyyy-MM-dd");
    if (dateStr.contains(searchText)) return true;

    return false;
}

bool SearchVisitor::isMatch() const { return matches; }
