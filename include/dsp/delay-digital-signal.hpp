#ifndef LIBDSP_INCLUDE_DSP_DELAY_SIGNAL_HPP
#define LIBDSP_INCLUDE_DSP_DELAY_SIGNAL_HPP

#include <atomic>
#include <ctgmath>
#include <optional>

namespace dsp {

/**
 * This functor delays the rising or falling edge in a binary signal.
 *
 * This data structure is safe for one writer and multiple readers executing concurrently.
 */
template <typename T>
class delay_digital_signal {
   public:
    enum class event { RISING_EDGE, FALLING_EDGE };

    delay_digital_signal(event event, T delay_x);

    std::optional<bool> operator()(T x, bool y);
    std::optional<bool> operator()(std::optional<T> x, std::optional<bool> y);
    std::optional<bool> get() const;

   private:
    enum class state { INIT, EVENT, OUTPUT };

    const event event_;
    const T delay_x_;

    state state_ = state::INIT;

    T current_event_x_     = 0;
    bool current_input_y_  = false;
    bool current_output_y_ = false;

    std::atomic_bool ready_ = false;

    void set_event(T x);
    void set_output(bool y);

    void state_init(T x, bool y);
    void state_event(T x, bool y);
    void state_output(T x, bool y);
};

template <typename T>
delay_digital_signal<T>::delay_digital_signal(event event, T delay_x) : event_(event), delay_x_(delay_x) {}

template <typename T>
std::optional<bool> delay_digital_signal<T>::operator()(T x, bool y) {
    switch (state_) {
    case state::INIT:
        state_init(x, y);
        break;
    case state::EVENT:
        state_event(x, y);
        break;
    case state::OUTPUT:
        state_output(x, y);
        break;
    }

    current_input_y_ = y;
    if (!ready_) {
        return {};
    }

    return current_output_y_;
}

template <typename T>
std::optional<bool> delay_digital_signal<T>::operator()(std::optional<T> x, std::optional<bool> y) {
    if (x.has_value() && y.has_value()) {
        return (*this)(x.value(), y.value());
    }

    return {};
}

template <typename T>
std::optional<bool> delay_digital_signal<T>::get() const {
    if (!ready_.load(std::memory_order_consume)) {
        return {};
    }

    return current_output_y_;
}

template <typename T>
inline void delay_digital_signal<T>::set_event(T x) {
    current_event_x_ = x;
}

template <typename T>
inline void delay_digital_signal<T>::set_output(bool y) {
    current_output_y_ = y;
    ready_.store(true, std::memory_order_release);
}

template <typename T>
inline void delay_digital_signal<T>::state_init(T x, bool y) {
    switch (event_) {
    case event::RISING_EDGE:
        if (y) {
            state_ = state::EVENT;
            set_event(x);
        } else {
            state_ = state::OUTPUT;
            set_output(false);
        }
        break;

    case event::FALLING_EDGE:
        if (!y) {
            state_ = state::EVENT;
            set_event(x);
        } else {
            state_ = state::OUTPUT;
            set_output(true);
        }
        break;
    }
}

template <typename T>
inline void delay_digital_signal<T>::state_event(T x, bool y) {
    switch (event_) {
    case event::RISING_EDGE:
        if (!y) {
            state_ = state::OUTPUT;
            set_output(false);
        } else if (x - current_event_x_ > delay_x_) {
            state_ = state::OUTPUT;
            set_output(true);
        }
        break;

    case event::FALLING_EDGE:
        if (y) {
            state_ = state::OUTPUT;
            set_output(true);
        } else if (x - current_event_x_ > delay_x_) {
            state_ = state::OUTPUT;
            set_output(false);
        }
        break;
    }
}

template <typename T>
inline void delay_digital_signal<T>::state_output(T x, bool y) {
    switch (event_) {
    case event::RISING_EDGE:
        if (!y) {
            set_output(false);
        } else if (!current_input_y_) {
            state_ = state::EVENT;
            set_event(x);
        }
        break;

    case event::FALLING_EDGE:
        if (y) {
            set_output(true);
        } else if (current_input_y_) {
            state_ = state::EVENT;
            set_event(x);
        }
        break;
    }
}

} /* namespace dsp */

#endif /* LIBDSP_INCLUDE_DSP_DELAY_SIGNAL_HPP */
