#include "task3.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

namespace Task3 {

    int64_t S = 0;

    int64_t Base::Counter = 0;

    Base::Base() : N(++Counter) {}

#define DEFINE_BASE_METHOD(type) void Base::Create##type##1() {              \
                                     if(!base1)                              \
                                         base1 = std::make_unique<type>();   \
                                 }                                           \
                                 void Base::Create##type##2() {              \
                                     if(!base2)                              \
                                         base2 = std::make_unique<type>();   \
                                 }

    DEFINE_BASE_METHOD(Alpha)

    DEFINE_BASE_METHOD(Beta)

    DEFINE_BASE_METHOD(Gamma)

    bool Base::Has1() {
        return static_cast<bool>(base1);
    }

    bool Base::Has2() {
        return static_cast<bool>(base2);
    }

    Base::~Base() {
        S = S / 2 - 3 * N + 15;
    }

    void Base::Calculate(int64_t &cur_S) const {
        cur_S = cur_S / 2 - 3 * N + 15;
    }

    Base &Base::Get1() {
        if (base1)
            return *base1;
        throw std::runtime_error("Get1: inner object doesn't exist");
    }

    Base &Base::Get2() {
        if (base2)
            return *base2;
        throw std::runtime_error("Get2: inner object doesn't exist");
    }

    Alpha::~Alpha() {
        S = S + N;
    }

#define SUBCLASS_CALCULATE_IMPL Base::Calculate(cur_S);       \
                                if (base2)                    \
                                    base2->Calculate(cur_S);  \
                                if (base1)                    \
                                    base1->Calculate(cur_S)

    void Alpha::Calculate(int64_t &cur_S) const {
        cur_S = cur_S + N;
        SUBCLASS_CALCULATE_IMPL;
    }

    Beta::~Beta() {
        S = S - 2 * N;
    }

    void Beta::Calculate(int64_t &cur_S) const {
        cur_S = cur_S - 2 * N;
        SUBCLASS_CALCULATE_IMPL;
    }

    Gamma::~Gamma() {
        S = S + N - 13;
    }

    void Gamma::Calculate(int64_t &cur_S) const {
        cur_S = cur_S + N - 13;
        SUBCLASS_CALCULATE_IMPL;
    }

    struct base {
        explicit base(int64_t N) : N(N) {}

        const int64_t N;

        virtual void calculate(int64_t &cur_S) = 0;

        virtual std::string str() {
            return "Base";
        }
    };

    struct a : base {
        explicit a(int64_t N) : base(N) {}

        void calculate(int64_t &cur_S) override {
            cur_S = cur_S + N;
            cur_S = cur_S / 2 - 3 * N + 15;
        }

        std::string str() override {
            return "Alpha";
        }
    };

    struct b : base {
        explicit b(int64_t N) : base(N) {}

        void calculate(int64_t &cur_S) override {
            cur_S = cur_S - 2 * N;
            cur_S = cur_S / 2 - 3 * N + 15;
        }

        std::string str() override {
            return "Beta";
        }
    };

    struct g : base {
        explicit g(int64_t N) : base(N) {}

        void calculate(int64_t &cur_S) override {
            cur_S = cur_S + N - 13;
            cur_S = cur_S / 2 - 3 * N + 15;
        }

        std::string str() override {
            return "Gamma";
        }
    };

    std::vector<std::vector<std::shared_ptr<base>>> permutations(int64_t size, int64_t N) {
        std::vector<std::vector<std::shared_ptr<base>>> res;
        if (size == 1) {
            return {{std::make_shared<a>(N)},{std::make_shared<b>(N)},{std::make_shared<g>(N)}};
        }
        auto perms = permutations(size - 1, N + 1);
        for (auto &i: std::vector<std::shared_ptr<base>>{std::make_shared<a>(N),
                                                         std::make_shared<b>(N),
                                                         std::make_shared<g>(N)}) {
            for (auto &j: perms) {
                std::vector<std::shared_ptr<base>> temp;
                temp.push_back(i);
                temp.insert(temp.end(), j.begin(), j.end());
                res.push_back(std::move(temp));
            }
        }
        return res;
    }

    std::unordered_map<std::string, int64_t> Combinations(const int64_t M) {
        if(M <= 0)
            return {};
        std::unordered_map<std::string, int64_t> res;
        for (auto &permutation: permutations(M, 1)) {
            std::stringstream ss;
            bool first = true;
            for(auto& obj: permutation){
                ss << (first ? "" : ", ") << obj->str();
                first = false;
            }
            int64_t cur_S = 0;
            for (auto object = permutation.rbegin(); object != permutation.rend(); ++object) {
                (*object)->calculate(cur_S);
            }
            res[ss.str()] = cur_S;
        }
        return res;
    }

} //namespace Task3
