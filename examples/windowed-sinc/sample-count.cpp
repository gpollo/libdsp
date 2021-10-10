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
    static constexpr float CUTOFF_FREQUENCY_HZ   = static_cast<type>(25);
};

int main() {
    using window_blackman11 = window_setting<float, 7, dsp::window::blackman_coefficients<float, 7>>;
    using window_blackman27 = window_setting<float, 27, dsp::window::blackman_coefficients<float, 27>>;
    using window_blackman47 = window_setting<float, 47, dsp::window::blackman_coefficients<float, 47>>;

    using filter_blackman11 = dsp::filter::windowed_sinc::high_pass<window_blackman11>;
    using filter_blackman27 = dsp::filter::windowed_sinc::high_pass<window_blackman27>;
    using filter_blackman47 = dsp::filter::windowed_sinc::high_pass<window_blackman47>;

    auto gains_blackman11 =
        dsp::utils::frequency_response<POINT_COUNT, filter_blackman11>(1.0, 50.0, SAMPLING_FREQUENCY);
    auto gains_blackman27 =
        dsp::utils::frequency_response<POINT_COUNT, filter_blackman27>(1.0, 50.0, SAMPLING_FREQUENCY);
    auto gains_blackman47 =
        dsp::utils::frequency_response<POINT_COUNT, filter_blackman47>(1.0, 50.0, SAMPLING_FREQUENCY);

    std::cout << ">title=Frequency Response vs. Sample Count" << std::endl;
    std::cout << ">x-axis=Frequency [Hz]" << std::endl;
    std::cout << ">y-axis=Gain" << std::endl;
    std::cout << ">x-min=1" << std::endl;
    std::cout << ">x-max=49" << std::endl;
    std::cout << ">y-min=-0.1" << std::endl;
    std::cout << ">y-max=1.1" << std::endl;
    for (unsigned int i = 0; i < POINT_COUNT; i++) {
        auto frequency       = gains_blackman11[i].first;
        auto gain_blackman11 = gains_blackman11[i].second;
        auto gain_blackman27 = gains_blackman27[i].second;
        auto gain_blackman47 = gains_blackman47[i].second;
        std::cout << frequency << " " << gain_blackman11 << " " << gain_blackman27 << " " << gain_blackman47
                  << std::endl;
    }

    return 0;
}