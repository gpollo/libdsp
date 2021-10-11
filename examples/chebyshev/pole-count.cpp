#include <cmath>
#include <iostream>

#include "dsp/filter/chebyshev.hpp"
#include "dsp/utils/frequency-response.hpp"

static constexpr unsigned int POINT_COUNT = 300;
static constexpr float SAMPLING_FREQUENCY = 100.0F;

template <unsigned int N>
struct settings {
    using type = double;

    static constexpr unsigned int POLE_COUNT     = N;
    static constexpr float PERCENT_RIPPLE        = 0.0F;
    static constexpr float SAMPLING_FREQUENCY_HZ = SAMPLING_FREQUENCY;
    static constexpr float CUTOFF_FREQUENCY_HZ   = 45.0F;
};

int main() {
    using filter_chebyshev_2  = dsp::filter::chebyshev::high_pass<settings<2>>;
    using filter_chebyshev_4  = dsp::filter::chebyshev::high_pass<settings<4>>;
    using filter_chebyshev_6  = dsp::filter::chebyshev::high_pass<settings<6>>;
    using filter_chebyshev_8  = dsp::filter::chebyshev::high_pass<settings<8>>;
    using filter_chebyshev_10 = dsp::filter::chebyshev::high_pass<settings<10>>;

    auto gains_chebyshev_2 =
        dsp::utils::frequency_response<POINT_COUNT, filter_chebyshev_2>(1.0, 50.0, SAMPLING_FREQUENCY);
    auto gains_chebyshev_4 =
        dsp::utils::frequency_response<POINT_COUNT, filter_chebyshev_4>(1.0, 50.0, SAMPLING_FREQUENCY);
    auto gains_chebyshev_6 =
        dsp::utils::frequency_response<POINT_COUNT, filter_chebyshev_6>(1.0, 50.0, SAMPLING_FREQUENCY);
    auto gains_chebyshev_8 =
        dsp::utils::frequency_response<POINT_COUNT, filter_chebyshev_8>(1.0, 50.0, SAMPLING_FREQUENCY);
    auto gains_chebyshev_10 =
        dsp::utils::frequency_response<POINT_COUNT, filter_chebyshev_10>(1.0, 50.0, SAMPLING_FREQUENCY);

    std::cout << ">title=Frequency Response vs. Pole Count" << std::endl;
    std::cout << ">x-axis=Frequency [Hz]" << std::endl;
    std::cout << ">y-axis=Gain" << std::endl;
    std::cout << ">x-min=1" << std::endl;
    std::cout << ">x-max=49" << std::endl;
    std::cout << ">y-min=-0.1" << std::endl;
    std::cout << ">y-max=1.1" << std::endl;
    for (unsigned int i = 0; i < POINT_COUNT; i++) {
        auto frequency         = gains_chebyshev_2[i].first;
        auto gain_chebyshev_2  = gains_chebyshev_2[i].second;
        auto gain_chebyshev_4  = gains_chebyshev_4[i].second;
        auto gain_chebyshev_6  = gains_chebyshev_6[i].second;
        auto gain_chebyshev_8  = gains_chebyshev_8[i].second;
        auto gain_chebyshev_10 = gains_chebyshev_10[i].second;
        std::cout << frequency << " " << gain_chebyshev_2 << " " << gain_chebyshev_4 << " " << gain_chebyshev_6 << " "
                  << gain_chebyshev_8 << " " << gain_chebyshev_10 << std::endl;
    }

    return 0;
}