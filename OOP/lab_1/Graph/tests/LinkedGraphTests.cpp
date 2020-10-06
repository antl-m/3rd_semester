#include "../Graph.h"
#include <string>

#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_SUITE(LinkedGraphTest);

    BOOST_AUTO_TEST_CASE (pushing_vertex_test) {
        LinkedGraph<std::string, double> g;
        std::map<std::string, std::set<Node<std::string, double>>> exp;
        std::stringstream g_ss;
        std::stringstream exp_ss;

        g.push_vertex("Yuzhne");
        exp["Yuzhne"];

        g_ss << g;
        exp_ss << exp;

        BOOST_CHECK_EQUAL(g_ss.str(), exp_ss.str());

        g_ss.clear();
        exp_ss.clear();

        g.push_vertex("Odessa");
        exp["Odessa"];

        g_ss << g;
        exp_ss << exp;
        BOOST_CHECK_EQUAL(g_ss.str(), exp_ss.str());
    }

    BOOST_AUTO_TEST_CASE (pushing_vertex_twice_test) {
        LinkedGraph<std::string, double> g;
        std::map<std::string, std::set<Node<std::string, double>>> exp;
        std::stringstream g_ss;
        std::stringstream exp_ss;

        g.push_vertex("Yuzhne");
        exp["Yuzhne"];

        g.push_vertex("Yuzhne");
        exp["Yuzhne"];

        g_ss << g;
        exp_ss << exp;
        BOOST_CHECK_EQUAL(g_ss.str(), exp_ss.str());
    }

    BOOST_AUTO_TEST_CASE (pushing_edge_test) {
        LinkedGraph<std::string, double> g;
        std::map<std::string, std::set<Node<std::string, double>>> exp;
        std::stringstream g_ss;
        std::stringstream exp_ss;

        g.push_vertex("Yuzhne");
        g.push_vertex("Odessa");
        g.push_edge(45.7, "Yuzhne", "Odessa");
        exp["Yuzhne"].insert({"Odessa", 45.7});
        exp["Odessa"].insert({"Yuzhne", 45.7});

        g_ss << g;
        exp_ss << exp;
        BOOST_CHECK_EQUAL(g_ss.str(), exp_ss.str());
    }

    BOOST_AUTO_TEST_CASE (pushing_edge_twice_test) {
        LinkedGraph<std::string, double> g;
        g.push_vertex("Yuzhne");
        g.push_vertex("Odessa");
        g.push_edge(32.5, "Yuzhne", "Odessa");

        BOOST_REQUIRE_THROW(g.push_edge(36, "Yuzhne", "Odessa"), GraphExc);
    }

    BOOST_AUTO_TEST_CASE (connectivity_test) {
        LinkedGraph<std::string, double> g;
        g.push_vertex("Yuzhne");
        g.push_vertex("Odessa");

        BOOST_CHECK(!g.connectivity());

        g.push_edge(32.5, "Yuzhne", "Odessa");

        BOOST_CHECK(g.connectivity());
    }

    BOOST_AUTO_TEST_CASE(length_ariphmetic_test) {
        LinkedGraph<std::string, double> g;
        g.push_vertex("Yuzhne");
        g.push_vertex("Odessa");

        BOOST_CHECK(g.length("Yuzhne", "Odessa") == std::vector<double>{});

        g.push_edge(40.5, "Yuzhne", "Odessa");

        BOOST_CHECK(g.length("Yuzhne", "Odessa")[0] == 40.5);

        g.push_vertex("Dofinivka");
        g.push_edge(15.2, "Dofinivka", "Yuzhne");
        g.push_edge(11.7, "Dofinivka", "Odessa");

        BOOST_CHECK_CLOSE(g.length("Yuzhne", "Odessa")[0], 26.9, 0.00001);
    }

    BOOST_AUTO_TEST_CASE(length__not_ariphmetic_test) {
        LinkedGraph<std::string, std::string> g;
        g.push_vertex("Yuzhne");
        g.push_vertex("Odessa");

        BOOST_CHECK(g.length("Yuzhne", "Odessa") == std::vector<std::string>{});

        g.push_edge("a", "Yuzhne", "Odessa");

        BOOST_CHECK(g.length("Yuzhne", "Odessa") == std::vector<std::string>{"a"});

        g.push_vertex("Dofinivka");
        g.push_edge("b", "Dofinivka", "Yuzhne");
        g.push_edge("c", "Dofinivka", "Odessa");

        BOOST_CHECK(g.length("Yuzhne", "Odessa") == std::vector<std::string>{"a"});
        BOOST_CHECK(g.length("Yuzhne", "Dofinivka") == std::vector<std::string>{"b"});
        BOOST_CHECK(g.length("Odessa", "Dofinivka") == std::vector<std::string>{"c"});
    }

BOOST_AUTO_TEST_SUITE_END();