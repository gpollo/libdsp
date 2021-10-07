#ifndef LIBDSP_INCLUDE_DSP_MAXIMIZER_HPP
#define LIBDSP_INCLUDE_DSP_MAXIMIZER_HPP

#include <optional>

namespace dsp {

/**
 * This functor keeps track of the largest value it encountered.
 */
template <typename T>
class maximizer {
   public:
    T operator()(T input);
    std::optional<T> operator()(std::optional<T> input);
    std::optional<T> get() const;

   private:
    bool initialised_ = false;
    T current_value_;
};

template <typename T>
T maximizer<T>::operator()(T input) {
    if (!initialised_ || input > current_value_) {
        current_value_ = input;
    }

    initialised_ = true;

    return current_value_;
}

template <typename T>
std::optional<T> maximizer<T>::operator()(std::optional<T> input) {
    if (input.has_value()) {
        return (*this)(input.value());
    }

    return {};
}

template <typename T>
std::optional<T> maximizer<T>::get() const {
    if (!initialised_) {
        return {};
    }

    return current_value_;
}

} /* namespace dsp */

#endif /* LIBDSP_INCLUDE_DSP_MAXIMIZER_HPP */
