#include <cassert>
#include <cmath>

#include <dsp/partial-linear-map.hpp>

static bool almost_equal(float value, float expected, float epsilon) {
    return (std::fabs(value - expected) < std::fabs(epsilon));
}

static void test_ascending() {
    dsp::partial_linear_map<float> simple_linear_mapping(10.0F, 20.0F, 100.0F, 200.0F);

    /* values before the linear region */
    assert(almost_equal(simple_linear_mapping(5.0F), 100.0F, 0.0001F));
    assert(almost_equal(simple_linear_mapping(10.0F), 100.0F, 0.0001F));

    /* values in the linear region */
    assert(almost_equal(simple_linear_mapping(12.0F), 120.0F, 0.0001F));
    assert(almost_equal(simple_linear_mapping(15.0F), 150.0F, 0.0001F));
    assert(almost_equal(simple_linear_mapping(18.0F), 180.0F, 0.0001F));

    /* values after the linear region */
    assert(almost_equal(simple_linear_mapping(20.0F), 200.0F, 0.0001F));
    assert(almost_equal(simple_linear_mapping(25.0F), 200.0F, 0.0001F));
}

static void test_descending() {
    dsp::partial_linear_map<float> simple_linear_mapping(10.0F, 20.0F, 200.0F, 100.0F);

    /* values before the linear region */
    assert(almost_equal(simple_linear_mapping(5.0F), 200.0F, 0.0001F));
    assert(almost_equal(simple_linear_mapping(10.0F), 200.0F, 0.0001F));

    /* values in the linear region */
    assert(almost_equal(simple_linear_mapping(12.0F), 180.0F, 0.0001F));
    assert(almost_equal(simple_linear_mapping(15.0F), 150.0F, 0.0001F));
    assert(almost_equal(simple_linear_mapping(18.0F), 120.0F, 0.0001F));

    /* values after the linear region */
    assert(almost_equal(simple_linear_mapping(20.0F), 100.0F, 0.0001F));
    assert(almost_equal(simple_linear_mapping(25.0F), 100.0F, 0.0001F));
}

int main() {
    test_ascending();
    test_descending();

    return 0;
}