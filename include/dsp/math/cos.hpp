#ifndef LIBDSP_INCLUDE_DSP_MATH_COS_HPP
#define LIBDSP_INCLUDE_DSP_MATH_COS_HPP

#include <cmath>

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
#include <quadmath.h>
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

namespace dsp::math {

template <typename T>
constexpr T cos(T value);

template <>
constexpr float cos<float>(float value) {
    return cosf(value);
}

template <>
constexpr double cos<double>(double value) {
    return ::cos(value);
}

template <>
constexpr long double cos<long double>(long double value) {
    return cosl(value);
}

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
template <>
constexpr __float128 cos<__float128>(__float128 value) {
    return cosq(value);
}
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

} /* namespace dsp::math */

#endif /* LIBDSP_INCLUDE_DSP_MATH_COS_HPP */