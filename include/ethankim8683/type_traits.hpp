#ifndef ETHANKIM8683_TYPE_TRAITS
#define ETHANKIM8683_TYPE_TRAITS

#include <type_traits>
#include <vector>

#include "atcoder/modint.hpp"

template <typename T>
struct type_container {
  using type = T;
};

// https://stackoverflow.com/a/38853594/19662543
template <typename T>
struct double_width;
template <>
struct double_width<char> : type_container<short> {};
template <>
struct double_width<short> : type_container<int> {};
template <>
struct double_width<int> : type_container<long long> {};
template <>
struct double_width<long> : type_container<long long> {};
template <>
struct double_width<long long> : type_container<__int128> {};
template <>
struct double_width<unsigned char> : type_container<unsigned short> {};
template <>
struct double_width<unsigned short> : type_container<unsigned int> {};
template <>
struct double_width<unsigned int> : type_container<unsigned long long> {};
template <>
struct double_width<unsigned long> : type_container<unsigned long long> {};
template <>
struct double_width<unsigned long long> : type_container<unsigned __int128> {};
template <>
struct double_width<float> : type_container<double> {};
template <>
struct double_width<double> : type_container<long double> {};
template <int MOD>
struct double_width<atcoder::static_modint<MOD>>
    : type_container<atcoder::static_modint<MOD>> {};
template <int ID>
struct double_width<atcoder::dynamic_modint<ID>>
    : type_container<atcoder::dynamic_modint<ID>> {};

// https://stackoverflow.com/a/16337657
template <typename>
struct is_vector : std::false_type {};
template <typename T, typename S>
struct is_vector<std::vector<T, S>> : std::true_type {};
template <typename, typename>
struct is_vector_of : std::false_type {};
template <typename T, typename S>
struct is_vector_of<T, std::vector<T, S>> : std::true_type {};

#endif  // ETHANKIM8683_TYPE_TRAITS
