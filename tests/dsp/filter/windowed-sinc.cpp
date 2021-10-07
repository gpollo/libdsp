#include <assert.h>
#include <tgmath.h>

#include <dsp/filter/windowed-sinc.hpp>
#include <dsp/utils/frequency-response.hpp>
#include <dsp/window/blackman.hpp>

template <typename T>
static bool almost_equal(T value, T expected, T epsilon = 0.00001) {
    return (std::abs(value - expected) < epsilon);
}

template <typename T, unsigned int N>
struct settings {
    using type   = T;
    using window = dsp::window::blackman_coefficients<T, N>;

    static constexpr unsigned int SAMPLE_COUNT   = N;
    static constexpr float SAMPLING_FREQUENCY_HZ = static_cast<type>(100);
    static constexpr float CUTOFF_FREQUENCY_HZ   = static_cast<type>(1);
};

static void test_frequency_response() {
    using filter_settings = settings<float, 27>;
    using filter          = dsp::filter::windowed_sinc::low_pass<filter_settings>;

    auto gains = dsp::utils::frequency_response<20, filter>(1, 50, filter_settings::SAMPLING_FREQUENCY_HZ);

    assert(almost_equal(gains[0].first, 1.0000, 0.0001));
    assert(almost_equal(gains[1].first, 3.4500, 0.0001));
    assert(almost_equal(gains[2].first, 5.9000, 0.0001));
    assert(almost_equal(gains[3].first, 8.3500, 0.0001));
    assert(almost_equal(gains[4].first, 10.8000, 0.0001));
    assert(almost_equal(gains[5].first, 13.2500, 0.0001));
    assert(almost_equal(gains[6].first, 15.7000, 0.0001));
    assert(almost_equal(gains[7].first, 18.1500, 0.0001));
    assert(almost_equal(gains[8].first, 20.6000, 0.0001));
    assert(almost_equal(gains[9].first, 23.0500, 0.0001));
    assert(almost_equal(gains[10].first, 25.5000, 0.0001));
    assert(almost_equal(gains[11].first, 27.9500, 0.0001));
    assert(almost_equal(gains[12].first, 30.4000, 0.0001));
    assert(almost_equal(gains[13].first, 32.8500, 0.0001));
    assert(almost_equal(gains[14].first, 35.3000, 0.0001));
    assert(almost_equal(gains[15].first, 37.7500, 0.0001));
    assert(almost_equal(gains[16].first, 40.2000, 0.0001));
    assert(almost_equal(gains[17].first, 42.6500, 0.0001));
    assert(almost_equal(gains[18].first, 45.1000, 0.0001));
    assert(almost_equal(gains[19].first, 47.5500, 0.0001));

    assert(almost_equal(gains[0].second, 0.9671, 0.0001));
    assert(almost_equal(gains[1].second, 0.6659, 0.0001));
    assert(almost_equal(gains[2].second, 0.2853, 0.0001));
    assert(almost_equal(gains[3].second, 0.0616, 0.0001));
    assert(almost_equal(gains[4].second, 0.0028, 0.0001));
    assert(almost_equal(gains[5].second, 0.0010, 0.0001));
    assert(almost_equal(gains[6].second, 0.0002, 0.0001));
    assert(almost_equal(gains[7].second, 0.0007, 0.0001));
    assert(almost_equal(gains[8].second, 0.0005, 0.0001));
    assert(almost_equal(gains[9].second, 0.0000, 0.0001));
    assert(almost_equal(gains[10].second, 0.0003, 0.0001));
    assert(almost_equal(gains[11].second, 0.0002, 0.0001));
    assert(almost_equal(gains[12].second, 0.0001, 0.0001));
    assert(almost_equal(gains[13].second, 0.0001, 0.0001));
    assert(almost_equal(gains[14].second, 0.0000, 0.0001));
    assert(almost_equal(gains[15].second, 0.0000, 0.0001));
    assert(almost_equal(gains[16].second, 0.0000, 0.0001));
    assert(almost_equal(gains[17].second, 0.0000, 0.0001));
    assert(almost_equal(gains[18].second, 0.0000, 0.0001));
    assert(almost_equal(gains[19].second, 0.0000, 0.0001));
}

int main() {
    test_frequency_response();

    return 0;
}