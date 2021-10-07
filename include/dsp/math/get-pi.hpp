#ifndef LIBDSP_INCLUDE_DSP_MATH_GET_PI_HPP
#define LIBDSP_INCLUDE_DSP_MATH_GET_PI_HPP

namespace dsp::math {

template <typename T>
constexpr T get_pi();

template <>
constexpr float get_pi<float>() {
    return 3.1415927410125732421875F;
}

template <>
constexpr double get_pi<double>() {
    return 3.141592653589793115997963468544185161590576171875;
}

template <>
constexpr long double get_pi<long double>() {
    return 3.141592653589793238462643383279502797479068098137295573004504331874296718662975536062731407582759857177734375L;
}

#ifdef LIBDSP_LIBQUADMATH_SUPPORT
template <>
constexpr __float128 get_pi<__float128>() {
    return 3.141592653589793238462643383279502797479068098137295573004504331874296718662975536062731407582759857177734375Q;
}
#endif /* LIBDSP_LIBQUADMATH_SUPPORT */

} /* namespace dsp::math */

#endif /* LIBDSP_INCLUDE_DSP_MATH_GET_PI_HPP */