#include <cassert>

#include <dsp/delay-digital-signal.hpp>

static void assert_optional_is_empty(const std::optional<bool>& opt) {
    assert(!opt.has_value());
}

static void assert_optional_is_true(const std::optional<bool>& opt) {
    assert(opt.has_value());
    assert(opt.value());
}

static void assert_optional_is_false(const std::optional<bool>& opt) {
    assert(opt.has_value());
    assert(!opt.value());
}

static void test_rising_edge_begin_low() {
    dsp::delay_digital_signal<unsigned int> delay(dsp::delay_digital_signal<unsigned int>::event::RISING_EDGE, 5000);

    /* should return low */
    assert_optional_is_false(delay(6000, false));

    /* should return high only after 5000 ticks */
    assert_optional_is_false(delay(8000, true));
    assert_optional_is_false(delay(11000, true));
    assert_optional_is_false(delay(13000, true));
    assert_optional_is_true(delay(13001, true));
    assert_optional_is_true(delay(15000, true));

    /* should return low immediately */
    assert_optional_is_false(delay(16000, false));

    /* should return high only after 5000 ticks */
    assert_optional_is_false(delay(17000, true));
    assert_optional_is_false(delay(20000, true));
    assert_optional_is_false(delay(22000, true));
    assert_optional_is_true(delay(22001, true));
    assert_optional_is_true(delay(25000, true));
}

static void test_rising_edge_begin_high() {
    dsp::delay_digital_signal<unsigned int> delay(dsp::delay_digital_signal<unsigned int>::event::RISING_EDGE, 5000);

    /* should return high only after 5000 ticks */
    assert_optional_is_empty(delay(8000, true));
    assert_optional_is_empty(delay(11000, true));
    assert_optional_is_empty(delay(13000, true));
    assert_optional_is_true(delay(13001, true));
    assert_optional_is_true(delay(15000, true));

    /* should return low immediately */
    assert_optional_is_false(delay(16000, false));

    /* should return high only after 5000 ticks */
    assert_optional_is_false(delay(17000, true));
    assert_optional_is_false(delay(20000, true));
    assert_optional_is_false(delay(22000, true));
    assert_optional_is_true(delay(22001, true));
    assert_optional_is_true(delay(25000, true));
}

static void test_falling_edge_begin_high() {
    dsp::delay_digital_signal<unsigned int> delay(dsp::delay_digital_signal<unsigned int>::event::FALLING_EDGE, 5000);

    /* should return high */
    assert_optional_is_true(delay(6000, true));

    /* should return low only after 5000 ticks */
    assert_optional_is_true(delay(8000, false));
    assert_optional_is_true(delay(11000, false));
    assert_optional_is_true(delay(13000, false));
    assert_optional_is_false(delay(13001, false));
    assert_optional_is_false(delay(15000, false));

    /* should return high immediately */
    assert_optional_is_true(delay(16000, true));

    /* should return low only after 5000 ticks */
    assert_optional_is_true(delay(17000, false));
    assert_optional_is_true(delay(20000, false));
    assert_optional_is_true(delay(22000, false));
    assert_optional_is_false(delay(22001, false));
    assert_optional_is_false(delay(25000, false));
}

static void test_falling_edge_begin_low() {
    dsp::delay_digital_signal<unsigned int> delay(dsp::delay_digital_signal<unsigned int>::event::FALLING_EDGE, 5000);

    /* should return low only after 5000 ticks */
    assert_optional_is_empty(delay(8000, false));
    assert_optional_is_empty(delay(11000, false));
    assert_optional_is_empty(delay(13000, false));
    assert_optional_is_false(delay(13001, false));
    assert_optional_is_false(delay(15000, false));

    /* should return high immediately */
    assert_optional_is_true(delay(16000, true));

    /* should return low only after 5000 ticks */
    assert_optional_is_true(delay(17000, false));
    assert_optional_is_true(delay(20000, false));
    assert_optional_is_true(delay(22000, false));
    assert_optional_is_false(delay(22001, false));
    assert_optional_is_false(delay(25000, false));
}

int main() {
    test_rising_edge_begin_low();
    test_rising_edge_begin_high();
    test_falling_edge_begin_high();
    test_falling_edge_begin_low();

    return 0;
}