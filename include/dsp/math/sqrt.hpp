#ifndef LIBDSP_INCLUDE_DSP_MATH_SQRT_HPP
#define LIBDSP_INCLUDE_DSP_MATH_SQRT_HPP

#include <cmath>

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
#include <quadmath.h>
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

namespace dsp::math {

template <typename T>
constexpr T sqrt(T value);

template <>
constexpr float sqrt<float>(float value) {
    return sqrtf(value);
}

template <>
constexpr double sqrt<double>(double value) {
    return ::sqrt(value);
}

template <>
constexpr long double sqrt<long double>(long double value) {
    return sqrtl(value);
}

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
template <>
constexpr __float128 sqrt<__float128>(__float128 value) {
    return sqrtq(value);
}
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

} /* namespace dsp::math */

#endif /* LIBDSP_INCLUDE_DSP_MATH_SQRT_HPP */