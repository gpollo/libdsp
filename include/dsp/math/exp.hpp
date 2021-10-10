#ifndef LIBDSP_INCLUDE_DSP_MATH_EXP_HPP
#define LIBDSP_INCLUDE_DSP_MATH_EXP_HPP

#include <cmath>

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
#include <quadmath.h>
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

namespace dsp::math {

template <typename T>
constexpr T exp(T value);

template <>
constexpr float exp<float>(float value) {
    return expf(value);
}

template <>
constexpr double exp<double>(double value) {
    return ::exp(value);
}

template <>
constexpr long double exp<long double>(long double value) {
    return expl(value);
}

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
template <>
__float128 exp<__float128>(__float128 value) {
    return expq(value);
}
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

} /* namespace dsp::math */

#endif /* LIBDSP_INCLUDE_DSP_MATH_EXP_HPP */