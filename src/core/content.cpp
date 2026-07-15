#include <iostream>

#include "core/content.hpp"

int Content::next_id = 1;

Content::Content (): id(0), title(""), type(Type::MOVIE), genre(Genre::ACTION), year(0), views(0), rating(0.0f), rating_count(0) {}

Content::Content (std::string title, Type type, Genre genre, int year, long views, float rating):

    id(next_id++),
    title(title),
    type(type),
    genre(genre),
    year(year),
    views(views),
    rating((rating <= 5 && rating >= 0) ? rating : 0),
    rating_count(0)

{}

Content::Content (int id, std::string title, Type type, Genre genre, int year, long views, float rating, int rating_count):

    id(id),
    title(title),
    type(type),
    genre(genre),
    year(year),
    views(views),
    rating((rating <= 5 && rating >= 0) ? rating : 0),
    rating_count(rating_count)

{
    if (id >= next_id) next_id = id + 1;
}

int Content::get_id() const { return id; }
std::string Content::get_title() const { return title; }
Type Content::get_type() const { return type; }
Genre Content::get_genre() const { return genre; }
int Content::get_year() const { return year; }
long Content::get_views() const { return views; }
float Content::get_rating () const { return rating; }
int Content::get_rating_count () const { return rating_count; }

void Content::set_title(std::string title) { this->title = title; }
void Content::set_type(Type type) { this->type = type; }
void Content::set_genre(Genre genre) { this->genre = genre; }
void Content::set_year(int year) { this->year = year; }
void Content::add_views(long views) { this->views += views; }
void Content::set_views(long views) { this->views = views; }
void Content::set_rating(float rating) { if (rating <= 5 && rating >= 0) this->rating = rating; }

void Content::add_rating(float new_rating) { 
    
    if (new_rating < 0.0f || new_rating > 5.0f) return;

    float total_score = (this->rating * this->rating_count) + new_rating;
    this->rating_count++;
    this->rating = total_score / this->rating_count;
    
}

bool content_rating_desc(const Content &a, const Content &b) {
    return a.get_rating() > b.get_rating();
}