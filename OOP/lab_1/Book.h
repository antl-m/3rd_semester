#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include "Graph.h"

bool operator<(const tm& lhs, const tm& rhs);

class Book {
public:

    friend bool operator<(const Book& lhs, const Book& rhs);

private:
    std::string book_name;
    std::set<std::string> authors;
    tm release_date;
    std::size_t page_count;
    std::string annotation;
};

bool operator<(const Book& lhs, const Book& rhs);

enum class PartLevel {
    MAIN,
    MINOR,
    EPISODIC
};

class Character {
public:
private:
    std::set<std::string> names;
    std::set<Book> books;
    std::map<Book, PartLevel> book_to_plevel;
};

class BookSeries{
public:
private:
};