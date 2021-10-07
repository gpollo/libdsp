#include <assert.h>
#include <tgmath.h>

#include <dsp/filter/convolution.hpp>

template <typename T>
static bool almost_equal(T value, T expected, T epsilon = 0.00001) {
    return (std::abs(value - expected) < epsilon);
}

template <typename T, unsigned int N>
struct moving_average_coefficients {
    using type = T;

    static constexpr std::array<T, N> get() {
        std::array<T, N> coefficients;

        for (unsigned int i = 0; i < N; i++) {
            coefficients[i] = static_cast<T>(1) / static_cast<T>(N);
        }

        return coefficients;
    }
};

static void test_moving_average() {
    dsp::filter::convolution<float, 10, moving_average_coefficients<float, 10>> convolution;

    assert(!convolution(11).has_value());
    assert(!convolution(12).has_value());
    assert(!convolution(13).has_value());
    assert(!convolution(14).has_value());
    assert(!convolution(15).has_value());
    assert(!convolution(16).has_value());
    assert(!convolution(17).has_value());
    assert(!convolution(18).has_value());
    assert(!convolution(19).has_value());
    assert(almost_equal(convolution(20).value_or(-1), 15.5F));
    assert(almost_equal(convolution(21).value_or(-1), 16.5F));
    assert(almost_equal(convolution(22).value_or(-1), 17.5F));
    assert(almost_equal(convolution(23).value_or(-1), 18.5F));
    assert(almost_equal(convolution(24).value_or(-1), 19.5F));
    assert(almost_equal(convolution(25).value_or(-1), 20.5F));
    assert(almost_equal(convolution(26).value_or(-1), 21.5F));
    assert(almost_equal(convolution(27).value_or(-1), 22.5F));
    assert(almost_equal(convolution(28).value_or(-1), 23.5F));
    assert(almost_equal(convolution(29).value_or(-1), 24.5F));
    assert(almost_equal(convolution(30).value_or(-1), 25.5F));
    assert(almost_equal(convolution(40).value_or(-1), 27.4F));
    assert(almost_equal(convolution(-40).value_or(-1), 21.2F));
}

int main() {
    test_moving_average();

    return 0;
}