#ifndef LIBDSP_INCLUDE_DSP_CROP_HPP
#define LIBDSP_INCLUDE_DSP_CROP_HPP

#include <optional>

namespace dsp::crop {

/**
 * This simple functor crop a given input to a value if it is below a certain threshold.
 *
 * Useful if you want to crop noise above zero to zero.
 */
template <typename T>
class down {
   public:
    down(T x_threshold, T y_minimum);

    T operator()(T x) const;
    std::optional<T> operator()(std::optional<T> x) const;

   private:
    const T x_threshold_;
    const T y_minimum_;
};

template <typename T>
down<T>::down(T x_threshold, T y_minimum)
    : x_threshold_(x_threshold), y_minimum_((x_threshold < y_minimum) ? x_threshold : y_minimum) {}

template <typename T>
T down<T>::operator()(T x) const {
    if (x < x_threshold_) {
        return y_minimum_;
    }

    T y = x;

    return y;
}

template <typename T>
std::optional<T> down<T>::operator()(std::optional<T> x) const {
    if (x.has_value()) {
        return (*this)(x.value());
    }

    return {};
}

} /* namespace dsp::crop */

#endif /* LIBDSP_INCLUDE_DSP_CROP_HPP */