#ifndef OBS_BSTYPE_HPP
#define OBS_BSTYPE_HPP

#include <cinttypes>

namespace obs::types {
template <typename... Ts> struct type_list {};

template <std::size_t I, typename L> struct type_list_at {};

template <std::size_t I, typename T, typename... T1>
struct type_list_at<I, type_list<T, T1...>> {
  using type = typename type_list_at<I - 1, type_list<T1...>>::type;
};

template <typename T, typename... T1>
struct type_list_at<0, type_list<T, T1...>> {
  using type = T;
};
} // namespace obs::types

#endif
