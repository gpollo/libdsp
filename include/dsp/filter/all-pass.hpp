#ifndef LIBDSP_INCLUDE_DSP_FILTER_ALL_PASS_HPP
#define LIBDSP_INCLUDE_DSP_FILTER_ALL_PASS_HPP

#include <atomic>
#include <optional>

namespace dsp::filter {

/**
 * This functor provides a all-pass filter (placebo).
 *
 * This data structure is safe for one writer and multiple readers executing concurrently.
 */
template <typename T>
class all_pass {
   public:
    using type = T;

    std::optional<T> operator()(T sample);
    std::optional<T> operator()(std::optional<T> sample);
    std::optional<T> get() const;

   private:
    std::atomic_bool ready_ = false;
    T current_output_;
};

template <typename T>
std::optional<T> all_pass<T>::operator()(T sample) {
    current_output_ = sample;
    ready_.store(true, std::memory_order_release);
    return current_output_;
}

template <typename T>
std::optional<T> all_pass<T>::operator()(std::optional<T> sample) {
    if (sample.has_value()) {
        return (*this)(sample.value());
    }

    return {};
}

template <typename T>
std::optional<T> all_pass<T>::get() const {
    if (!ready_.load(std::memory_order_consume)) {
        return {};
    }

    return current_output_;
}

} /* namespace dsp::filter */

#endif /* LIBDSP_INCLUDE_DSP_FILTER_ALL_PASS_HPP */