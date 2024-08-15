#pragma once

#include <type_traits>

template <class T>
concept IsArithmetic = std::is_arithmetic_v<T>;