#include <assert.h>
#include <tgmath.h>

#include <dsp/filter/all-pass.hpp>
#include <dsp/utils/frequency-response.hpp>

template <typename T>
static bool almost_equal(T value, T expected, T epsilon = 0.00001) {
    return (std::abs(value - expected) < epsilon);
}

static void test_frequency_response() {
    using filter = dsp::filter::all_pass<float>;
    auto gains   = dsp::utils::frequency_response<20, filter>(1.0F, 50.0F, 100.0F);

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

    assert(almost_equal(gains[0].second, 1.0000, 0.0001));
    assert(almost_equal(gains[1].second, 1.0000, 0.0001));
    assert(almost_equal(gains[2].second, 1.0000, 0.0001));
    assert(almost_equal(gains[3].second, 1.0000, 0.0001));
    assert(almost_equal(gains[4].second, 1.0000, 0.0001));
    assert(almost_equal(gains[5].second, 1.0000, 0.0001));
    assert(almost_equal(gains[6].second, 1.0000, 0.0001));
    assert(almost_equal(gains[7].second, 1.0000, 0.0001));
    assert(almost_equal(gains[8].second, 1.0000, 0.0001));
    assert(almost_equal(gains[9].second, 1.0000, 0.0001));
    assert(almost_equal(gains[10].second, 1.0000, 0.0001));
    assert(almost_equal(gains[11].second, 1.0000, 0.0001));
    assert(almost_equal(gains[12].second, 1.0000, 0.0001));
    assert(almost_equal(gains[13].second, 1.0000, 0.0001));
    assert(almost_equal(gains[14].second, 1.0000, 0.0001));
    assert(almost_equal(gains[15].second, 1.0000, 0.0001));
    assert(almost_equal(gains[16].second, 1.0000, 0.0001));
    assert(almost_equal(gains[17].second, 1.0000, 0.0001));
    assert(almost_equal(gains[18].second, 1.0000, 0.0001));
    assert(almost_equal(gains[19].second, 1.0000, 0.0001));
}

int main() {
    test_frequency_response();

    return 0;
}