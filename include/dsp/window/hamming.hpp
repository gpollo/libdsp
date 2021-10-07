#ifndef LIBDSP_INCLUDE_DSP_WINDOW_HAMMING_HPP
#define LIBDSP_INCLUDE_DSP_WINDOW_HAMMING_HPP

#include <array>

#include "dsp/math.hpp"

namespace dsp::window {

template <typename T, unsigned int N>
struct hamming_coefficients {
    using type = T;

    static constexpr std::array<T, N> get() {
        std::array<T, N> coefficients{};

        for (unsigned int i = 0; i < N; i++) {
            const auto k1           = static_cast<T>(0.54);
            const auto k2           = static_cast<T>(0.46);
            const auto index        = static_cast<T>(i);
            const auto phase        = static_cast<T>(2.0 * math::get_pi<type>()) * index;
            const auto sample_count = static_cast<T>(N);
            coefficients[i]         = k1 - k2 * math::cos(phase / sample_count);
        }

        return coefficients;
    }
};

} /* namespace dsp::window */

#endif /* LIBDSP_INCLUDE_DSP_WINDOW_HAMMING_HPP */