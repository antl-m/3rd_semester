#include "../f.h"

#include <vector>
#include <map>

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE testGraph
#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_SUITE(MainTests);

    BOOST_AUTO_TEST_CASE(IntegralTest){
        auto exp = [](int64_t x){
            if (x > 0) {
                return fact(x) % 157;
            } else {
                return (x * x * x) % 257;
            }
        };

        BOOST_CHECK_EQUAL(f(10), exp(10));
        BOOST_CHECK_EQUAL(f(-10), exp(-10));
        BOOST_CHECK_EQUAL(f(0), exp(0));
    }

    BOOST_AUTO_TEST_CASE(FloatingPointTest){
        auto exp = [](double x) -> int64_t {
            return static_cast<int64_t>(std::exp(1./sin(x))) % 357;
        };

        BOOST_CHECK_EQUAL(f(10.f), exp(10.f));
        BOOST_CHECK_EQUAL(f(-10.f), exp(-10.f));
        BOOST_CHECK_EQUAL(f(0.f), exp(0.f));
    }

    BOOST_AUTO_TEST_CASE(TextStringTest){

        BOOST_CHECK_EQUAL(f("Anatoliy Malibroda"), 8);
        BOOST_CHECK_EQUAL(f("ntl Mlbrd"), 0);
        BOOST_CHECK_EQUAL(f("aaaaaaaaaaaaaaa"), 15);
    }

    BOOST_AUTO_TEST_CASE(PairTest){
        std::pair<std::string, int> p("Anatoliy Malibroda", 3);
        int64_t exp = std::pow(f(p.second), f(p.first));
        exp %= 557;
        BOOST_CHECK_EQUAL(f(p), exp);
    }

    BOOST_AUTO_TEST_CASE(ContainerTest){
        std::vector<int> v = {1, 2, 3, 4, 5};
        int64_t exp = f(1)*f(2)+f(2)*f(3)+f(3)*f(4)+f(4)*f(5);
        exp %= 757;
        BOOST_CHECK_EQUAL(f(v), exp);

        std::map<int, int> m = {{1,2},{3,4},{5,6}};
        std::vector tv = {std::make_pair(1, 2),
                                   std::make_pair(3, 4),
                                   std::make_pair(5, 6)};
        int64_t exp_m = f(tv);
        BOOST_CHECK_EQUAL(f(m), exp_m);
    }

BOOST_AUTO_TEST_SUITE_END();