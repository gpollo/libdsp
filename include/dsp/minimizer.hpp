#ifndef LIBDSP_INCLUDE_DSP_MINIMIZER_HPP
#define LIBDSP_INCLUDE_DSP_MINIMIZER_HPP

#include <optional>

namespace dsp {

/**
 * This functor keeps track of the smallest value it encountered.
 */
template <typename T>
class minimizer {
   public:
    T operator()(T input);
    std::optional<T> operator()(std::optional<T> input);
    std::optional<T> get() const;

   private:
    bool initialised_ = false;
    T current_value_;
};

template <typename T>
T minimizer<T>::operator()(T input) {
    if (!initialised_ || input < current_value_) {
        current_value_ = input;
    }

    initialised_ = true;

    return current_value_;
}

template <typename T>
std::optional<T> minimizer<T>::operator()(std::optional<T> input) {
    if (input.has_value()) {
        return (*this)(input.value());
    }

    return {};
}

template <typename T>
std::optional<T> minimizer<T>::get() const {
    if (!initialised_) {
        return {};
    }

    return current_value_;
}

} /* namespace dsp */

#endif /* LIBDSP_INCLUDE_DSP_MINIMIZER_HPP */
