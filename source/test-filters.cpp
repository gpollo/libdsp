#include <cmath>
#include <iostream>

#include "dsp/filter/windowed-sinc.hpp"
#include "dsp/utils/frequency-response.hpp"
#include "dsp/window/blackman.hpp"
#include "dsp/window/hamming.hpp"
#include "dsp/window/none.hpp"

#include "dsp/filter/chebyshev.hpp"

static constexpr float SAMPLING_FREQUENCY = 100;
static constexpr unsigned int POINT_COUNT = 300;

template <typename T, unsigned int N, typename W>
struct window_setting {
    using type   = T;
    using window = W;

    static constexpr unsigned int SAMPLE_COUNT   = N;
    static constexpr float SAMPLING_FREQUENCY_HZ = static_cast<type>(SAMPLING_FREQUENCY);
    static constexpr float CUTOFF_FREQUENCY_HZ   = static_cast<type>(10);
};

int main() {
    using window_blackman = window_setting<float, 7, dsp::window::blackman_coefficients<float, 7>>;
    using window_hamming  = window_setting<float, 7, dsp::window::hamming_coefficients<float, 7>>;
    using window_none     = window_setting<float, 7, dsp::window::none_coefficients<float, 7>>;

    using filter_blackman = dsp::filter::windowed_sinc::high_pass<window_blackman>;
    using filter_hamming  = dsp::filter::windowed_sinc::high_pass<window_hamming>;
    using filter_none     = dsp::filter::windowed_sinc::high_pass<window_none>;

    auto gains_blackman = dsp::utils::frequency_response<POINT_COUNT, filter_blackman>(1.0, 50.0, SAMPLING_FREQUENCY);
    auto gains_hamming  = dsp::utils::frequency_response<POINT_COUNT, filter_hamming>(1.0, 50.0, SAMPLING_FREQUENCY);
    auto gains_none     = dsp::utils::frequency_response<POINT_COUNT, filter_none>(1.0, 50.0, SAMPLING_FREQUENCY);

    std::cout << ">title=Frequency Response vs. Window Type" << std::endl;
    std::cout << ">x-axis=Frequency [Hz]" << std::endl;
    std::cout << ">y-axis=Gain" << std::endl;
    std::cout << ">x-min=1" << std::endl;
    std::cout << ">x-max=49" << std::endl;
    std::cout << ">y-min=-0.1" << std::endl;
    std::cout << ">y-max=1.1" << std::endl;
    for (unsigned int i = 0; i < POINT_COUNT; i++) {
        auto frequency     = gains_blackman[i].first;
        auto gain_blackman = gains_blackman[i].second;
        auto gain_hamming  = gains_hamming[i].second;
        auto gain_none     = gains_none[i].second;
        std::cout << frequency << " " << gain_blackman << " " << gain_hamming << " " << gain_none << std::endl;
    }

    return 0;
}