#ifndef LIBDSP_INCLUDE_DSP_UTILS_FREQUENCY_RESPONSE_HPP
#define LIBDSP_INCLUDE_DSP_UTILS_FREQUENCY_RESPONSE_HPP

#include <array>
#include <utility>

#include "dsp/math.hpp"
#include "dsp/maximizer.hpp"
#include "dsp/minimizer.hpp"

namespace dsp::utils {

namespace impl {

template <typename F>
double gain_of(double sampling_frequency, double signal_frequency) {
    using type = typename F::type;

    F filter;
    minimizer<type> min;
    maximizer<type> max;

    auto sampling_period = 1.0 / sampling_frequency;
    auto signal_period   = 1.0 / signal_frequency;

    auto current_sample = 0U;
    while (true) {
        const auto time  = static_cast<type>(sampling_period) * static_cast<type>(current_sample++);
        const auto phase = static_cast<type>(2.0 * math::get_pi<type>() * signal_frequency * time);
        const auto value = math::sin(phase);

        auto output_opt = filter(value);
        if (output_opt.has_value()) {
            break;
        }
    }

    auto sample_count = static_cast<unsigned int>(40.0 * (signal_period / sampling_period));
    for (unsigned int i = 0; i < 10 * sample_count; i++) {
        const auto time  = static_cast<type>(sampling_period) * static_cast<type>(current_sample++);
        const auto phase = static_cast<type>(2.0 * math::get_pi<type>() * signal_frequency * time);
        const auto value = math::sin(phase);

        auto output = filter(value).value();

        min(output);
        max(output);
    }

    auto amplitude = std::max(-min.get().value(), max.get().value());
    return amplitude / 1.0F;
}

} /* namespace impl */

/**
 * This function computes the values of a frequency response graph. Behind the scene,
 * it simulates different sine frequencies and put the signal into the filter.
 *
 * The filter template parameter `F` must provide the following types/methods.
 *
 *    using type = ...;
 *    std::optional<type> operator()(type sample);
 */
template <unsigned int N, typename F>
std::array<std::pair<double, double>, N> frequency_response(double start, double end, double sampling_frequency) {
    std::array<std::pair<double, double>, N> results;

    auto distance = (end - start) / static_cast<double>(N);
    for (unsigned int i = 0; i < N; i++) {
        double signal_frequency = start + distance * static_cast<double>(i);
        double gain             = impl::gain_of<F>(sampling_frequency, signal_frequency);
        results[i]              = std::make_pair(signal_frequency, gain);
    }

    return results;
}

} /* namespace dsp::utils */

#endif /* LIBDSP_INCLUDE_DSP_UTILS_FREQUENCY_RESPONSE_HPP */