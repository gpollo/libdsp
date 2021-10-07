#include <assert.h>
#include <tgmath.h>

#include <dsp/filter/moving-average.hpp>

template <typename T>
static bool almost_equal(T value, T expected, T epsilon = 0.00001) {
    return (std::abs(value - expected) < epsilon);
}

static void test_simple_inputs() {
    dsp::filter::moving_average<float, 10> filter;

    assert(!filter(11).has_value());
    assert(!filter(12).has_value());
    assert(!filter(13).has_value());
    assert(!filter(14).has_value());
    assert(!filter(15).has_value());
    assert(!filter(16).has_value());
    assert(!filter(17).has_value());
    assert(!filter(18).has_value());
    assert(!filter(19).has_value());
    assert(almost_equal(filter(20).value_or(-1), 15.5F));
    assert(almost_equal(filter(21).value_or(-1), 16.5F));
    assert(almost_equal(filter(22).value_or(-1), 17.5F));
    assert(almost_equal(filter(23).value_or(-1), 18.5F));
    assert(almost_equal(filter(24).value_or(-1), 19.5F));
    assert(almost_equal(filter(25).value_or(-1), 20.5F));
    assert(almost_equal(filter(26).value_or(-1), 21.5F));
    assert(almost_equal(filter(27).value_or(-1), 22.5F));
    assert(almost_equal(filter(28).value_or(-1), 23.5F));
    assert(almost_equal(filter(29).value_or(-1), 24.5F));
    assert(almost_equal(filter(30).value_or(-1), 25.5F));
    assert(almost_equal(filter(40).value_or(-1), 27.4F));
    assert(almost_equal(filter(-40).value_or(-1), 21.2F));
}

int main() {
    test_simple_inputs();

    return 0;
}