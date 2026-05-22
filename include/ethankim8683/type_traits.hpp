#ifndef ETHANKIM8683_TYPE_TRAITS
#define ETHANKIM8683_TYPE_TRAITS 1

#include <type_traits>
#include <vector>

#include "atcoder/modint"

namespace ethankim8683 {

template <class T>
struct type_container {
  using type = T;
};

// https://stackoverflow.com/a/38853594/19662543
template <class T>
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
template <class T>
using double_width_t = typename double_width<T>::type;

// https://stackoverflow.com/a/16337657
template <class>
struct is_vector : std::false_type {};
template <class T, class S>
struct is_vector<std::vector<T, S>> : std::true_type {};
template <class T>
inline constexpr bool is_vector_v = is_vector<T>::value;
template <class, class>
struct is_vector_of : std::false_type {};
template <class T, class S>
struct is_vector_of<T, std::vector<T, S>> : std::true_type {};
template <class T, class S>
inline constexpr bool is_vector_of_v = is_vector_of<T, S>::value;

template <class T>
struct is_invertible : std::is_floating_point<T> {};
template <int MOD>
struct is_invertible<atcoder::static_modint<MOD>> : std::true_type {};
template <int ID>
struct is_invertible<atcoder::dynamic_modint<ID>> : std::true_type {};
template <class T>
inline constexpr bool is_invertible_v = is_invertible<T>::value;

}  // namespace ethankim8683

#endif  // ETHANKIM8683_TYPE_TRAITS
