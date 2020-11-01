#ifndef MODULE1_TASK2_F_H
#define MODULE1_TASK2_F_H

#include "custom_traits.h"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>


int64_t fact(int64_t x) {
    int64_t res = 1;
    for (int64_t i = 2; i <= x; ++i) {
        res *= i;
    }
    return res;
}

template <typename Integer, std::enable_if_t<std::is_integral<Integer>::value, int> = 0>
int64_t f(Integer x) {
    if (x > 0) {
        return fact(x) % 157;
    } else {
        return (x * x * x) % 257;
    }
}

template <typename Floating, std::enable_if_t<std::is_floating_point<Floating>::value, int> = 0>
int64_t f(Floating x) {
    return static_cast<int64_t>(std::exp(1./std::sin(x))) % 357;
}

template <typename CString, std::enable_if_t<is_cstring<CString>::value, int> = 0>
int64_t f(CString x) {
    static const std::string vowels = "aeiouAEIOU";
    int64_t res = 0;
    for(std::size_t i = 0; i < strlen(x); ++i){
        if(vowels.find(x[i]) != vowels.npos)
            ++res;
    }
    return res;
}

template <typename String, std::enable_if_t<is_string<String>::value, int> = 0>
int64_t f(String x) {
    static const std::string vowels = "aeiouAEIOU";
    int64_t res = 0;
    for(const char i: x){
        if(vowels.find(i) != vowels.npos)
            ++res;
    }
    return res;
}

template <typename Pair, std::enable_if_t<is_pair<Pair>::value, int> = 0>
int64_t f(Pair x){
    return static_cast<int64_t>(pow(f(x.second), f(x.first))) % 557;
}

template <typename T, std::enable_if_t<!is_one_of_overloaded<T>::value, int> = 0>
int64_t f(T x){
    return 7125;
}

template <typename Container,
        std::enable_if_t<is_container<Container>::value && !is_string<Container>::value, int> = 0>
int64_t f(Container x){
    int64_t result = 0;
    for (auto i = x.begin(); std::next(i) != x.end(); ++i) {
        result += f(*i)*f(*std::next(i));
    }
    return result % 757;
}

#endif //MODULE1_TASK2_F_H
