#include "Book.h"

bool operator<(const tm& lhs, const tm& rhs){
    return std::vector<int>{lhs.tm_year, lhs.tm_mon, lhs.tm_mday} <
           std::vector<int>{rhs.tm_year, rhs.tm_mon, rhs.tm_mday};
}

bool operator<(const Book& lhs, const Book& rhs){
    return lhs.release_date < rhs.release_date;
}

std::ostream &operator<<(std::ostream &out, const Book &b) {
    out << std::endl;
    out << "Book: " << b.book_name << std::endl;
    out << "Authors: " << b.authors << std::endl;
    out << "Release date: " << b.release_date << std::endl;
    out << "Pages: " << b.page_count << std::endl;
    out << "Annotation: " << b.annotation << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const tm &t) {
    out << std::setw(2) << std::setfill('0') << t.tm_mday
        << std::setw(2) << std::setfill('0') << t.tm_mon
        << std::setw(4) << std::setfill('0') << t.tm_year;
    return out;
}

void BookSeries::insert_book(const Book &book) {
    data.push_vertex(book);
}

void BookSeries::insert_character(const Character &character, const Book &book1, const Book &book2) {
    auto char_books = character.main_books();
    if (char_books.count(book1) && char_books.count(book2)) {
        data.push_edge(character, book1, book2);
        return;
    }
    std::stringstream message;
    message << "insert_character: books " << book1 << " and " << book2
            << " aren't connected with character " << character << ".";
    throw std::logic_error(message.str());
}

std::set<Book> Character::main_books() const {
    std::set<Book> res;
    for(const auto& [book, lvl]: book_to_plevel){
        if(lvl != PartLevel::EPISODIC)
            res.insert(book);
    }
    return res;
}

std::ostream &operator<<(std::ostream &out, const Character &c) {
    out << std::endl;
    out << "Names: " << c.names << std::endl;
    out << "Books: " << c.books << std::endl;
    out << "Part level in books: " << c.book_to_plevel <<std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, PartLevel i) {
    switch (i) {
        case PartLevel::MAIN:
            out << "main";
            break;
        case PartLevel::MINOR:
            out << "minor";
            break;
        case PartLevel::EPISODIC:
            out << "episodic";
            break;
    }
    return out;
}
