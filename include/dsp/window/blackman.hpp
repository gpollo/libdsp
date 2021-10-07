#ifndef LIBDSP_INCLUDE_DSP_WINDOW_BLACKMAN_HPP
#define LIBDSP_INCLUDE_DSP_WINDOW_BLACKMAN_HPP

#include <array>

#include "dsp/math.hpp"

namespace dsp::window {

template <typename T, unsigned int N>
struct blackman_coefficients {
    using type = T;

    static constexpr std::array<T, N> get() {
        std::array<T, N> coefficients{};

        for (unsigned int i = 0; i < N; i++) {
            const auto k1           = static_cast<T>(0.42);
            const auto k2           = static_cast<T>(0.50);
            const auto k3           = static_cast<T>(0.08);
            const auto index        = static_cast<T>(i);
            const auto phase1       = static_cast<T>(2.0 * math::get_pi<type>()) * index;
            const auto phase2       = static_cast<T>(4.0 * math::get_pi<type>()) * index;
            const auto sample_count = static_cast<T>(N - ((N % 2 == 0U) ? 0U : 1U));
            coefficients[i] = k1 - k2 * math::cos(phase1 / sample_count) + k3 * math::cos(phase2 / sample_count);
        }

        return coefficients;
    }
};

} /* namespace dsp::window */

#endif /* LIBDSP_INCLUDE_DSP_WINDOW_BLACKMAN_HPP */