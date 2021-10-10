#ifndef LIBDSP_INCLUDE_DSP_INTEGRAL_HPP
#define LIBDSP_INCLUDE_DSP_INTEGRAL_HPP

#include <optional>

namespace dsp {

template <typename T>
class integral {
   public:
    std::optional<T> operator()(T x, T y);
    std::optional<T> operator()(std::optional<T> x, std::optional<T> y);

   private:
    bool ready_    = false;
    T current_sum_ = T();
    T last_x_;
    T last_y_;
};

template <typename T>
std::optional<T> integral<T>::operator()(T x, T y) {
    if (!ready_) {
        ready_  = true;
        last_x_ = x;
        last_y_ = y;
        return {};
    }

    T trapezoid = ((x - last_x_) * (y + last_y_)) / 2;
    current_sum_ += trapezoid;

    last_x_ = x;
    last_y_ = y;

    return current_sum_;
}

template <typename T>
std::optional<T> integral<T>::operator()(std::optional<T> x, std::optional<T> y) {
    if (x.has_value() && y.has_value()) {
        return (*this)(x.value(), y.value());
    }

    return {};
}

} /* namespace dsp */

#endif /* LIBDSP_INCLUDE_DSP_INTEGRAL_HPP */
