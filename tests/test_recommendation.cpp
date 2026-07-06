#include <iostream>
#include <vector>
#include <iomanip>

#include "core/content.hpp"
#include "core/genre.hpp"
#include "core/type.hpp"
#include "core/score_calculator.hpp"

int main() {
    std::cout << "=== CornHub Recommendation System Test ===" << std::endl;

    // Create a mock catalog of contents
    // Movie/Series get 10 points base.
    // Popularity = (views/10) + rating. If Movie/Series, multiplied by 1.5.
    // Classic (<= 2015): multiply by (2026 - year)
    // New Release (> 2015): divide by (2026 - year)
    // Liked genres: +10 per genre.
    std::vector<Content*> catalog = {
        new Content("Interstellar", Type::MOVIE, Genre::SCIENCE_FICTION, 2014, 950000, 4.9), // Classic, diff = 12
        new Content("The Matrix", Type::MOVIE, Genre::ACTION, 1999, 800000, 4.8),           // Classic, diff = 27
        new Content("Modern Comedy", Type::MOVIE, Genre::COMEDY, 2024, 150000, 4.2),        // New Release, diff = 2
        new Content("Horror Show", Type::SERIES, Genre::HORROR, 2025, 50000, 3.8),          // New Release, diff = 1
        new Content("Slice of Life Anime", Type::ANIME, Genre::SLICE_OF_LIFE, 2021, 200000, 4.7), // New Release, diff = 5 (Anime, no Movie/Series boost)
        new Content("Romantic Sunset", Type::MOVIE, Genre::ROMANCE, 2010, 50000, 4.5),       // Classic, diff = 16
        new Content("Action Movie Fast", Type::MOVIE, Genre::ACTION, 2026, 300000, 3.5),     // New Release, diff = 1
        new Content("Vintage Horror", Type::MOVIE, Genre::HORROR, 1980, 100000, 4.0)         // Classic, diff = 46
    };

    ScoreCalculator calculator;
    calculator.build_default_tree();

    std::cout << "Loading recommendation questions tree..." << std::endl;
    std::cout << "Please answer the questions below to receive catalog recommendations." << std::endl;

    Node* recommendations = calculator.recommend(catalog);

    std::cout << "\n=== Your Recommendations (Sorted by Score) ===" << std::endl;
    std::cout << std::left << std::setw(25) << "Title" 
              << std::setw(15) << "Type" 
              << std::setw(18) << "Genre" 
              << std::setw(8) << "Year" 
              << std::setw(12) << "Views" 
              << std::setw(8) << "Rating" 
              << std::setw(10) << "Score" 
              << std::endl;
    std::cout << std::string(96, '-') << std::endl;

    Node* curr = recommendations;
    while (curr != nullptr) {
        Content* c = curr->content;
        std::string typeStr;
        switch(c->get_type()) {
            case Type::MOVIE: typeStr = "Movie"; break;
            case Type::SERIES: typeStr = "Series"; break;
            case Type::DOCUMENTARY: typeStr = "Documentary"; break;
            case Type::ANIME: typeStr = "Anime"; break;
            case Type::CARTOON: typeStr = "Cartoon"; break;
        }

        std::string genreStr;
        switch(c->get_genre()) {
            case Genre::ACTION: genreStr = "Action"; break;
            case Genre::COMEDY: genreStr = "Comedy"; break;
            case Genre::ROMANCE: genreStr = "Romance"; break;
            case Genre::HORROR: genreStr = "Horror"; break;
            case Genre::SUSPENSE: genreStr = "Suspense"; break;
            case Genre::DRAMA: genreStr = "Drama"; break;
            case Genre::SCIENCE_FICTION: genreStr = "Sci-Fi"; break;
            case Genre::SLICE_OF_LIFE: genreStr = "Slice-of-Life"; break;
        }

        std::cout << std::left << std::setw(25) << c->get_title()
                  << std::setw(15) << typeStr
                  << std::setw(18) << genreStr
                  << std::setw(8) << c->get_year()
                  << std::setw(12) << c->get_views()
                  << std::setw(8) << c->get_rating()
                  << std::setw(10) << c->get_score()
                  << std::endl;

        curr = curr->next;
    }

    // Clean up
    ScoreCalculator::free_list(recommendations);
    for (Content* c : catalog) {
        delete c;
    }

    std::cout << "\nTest completed successfully." << std::endl;
    return 0;
}
