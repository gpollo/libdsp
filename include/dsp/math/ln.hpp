#ifndef LIBDSP_INCLUDE_DSP_MATH_LN_HPP
#define LIBDSP_INCLUDE_DSP_MATH_LN_HPP

#include <cmath>

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
#include <quadmath.h>
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

namespace dsp::math {

template <typename T>
constexpr T ln(T value);

template <>
constexpr float ln<float>(float value) {
    return logf(value);
}

template <>
constexpr double ln<double>(double value) {
    return log(value);
}

template <>
constexpr long double ln<long double>(long double value) {
    return logl(value);
}

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
template <>
constexpr __float128 ln<__float128>(__float128 value) {
    return logq(value);
}
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

} /* namespace dsp::math */

#endif /* LIBDSP_INCLUDE_DSP_MATH_LN_HPP */