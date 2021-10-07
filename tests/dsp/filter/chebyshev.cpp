#include <assert.h>
#include <tgmath.h>

#include <dsp/filter/chebyshev.hpp>

template <typename T>
static bool almost_equal(T value, T expected, T epsilon = 0.00001) {
    return (std::abs(value - expected) < epsilon);
}

struct settings_2_pole {
    using type = long double;

    static constexpr unsigned int POLE_COUNT     = 2;
    static constexpr float PERCENT_RIPPLE        = 0.5F;
    static constexpr float SAMPLING_FREQUENCY_HZ = 100.0F;
    static constexpr float CUTOFF_FREQUENCY_HZ   = 5.0F;
};

static void test_2_pole_coefficients() {
    using generator             = dsp::filter::chebyshev::impl::chebyshev_coefficient<settings_2_pole, false>;
    constexpr auto coefficients = generator::get();

    /* taken from http://www.dspguide.com/ch20.htm */
    assert(almost_equal(coefficients.a_[0], 1.868823E-02L));
    assert(almost_equal(coefficients.a_[1], 3.737647E-02L));
    assert(almost_equal(coefficients.a_[2], 1.868823E-02L));
    assert(almost_equal(coefficients.b_[0], 1.593937E+00L));
    assert(almost_equal(coefficients.b_[1], -6.686903E-01L));
}

struct settings_4_pole {
    using type = double;

    static constexpr unsigned int POLE_COUNT     = 4;
    static constexpr float PERCENT_RIPPLE        = 0.5F;
    static constexpr float SAMPLING_FREQUENCY_HZ = 100.0F;
    static constexpr float CUTOFF_FREQUENCY_HZ   = 20.0F;
};

static void test_4_pole_coefficients() {
    using generator             = dsp::filter::chebyshev::impl::chebyshev_coefficient<settings_4_pole, false>;
    constexpr auto coefficients = generator::get();

    /* taken from http://www.dspguide.com/ch20.htm */
    assert(almost_equal(coefficients.a_[0], 3.224554E-02));
    assert(almost_equal(coefficients.a_[1], 1.289821E-01));
    assert(almost_equal(coefficients.a_[2], 1.934732E-01));
    assert(almost_equal(coefficients.a_[3], 1.289821E-01));
    assert(almost_equal(coefficients.a_[4], 3.224554E-02));
    assert(almost_equal(coefficients.b_[0], 1.265912E+00));
    assert(almost_equal(coefficients.b_[1], -1.203878E+00));
    assert(almost_equal(coefficients.b_[2], 5.405908E-01));
    assert(almost_equal(coefficients.b_[3], -1.185538E-01));
}

struct settings_6_pole {
    using type = double;

    static constexpr unsigned int POLE_COUNT     = 6;
    static constexpr float PERCENT_RIPPLE        = 0.5F;
    static constexpr float SAMPLING_FREQUENCY_HZ = 100.0F;
    static constexpr float CUTOFF_FREQUENCY_HZ   = 40.0F;
};

static void test_6_pole_coefficients() {
    using generator             = dsp::filter::chebyshev::impl::chebyshev_coefficient<settings_6_pole, false>;
    constexpr auto coefficients = generator::get();

    /* taken from http://www.dspguide.com/ch20.htm */
    assert(almost_equal(coefficients.a_[0], 2.211834E-01));
    assert(almost_equal(coefficients.a_[1], 1.327100E+00));
    assert(almost_equal(coefficients.a_[2], 3.317751E+00));
    assert(almost_equal(coefficients.a_[3], 4.423668E+00));
    assert(almost_equal(coefficients.a_[4], 3.317751E+00));
    assert(almost_equal(coefficients.a_[5], 1.327100E+00));
    assert(almost_equal(coefficients.a_[6], 2.211834E-01));
    assert(almost_equal(coefficients.b_[0], -3.058672E+00));
    assert(almost_equal(coefficients.b_[1], -4.390465E+00));
    assert(almost_equal(coefficients.b_[2], -3.523254E+00));
    assert(almost_equal(coefficients.b_[3], -1.684185E+00));
    assert(almost_equal(coefficients.b_[4], -4.414881E-01));
    assert(almost_equal(coefficients.b_[5], -5.767513E-02));
}

int main() {
    test_2_pole_coefficients();
    test_4_pole_coefficients();
    test_6_pole_coefficients();

    return 0;
}