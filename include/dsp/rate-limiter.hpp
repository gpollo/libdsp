#ifndef LIBDSP_INCLUDE_DSP_RATE_LIMITER_HPP
#define LIBDSP_INCLUDE_DSP_RATE_LIMITER_HPP

#include <atomic>
#include <ctgmath>
#include <optional>

namespace dsp {

/**
 * This functor provides a rate limiter for both increasing and decreasing inputs.
 *
 * This data structure is safe for one writer and multiple readers executing concurrently.
 */
template <typename T>
class rate_limiter {
   public:
    rate_limiter(std::optional<T> min, std::optional<T> max, T min_delta_x);

    std::optional<T> operator()(T x, T y);
    std::optional<T> operator()(std::optional<T> x, std::optional<T> y);
    std::optional<T> get() const;

   private:
    const T minimum_rate_;
    const bool minimum_rate_enabled_;

    const T maximum_rate_;
    const bool maximum_rate_enabled_;

    T min_delta_x_;
    T last_x_   = 0;
    T last_y_   = 0;
    T output_y_ = 0;

    bool first_sample_received_ = false;
    std::atomic_bool ready_     = false;
};

template <typename T>
rate_limiter<T>::rate_limiter(std::optional<T> min, std::optional<T> max, T min_delta_x)
    : minimum_rate_(min.value_or(0)),
      minimum_rate_enabled_(min.has_value()),
      maximum_rate_(max.value_or(0)),
      maximum_rate_enabled_(max.has_value()),
      min_delta_x_(min_delta_x) {}

template <typename T>
std::optional<T> rate_limiter<T>::operator()(T x, T y) {
    if (first_sample_received_) {
        if (std::abs(x - last_x_) < min_delta_x_) {
            return output_y_;
        }

        T dx   = x - last_x_;
        T dy   = y - last_y_;
        T rate = dy / dx;

        if (minimum_rate_enabled_ && rate < minimum_rate_) {
            y = last_y_ + dx * minimum_rate_;
        }

        if (maximum_rate_enabled_ && maximum_rate_ < rate) {
            y = last_y_ + dx * maximum_rate_;
        }

        output_y_ = y;
        ready_.store(true, std::memory_order_release);
    }

    last_x_ = x;
    last_y_ = y;

    if (!first_sample_received_) {
        first_sample_received_ = true;
        return {};
    }

    return output_y_;
}

template <typename T>
std::optional<T> rate_limiter<T>::operator()(std::optional<T> x, std::optional<T> y) {
    if (x.has_value() && y.has_value()) {
        return (*this)(x.value(), y.value());
    }

    return {};
}

template <typename T>
std::optional<T> rate_limiter<T>::get() const {
    if (!ready_.load(std::memory_order_consume)) {
        return {};
    }

    return output_y_;
}

} /* namespace dsp */

#endif /* LIBDSP_INCLUDE_DSP_RATE_LIMITER_HPP */
