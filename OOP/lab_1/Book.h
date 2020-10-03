#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include "Graph.h"
#include "stl_ostream.h"

bool operator<(const tm &lhs, const tm &rhs);

std::ostream &operator<<(std::ostream &out, const tm &t);


class Book {
public:

    friend bool operator<(const Book &lhs, const Book &rhs);

    friend std::ostream &operator<<(std::ostream &out, const Book &b);

private:
    std::string book_name;
    std::set<std::string> authors;
    tm release_date;
    std::size_t page_count;
    std::string annotation;
};


enum class PartLevel {
    MAIN,
    MINOR,
    EPISODIC
};

std::ostream &operator<<(std::ostream &out, PartLevel i);

class Character {
public:
    std::set<Book> main_books() const;

    friend std::ostream &operator<<(std::ostream &out, const Character &c);

private:
    std::set<std::string> names;
    std::set<Book> books;
    std::map<Book, PartLevel> book_to_plevel;
};

class BookSeries {
public:
    void insert_book(const Book &book);

    void insert_character(const Character &character, const Book &book1, const Book &book2);

private:
    MatrixGraph<Book, Character> data;
};

#endif //BOOK_H