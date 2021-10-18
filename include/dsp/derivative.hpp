#ifndef LIBDSP_INCLUDE_DSP_DERIVATIVE_HPP
#define LIBDSP_INCLUDE_DSP_DERIVATIVE_HPP

#include <optional>

namespace dsp {

template <typename T>
class derivative {
   public:
    std::optional<T> operator()(T x, T y);
    std::optional<T> operator()(std::optional<T> x, std::optional<T> y);

   private:
    bool ready_ = false;
    T last_x_   = static_cast<T>(0);
    T last_y_   = static_cast<T>(0);
};

template <typename T>
std::optional<T> derivative<T>::operator()(T x, T y) {
    if (!ready_) {
        ready_  = true;
        last_x_ = x;
        last_y_ = y;
        return {};
    }

    T delta_x = x - last_x_;
    T delta_y = y - last_y_;

    last_x_ = x;
    last_y_ = y;

    return delta_y / delta_x;
}

template <typename T>
std::optional<T> derivative<T>::operator()(std::optional<T> x, std::optional<T> y) {
    if (x.has_value() && y.has_value()) {
        return (*this)(x.value(), y.value());
    }

    return {};
}

} /* namespace dsp */

#endif /* LIBDSP_INCLUDE_DSP_DERIVATIVE_HPP */
