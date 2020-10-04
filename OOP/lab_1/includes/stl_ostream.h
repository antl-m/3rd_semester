#ifndef STL_OSTREAM_H
#define STL_OSTREAM_H

#include <ostream>
#include <vector>
#include <set>
#include <map>

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::set<T> &s) {
    out << "{ ";
    bool first = true;
    for (const auto &item: s) {
        if (first) {
            out << item;
            first = false;
        } else {
            out << ", " << item;
        }
    }
    out << " }";
    return out;
}

template<typename K, typename V>
std::ostream &operator<<(std::ostream &out, const std::map<K, V> &m) {
    out << "{ ";
    bool first = true;
    for (const auto &[key, val]: m) {
        if (first) {
            out << key << ": " << val;
            first = false;
        } else {
            out << " ," << key << ": " << val;
        }
    }
    out << " }";
    return out;
}


#endif //STL_OSTREAM_H
