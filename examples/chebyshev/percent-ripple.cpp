#include <cmath>
#include <iostream>

#include "dsp/filter/chebyshev.hpp"
#include "dsp/utils/frequency-response.hpp"

static constexpr unsigned int POINT_COUNT = 300;
static constexpr float SAMPLING_FREQUENCY = 100.0F;

template <unsigned int N>
struct settings {
    using type = double;

    static constexpr unsigned int POLE_COUNT     = 4;
    static constexpr float PERCENT_RIPPLE        = static_cast<float>(N) / 100.0F;
    static constexpr float SAMPLING_FREQUENCY_HZ = SAMPLING_FREQUENCY;
    static constexpr float CUTOFF_FREQUENCY_HZ   = 15.0F;
};

int main() {
    using filter_chebyshev_0_0_percent = dsp::filter::chebyshev::low_pass<settings<0>>;
    using filter_chebyshev_0_5_percent = dsp::filter::chebyshev::low_pass<settings<5>>;
    using filter_chebyshev_5_0_percent = dsp::filter::chebyshev::low_pass<settings<50>>;

    auto gains_chebyshev_0_0_percent =
        dsp::utils::frequency_response<POINT_COUNT, filter_chebyshev_0_0_percent>(1.0, 50.0, SAMPLING_FREQUENCY);
    auto gains_chebyshev_0_5_percent =
        dsp::utils::frequency_response<POINT_COUNT, filter_chebyshev_0_5_percent>(1.0, 50.0, SAMPLING_FREQUENCY);
    auto gains_chebyshev_5_0_percent =
        dsp::utils::frequency_response<POINT_COUNT, filter_chebyshev_5_0_percent>(1.0, 50.0, SAMPLING_FREQUENCY);

    std::cout << ">title=Frequency Response vs. Percent Ripple" << std::endl;
    std::cout << ">x-axis=Frequency [Hz]" << std::endl;
    std::cout << ">y-axis=Gain" << std::endl;
    std::cout << ">x-min=1" << std::endl;
    std::cout << ">x-max=49" << std::endl;
    std::cout << ">y-min=-0.1" << std::endl;
    std::cout << ">y-max=1.1" << std::endl;
    for (unsigned int i = 0; i < POINT_COUNT; i++) {
        auto frequency                  = gains_chebyshev_0_0_percent[i].first;
        auto gain_chebyshev_0_0_percent = gains_chebyshev_0_0_percent[i].second;
        auto gain_chebyshev_0_5_percent = gains_chebyshev_0_5_percent[i].second;
        auto gain_chebyshev_5_0_percent = gains_chebyshev_5_0_percent[i].second;
        std::cout << frequency << " " << gain_chebyshev_0_0_percent << " " << gain_chebyshev_0_5_percent << " "
                  << gain_chebyshev_5_0_percent << std::endl;
    }

    return 0;
}