#pragma once
#include <concepts>
#include <utility>

namespace mysort
{

template <class _Ty>
concept IsTuple = requires(_Ty t) { std::tuple_size<_Ty>::value; };

}  // namespace mysort