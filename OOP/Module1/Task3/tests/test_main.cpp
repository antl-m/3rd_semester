#include "../task3.h"

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE testGraph
#include "boost/test/unit_test.hpp"

#define LOG(x) std::cout << __LINE__ << ": "<< #x << " = " << x <<std::endl

using namespace Task3;

BOOST_AUTO_TEST_SUITE(Task3Tests);

    BOOST_AUTO_TEST_CASE(CommonTest){
        {
            //Gamma, Beta, Gamma, Gamma, Beta, Beta, Alpha, Beta, Alpha, Beta: 9
            Gamma g1;
            Beta g2;
            Gamma g3;
            Gamma g4;
            Beta g5;
            Beta g6;
            Alpha g7;
            Beta g8;
            Alpha g9;
            Beta g10;
            LOG(S);
        }
        LOG(S);
        {
            Alpha a, a1, a2, a3;
            Beta b, b1, b2, b3;
            Gamma g, g1, g2, g3;
            LOG(S);
        }
        LOG(S);
        {

            Alpha a;
            LOG(a.Has2());
            a.CreateAlpha1();
            a.CreateAlpha2();
            LOG(a.Has2());
            Beta b;
            LOG(b.Has1());
            b.CreateBeta1();
            LOG(b.Has1());
            Gamma g;
            LOG(g.Has2());
            g.CreateGamma2();
            LOG(g.Has2());
            LOG(S);
        }
        LOG(S);

        int64_t exp = 0;
        {
            Alpha a;
            a.CreateAlpha2();
            a.Get2().CreateGamma1();
            Beta b;
            Gamma g;
            std::vector<Base*> v = {&g, &b, &a};
            exp = Predict(v);
            LOG(S);
        }
        LOG(S);
        BOOST_CHECK_EQUAL(S, exp);

        for (const auto&[perm, val]: Combinations(1)) {
            std::cout << perm << ": " << val << std::endl;
        }
    }

BOOST_AUTO_TEST_SUITE_END();