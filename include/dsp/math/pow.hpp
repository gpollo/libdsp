#ifndef LIBDSP_INCLUDE_DSP_MATH_POW_HPP
#define LIBDSP_INCLUDE_DSP_MATH_POW_HPP

#include <cmath>

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
#include <quadmath.h>
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

namespace dsp::math {

template <typename T>
constexpr T pow(T x, T y);

template <>
constexpr float pow<float>(float x, float y) {
    return powf(x, y);
}

template <>
constexpr double pow<double>(double x, double y) {
    return ::pow(x, y);
}

template <>
constexpr long double pow<long double>(long double x, long double y) {
    return powl(x, y);
}

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
template <>
__float128 pow<__float128>(__float128 x, __float128 y) {
    return powq(x, y);
}
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

} /* namespace dsp::math */

#endif /* LIBDSP_INCLUDE_DSP_MATH_POW_HPP */