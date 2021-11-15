#ifndef LIBDSP_INCLUDE_DSP_FILTER_WINDOWED_SINC_HPP
#define LIBDSP_INCLUDE_DSP_FILTER_WINDOWED_SINC_HPP

#include "dsp/filter/convolution.hpp"
#include "dsp/math.hpp"

namespace dsp::filter::windowed_sinc {

namespace impl {

template <typename Settings, bool HighPass>
struct sinc_coefficients {
    using type = typename Settings::type;

    static constexpr unsigned int SAMPLE_COUNT   = Settings::SAMPLE_COUNT;
    static constexpr float SAMPLING_FREQUENCY_HZ = Settings::SAMPLING_FREQUENCY_HZ;
    static constexpr float CUTOFF_FREQUENCY_HZ   = Settings::CUTOFF_FREQUENCY_HZ;
    static constexpr float CUTOFF                = CUTOFF_FREQUENCY_HZ / SAMPLING_FREQUENCY_HZ;

    static_assert(SAMPLE_COUNT % 2 == 1, "sample count must be an odd number");

    static constexpr std::array<type, SAMPLE_COUNT> get() {
        std::array<type, SAMPLE_COUNT> coefficients{};
        type sum = 0;

        for (unsigned int i = 0; i < SAMPLE_COUNT; i++) {
            const auto index = static_cast<type>(i) - static_cast<type>(SAMPLE_COUNT / 2);
            const auto phase = static_cast<type>(2.0 * math::get_pi<type>() * CUTOFF);
            coefficients[i]  = (index == 0) ? (phase) : (math::sin(phase * index) / index);
            sum += coefficients[i];
            coefficients[i] *= (HighPass) ? (-1) : (1);
        }

        for (unsigned int i = 0; i < SAMPLE_COUNT; i++) {
            coefficients[i] /= sum;
        }

        if (HighPass) {
            coefficients[(SAMPLE_COUNT - 1) / 2] += static_cast<type>(1.0);
        }

        return coefficients;
    }
};

template <typename Settings, bool HighPass>
struct windowed_sinc_coefficients {
    using type   = typename Settings::type;
    using window = typename Settings::window;
    using sinc   = sinc_coefficients<Settings, false>;

    static constexpr unsigned int SAMPLE_COUNT = Settings::SAMPLE_COUNT;

    static constexpr std::array<type, SAMPLE_COUNT> get() {
        const std::array<type, SAMPLE_COUNT> WINDOW_COEFFICIENTS = window::get();
        const std::array<type, SAMPLE_COUNT> SINC_COEFFICIENTS   = sinc::get();

        std::array<type, SAMPLE_COUNT> coefficients{};
        type sum = 0;

        for (unsigned int i = 0; i < SAMPLE_COUNT; i++) {
            coefficients[i] = WINDOW_COEFFICIENTS[i] * SINC_COEFFICIENTS[i];
            sum += coefficients[i];
            coefficients[i] *= (HighPass) ? (-1) : (1);
        }

        for (unsigned int i = 0; i < SAMPLE_COUNT; i++) {
            coefficients[i] /= sum;
        }

        if (HighPass) {
            coefficients[(SAMPLE_COUNT - 1) / 2] += static_cast<type>(1.0);
        }

        return coefficients;
    }
};

} /* namespace impl */

/**
 * The template parameter `Settings` must provide the following types/methods.
 *
 *    using type   = ...;
 *    using window = ...;
 *    static constexpr unsigned int SAMPLE_COUNT   = ...;
 *    static constexpr float SAMPLING_FREQUENCY_HZ = ...;
 *    static constexpr float CUTOFF_FREQUENCY_HZ   = ...;
 *
 * This data structure is safe for one writer and multiple readers executing concurrently.
 */
template <typename Settings>
using low_pass =
    convolution<typename Settings::type, Settings::SAMPLE_COUNT, impl::windowed_sinc_coefficients<Settings, false>>;

/**
 * The template parameter `Settings` must provide the following types/methods.
 *
 *    using type   = ...;
 *    using window = ...;
 *    static constexpr unsigned int SAMPLE_COUNT   = ...;
 *    static constexpr float SAMPLING_FREQUENCY_HZ = ...;
 *    static constexpr float CUTOFF_FREQUENCY_HZ   = ...;
 *
 * This data structure is safe for one writer and multiple readers executing concurrently.
 */
template <typename Settings>
using high_pass =
    convolution<typename Settings::type, Settings::SAMPLE_COUNT, impl::windowed_sinc_coefficients<Settings, true>>;

} /* namespace dsp::filter::windowed_sinc */

#endif /* LIBDSP_INCLUDE_DSP_FILTER_WINDOWED_SINC_HPP */