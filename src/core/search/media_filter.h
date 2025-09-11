#ifndef MEDIA_FILTER_H
#define MEDIA_FILTER_H

#include <QString>
#include "../models/abstract_media.h"
#include "../visitors/search_visitor.h"
#include "../visitors/media_type_visitor.h"

class MediaFilter {
public:
    struct FilterSettings {
        QString searchText;
        bool showBooks = true;
        bool showMovies = true;
        bool showGames = true;
    };

    static bool matchesFilter(AbstractMedia* media, const FilterSettings& settings) {
        // First check if this type is enabled
        MediaTypeVisitor typeVisitor;
        media->accept(typeVisitor);
        
        bool typeEnabled = false;
        switch (typeVisitor.getType()) {
            case MediaTypeVisitor::MediaType::Book:
                typeEnabled = settings.showBooks;
                break;
            case MediaTypeVisitor::MediaType::Movie:
                typeEnabled = settings.showMovies;
                break;
            case MediaTypeVisitor::MediaType::Videogame:
                typeEnabled = settings.showGames;
                break;
        }
        
        if (!typeEnabled) {
            return false;
        }

        // If no search text, just return true (show all of enabled type)
        if (settings.searchText.isEmpty()) {
            return true;
        }

        // Check if media matches search text using the search visitor
        SearchVisitor searchVisitor(settings.searchText);
        media->accept(searchVisitor);
        
        return searchVisitor.isMatch();
    }
};

#endif // MEDIA_FILTER_H
