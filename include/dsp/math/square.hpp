#ifndef LIBDSP_INCLUDE_DSP_MATH_SQUARE_HPP
#define LIBDSP_INCLUDE_DSP_MATH_SQUARE_HPP

#include <cmath>

namespace dsp::math {

template <typename T, typename I>
constexpr T square(I value) {
    return static_cast<T>(value) * static_cast<T>(value);
}

} /* namespace dsp::math */

#endif /* LIBDSP_INCLUDE_DSP_MATH_SQUARE_HPP */