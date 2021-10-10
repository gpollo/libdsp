#include <cassert>
#include <cmath>

#include <dsp/crop.hpp>

static bool almost_equal(float value, float expected, float epsilon) {
    return (std::fabs(value - expected) < std::fabs(epsilon));
}

static void test_crop_down() {
    dsp::crop::down<float> crop(10.0F, 0.0F);

    /* inputs below the minimum output */
    assert(almost_equal(crop(-5.0F), 0.0F, 0.0001));
    assert(almost_equal(crop(0.0F), 0.0F, 0.0001));

    /* inputs above the minimum output, before the threshold */
    assert(almost_equal(crop(3.0F), 0.0F, 0.0001));
    assert(almost_equal(crop(7.0F), 0.0F, 0.0001));

    /* inputs above the minimum output, after the threshold */
    assert(almost_equal(crop(11.0F), 11.0F, 0.0001));
    assert(almost_equal(crop(100.0F), 100.0F, 0.0001));
}

int main() {
    test_crop_down();

    return 0;
}