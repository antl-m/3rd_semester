#ifndef MODULE1_TASK3_TASK3_H
#define MODULE1_TASK3_TASK3_H

#include "../Task2/custom_traits.h"

#include <cstdint>
#include <memory>
#include <unordered_map>

namespace Task3 {

    extern int64_t S;

    class Base;

    template<typename T>
    struct is_base_ptr
            : public std::disjunction<
                    std::is_same<Base *, typename std::decay<T>::type>,
                    std::is_same<const Base *, typename std::decay<T>::type>,
                    std::is_same<std::unique_ptr<Base>, typename std::decay<T>::type>,
                    std::is_same<const std::unique_ptr<Base>, typename std::decay<T>::type>,
                    std::is_same<std::shared_ptr<Base>, typename std::decay<T>::type>,
                    std::is_same<const std::shared_ptr<Base>, typename std::decay<T>::type>
            > {
    };

#define DECLARE_BASE_METHOD(type) void Create##type##1(); \
                                  void Create##type##2()

    class Base {
    public:
        Base();

        DECLARE_BASE_METHOD(Alpha);

        DECLARE_BASE_METHOD(Beta);

        DECLARE_BASE_METHOD(Gamma);

        bool Has1();

        bool Has2();

        Base& Get1();

        Base& Get2();

        virtual ~Base() = 0;

        virtual void Calculate(int64_t &cur_S) const;

    protected:

        static int64_t Counter;
        const int64_t N;

        std::unique_ptr<Base> base1, base2;

        template<typename Container,
                std::enable_if_t<is_container<Container>::value &&
                                 is_base_ptr<typename Container::value_type>::value, int> = 0>
        friend int64_t Predict(const Container &c) {
            int64_t cur_S = S;
            for (const auto &ptr: c) {
                ptr->Calculate(cur_S);
            }
            return cur_S;
        }
    };

#define DECLARE_SUBCLASS(type) class type : public Base {                          \
                               public:                                             \
                                   void Calculate(int64_t& cur_S) const override;  \
                                   ~type() override;                               \
                               }

    DECLARE_SUBCLASS(Alpha);

    DECLARE_SUBCLASS(Beta);

    DECLARE_SUBCLASS(Gamma);

    std::unordered_map<std::string, int64_t> Combinations(int64_t M);

} //namespace Task3


#endif //MODULE1_TASK3_TASK3_H
