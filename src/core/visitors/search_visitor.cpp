#include "search_visitor.h"
#include <QRegularExpression>

SearchVisitor::SearchVisitor(const QString& text)
    : searchText(text.trimmed().toLower()), matches(false)
{
}

void SearchVisitor::visit(Book &book)
{
    matches = checkCommonFields(book);
}

void SearchVisitor::visit(Movie &movie)
{
    matches = checkCommonFields(movie);
}

void SearchVisitor::visit(Videogame &game)
{
    matches = checkCommonFields(game);
}

bool SearchVisitor::checkCommonFields(AbstractMedia &media)
{
    if (searchText.isEmpty()) return true;

    const QString lowered = searchText.toLower();

    if (media.getName().toLower().contains(lowered)) return true;
    if (media.getGenre().toLower().contains(lowered)) return true;
    if (media.getDescription().toLower().contains(lowered)) return true;
    if (media.getComment().toLower().contains(lowered)) return true;

    return false;
}

bool SearchVisitor::isMatch() const { return matches; }
