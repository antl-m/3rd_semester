#ifndef MODULE1_TASK2_CUSTOM_TRAITS_H
#define MODULE1_TASK2_CUSTOM_TRAITS_H

#include <type_traits>
#include <string>

template<typename T>
struct is_string
        : public
          std::is_same<std::string, typename std::decay<T>::type
> {
};

template<typename T>
struct is_cstring
        : public std::disjunction<
                std::is_same<char *, typename std::decay<T>::type>,
                std::is_same<const char *, typename std::decay<T>::type>
> {
};

template<typename T, typename _ = void>
struct is_container : std::false_type {};

template<typename... Ts>
struct is_container_helper {};

template<typename T>
struct is_container<
        T,
        std::conditional_t<
                false,
                is_container_helper<
                        typename T::value_type,
                        typename T::size_type,
                        typename T::allocator_type,
                        typename T::iterator,
                        typename T::const_iterator,
                        decltype(std::declval<T>().size()),
                        decltype(std::declval<T>().begin()),
                        decltype(std::declval<T>().end()),
                        decltype(std::declval<T>().cbegin()),
                        decltype(std::declval<T>().cend())
                >,
                void
        >
> : public std::true_type {};

template<typename T, typename _ = void>
struct is_pair : std::false_type {};

template<typename... Ts>
struct is_pair_helper {};

template<typename T>
struct is_pair<
        T,
        std::conditional_t<
                false,
                is_pair_helper<
                        typename T::first_type,
                        typename T::second_type,
                        decltype(std::declval<T>().first),
                        decltype(std::declval<T>().second)
                >,
                void
        >
> : public std::true_type {};

template<typename T>
struct is_one_of_overloaded
        : public std::disjunction<
                std::is_integral<T>,
                std::is_floating_point<T>,
                is_string<T>,
                is_cstring<T>,
                is_container<T>,
                is_pair<T>
        > {
};

#endif //MODULE1_TASK2_CUSTOM_TRAITS_H
