#include "../Server.h"

#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_SUITE(TestShortestWay);

    BOOST_AUTO_TEST_CASE(Test) {
        using namespace SocialNet;
        Server s;
        auto tolik_id = s.AddUser("Anatolii", "Malibroda");
        auto dima_id = s.AddUser("Dmytro", "Sukovanchenko");
        auto arkash_id = s.AddUser("Arkadii", "Tsyganov");
        auto yegor_id = s.AddUser("Yegor", "Grushevyi");

        s.UserAddFriend(tolik_id, dima_id);
        s.UserAddFriend(tolik_id, yegor_id);
        s.UserAddFriend(dima_id, yegor_id);
        s.UserAddFriend(dima_id, arkash_id);

        std::vector<std::size_t> exp = {1, 2};
        auto a = s.ShortestWay(tolik_id, arkash_id);
        BOOST_CHECK(a == exp);
    }

BOOST_AUTO_TEST_SUITE_END();