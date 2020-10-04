#include "../Book.h"

#define BOOST_TEST_MODULE testBook
#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_CASE (Test){
    BOOST_REQUIRE_EQUAL(5-1, 3+1);
}