#ifndef LIBDSP_INCLUDE_DSP_WINDOW_NONE_HPP
#define LIBDSP_INCLUDE_DSP_WINDOW_NONE_HPP

#include <array>

namespace dsp::window {

template <typename T, unsigned int N>
struct none_coefficients {
    using type = T;

    static constexpr std::array<T, N> get() {
        std::array<T, N> coefficients{};

        for (unsigned int i = 0; i < N; i++) {
            coefficients[i] = 1;
        }

        return coefficients;
    }
};

} /* namespace dsp::window */

#endif /* LIBDSP_INCLUDE_DSP_WINDOW_NONE_HPP */