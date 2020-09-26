#include "Book.h"

bool operator<(const tm& lhs, const tm& rhs){
    return std::vector<int>{lhs.tm_year, lhs.tm_mon, lhs.tm_mday} <
           std::vector<int>{rhs.tm_year, rhs.tm_mon, rhs.tm_mday};
}

bool operator<(const Book& lhs, const Book& rhs){
    return lhs.release_date < rhs.release_date;
}