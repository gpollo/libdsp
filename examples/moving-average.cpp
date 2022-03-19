#include <cmath>
#include <iostream>

#include "dsp/filter/moving-average.hpp"
#include "dsp/utils/frequency-response.hpp"

static constexpr unsigned int POINT_COUNT = 300U;

int main() {
    using filter_5_samples  = dsp::filter::moving_average<double, 5U>;
    using filter_10_samples = dsp::filter::moving_average<double, 10U>;
    using filter_15_samples = dsp::filter::moving_average<double, 15U>;

    auto gains_5_samples  = dsp::utils::frequency_response<POINT_COUNT, filter_5_samples>(1.0, 50.0, 100.0);
    auto gains_10_samples = dsp::utils::frequency_response<POINT_COUNT, filter_10_samples>(1.0, 50.0, 100.0);
    auto gains_15_samples = dsp::utils::frequency_response<POINT_COUNT, filter_15_samples>(1.0, 50.0, 100.0);

    std::cout << ">title=Frequency Response vs. Sample Count" << std::endl;
    std::cout << ">x-axis=Frequency [Hz]" << std::endl;
    std::cout << ">y-axis=Gain" << std::endl;
    std::cout << ">x-min=1" << std::endl;
    std::cout << ">x-max=49" << std::endl;
    std::cout << ">y-min=-0.1" << std::endl;
    std::cout << ">y-max=1.1" << std::endl;
    for (unsigned int i = 0; i < POINT_COUNT; i++) {
        auto frequency       = gains_5_samples[i].first;
        auto gain_5_samples  = gains_5_samples[i].second;
        auto gain_10_samples = gains_10_samples[i].second;
        auto gain_15_samples = gains_15_samples[i].second;
        std::cout << frequency << " " << gain_5_samples << " " << gain_10_samples << " " << gain_15_samples
                  << std::endl;
    }

    return 0;
}