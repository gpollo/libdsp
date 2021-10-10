#include <cassert>
#include <cmath>

#include <dsp/integral.hpp>

static bool almost_equal(float value, float expected, float epsilon) {
    return (std::fabs(value - expected) < std::fabs(epsilon));
}

int main() {
    dsp::integral<float> integral;

    /* first sample, no output */
    assert(!integral(0.0F, 0.0F).has_value());

    /* positive area */
    assert(almost_equal(integral(100.0F, 30.0F).value_or(NAN), 1500.0F, 0.0001F));
    assert(almost_equal(integral(300.0F, 40.0F).value_or(NAN), 8500.0F, 0.0001F));
    assert(almost_equal(integral(350.0F, 10.0F).value_or(NAN), 9750.0F, 0.0001F));
    assert(almost_equal(integral(400.0F, 0.0F).value_or(NAN), 10000.0F, 0.0001F));

    /* negative area */
    assert(almost_equal(integral(600.0F, -50.0F).value_or(NAN), 5000.0F, 0.0001F));
    assert(almost_equal(integral(700.0F, -50.0F).value_or(NAN), 0.0F, 0.0001F));
    assert(almost_equal(integral(750.0F, 0.0F).value_or(NAN), -1250.0F, 0.0001F));

    return 0;
}