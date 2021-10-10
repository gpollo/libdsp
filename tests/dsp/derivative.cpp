#include <cassert>
#include <cmath>

#include <dsp/derivative.hpp>

static bool almost_equal(float value, float expected, float epsilon) {
    return (std::fabs(value - expected) < std::fabs(epsilon));
}

int main() {
    dsp::derivative<float> derivative;

    /* first sample, no output */
    assert(!derivative(0.0F, 0.0F).has_value());

    /* positive slope */
    assert(almost_equal(derivative(100.0F, 30.0F).value_or(NAN), 0.30F, 0.0001F));
    assert(almost_equal(derivative(110.0F, 40.0F).value_or(NAN), 1.00F, 0.0001F));
    assert(almost_equal(derivative(200.0F, 49.0F).value_or(NAN), 0.10F, 0.0001F));

    /* negative slope */
    assert(almost_equal(derivative(300.0F, -00.0F).value_or(NAN), -0.49F, 0.0001F));
    assert(almost_equal(derivative(400.0F, -50.0F).value_or(NAN), -0.50F, 0.0001F));

    return 0;
}