#ifndef LIBDSP_INCLUDE_DSP_MATH_SIN_HPP
#define LIBDSP_INCLUDE_DSP_MATH_SIN_HPP

#include <cmath>

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
#include <quadmath.h>
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

namespace dsp::math {

template <typename T>
constexpr T sin(T value);

template <>
constexpr float sin<float>(float value) {
    return sinf(value);
}

template <>
constexpr double sin<double>(double value) {
    return ::sin(value);
}

template <>
constexpr long double sin<long double>(long double value) {
    return sinl(value);
}

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
template <>
__float128 sin<__float128>(__float128 value) {
    return sinq(value);
}
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

} /* namespace dsp::math */

#endif /* LIBDSP_INCLUDE_DSP_MATH_SIN_HPP */