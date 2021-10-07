#ifndef LIBDSP_INCLUDE_DSP_MATH_TAN_HPP
#define LIBDSP_INCLUDE_DSP_MATH_TAN_HPP

#include <cmath>

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
#include <quadmath.h>
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

namespace dsp::math {

template <typename T>
constexpr T tan(T value);

template <>
constexpr float tan<float>(float value) {
    return tanf(value);
}

template <>
constexpr double tan<double>(double value) {
    return ::tan(value);
}

template <>
constexpr long double tan<long double>(long double value) {
    return tanl(value);
}

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
template <>
constexpr __float128 tan<__float128>(__float128 value) {
    return tanq(value);
}
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

} /* namespace dsp::math */

#endif /* LIBDSP_INCLUDE_DSP_MATH_TAN_HPP */