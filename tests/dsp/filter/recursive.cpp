#include <assert.h>
#include <tgmath.h>

#include <dsp/filter/recursive.hpp>

template <typename T>
static bool almost_equal(T value, T expected, T epsilon = 0.00001) {
    return (std::abs(value - expected) < epsilon);
}

template <typename T>
struct test_coefficients {
    using type         = T;
    using coefficients = dsp::filter::recursive_coefficients<T, 1, 4>;

    static constexpr coefficients get() {
        /* non-normalized coefficients are unstable but good enough for tests */
        coefficients coefficients;
        coefficients.a_[0] = 1;
        coefficients.b_[0] = 2;
        coefficients.b_[1] = 3;
        coefficients.b_[2] = 4;
        coefficients.b_[3] = 5;
        return coefficients;
    }
};
#include <iostream>
static void test_simple_inputs() {
    dsp::filter::recursive<float, 1, 4, test_coefficients<float>> recursive;

    assert(!recursive(10).has_value());
    assert(!recursive(10).has_value());
    assert(!recursive(10).has_value());
    assert(almost_equal(recursive(10).value_or(-1), 10.0F));
    assert(almost_equal(recursive(10).value_or(-1), 30.0F));
    assert(almost_equal(recursive(10).value_or(-1), 100.0F));
    assert(almost_equal(recursive(20).value_or(-1), 350.0F));
    assert(almost_equal(recursive(0).value_or(-1), 1170.0F));
    assert(almost_equal(recursive(0).value_or(-1), 3940.0F));
}

int main() {
    test_simple_inputs();

    return 0;
}