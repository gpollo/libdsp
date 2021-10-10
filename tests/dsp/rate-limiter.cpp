#include <cassert>
#include <cmath>

#include <dsp/rate-limiter.hpp>

static bool almost_equal(float value, float expected, float epsilon) {
    return (std::fabs(value - expected) < std::fabs(epsilon));
}

int main() {
    dsp::rate_limiter<float> limit(-50.0F, 100.0F, 0.0001F);

    /* initial sample */
    assert(!limit(0, 0).has_value());

    /* samples going up */
    assert(almost_equal(limit(1.0F, 200.0F).value_or(-1.0F), 100.0F, 0.001F));
    assert(almost_equal(limit(2.0F, 300.0F).value_or(-1.0F), 200.0F, 0.001F));
    assert(almost_equal(limit(3.0F, 350.0F).value_or(-1.0F), 300.0F, 0.001F));
    assert(almost_equal(limit(4.0F, 350.0F).value_or(-1.0F), 350.0F, 0.001F));
    assert(almost_equal(limit(5.0F, 450.0F).value_or(-1.0F), 450.0F, 0.001F));

    /* samples going down */
    assert(almost_equal(limit(7.0F, 300.0F).value_or(-1.0F), 350.0F, 0.001F));
    assert(almost_equal(limit(8.0F, 300.0F).value_or(-1.0F), 300.0F, 0.001F));
    assert(almost_equal(limit(9.0F, 100.0F).value_or(-1.0F), 250.0F, 0.001F));
    assert(almost_equal(limit(10.0F, 0.0F).value_or(-1.0F), 200.0F, 0.001F));
    assert(almost_equal(limit(11.0F, 0.0F).value_or(-1.0F), 150.0F, 0.001F));
    assert(almost_equal(limit(13.0F, 0.0F).value_or(-1.0F), 50.0F, 0.001F));

    return 0;
}