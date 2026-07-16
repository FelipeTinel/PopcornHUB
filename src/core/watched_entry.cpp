#include "core/watched_entry.hpp"

WatchedEntry::WatchedEntry(): id(0), title(""), type(Type::MOVIE), genre(Genre::ACTION), watch_count(0) {}

WatchedEntry::WatchedEntry(int id, std::string title, Type type, Genre::Value genre, long watch_count):
    id(id), title(title), type(type), genre(genre), watch_count(watch_count) {}

int WatchedEntry::get_id() const { return id; }
std::string WatchedEntry::get_title() const { return title; }
Type WatchedEntry::get_type() const { return type; }
Genre::Value WatchedEntry::get_genre() const { return genre; }
long WatchedEntry::get_watch_count() const { return watch_count; }

void WatchedEntry::add_watch() { watch_count++; }

bool watched_desc(const WatchedEntry &a, const WatchedEntry &b) {
    return a.get_watch_count() > b.get_watch_count();
}
