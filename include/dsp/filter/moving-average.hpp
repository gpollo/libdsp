#ifndef LIBDSP_INCLUDE_DSP_FILTER_MOVING_AVERAGE_HPP
#define LIBDSP_INCLUDE_DSP_FILTER_MOVING_AVERAGE_HPP

#include <array>
#include <atomic>
#include <optional>

namespace dsp::filter {

/**
 * This functor provides a simple moving average.
 *
 * This data structure is safe for one writer and multiple readers executing concurrently.
 */
template <typename T, unsigned int N>
class moving_average {
   public:
    void next(T sample);
    std::optional<T> operator()(T sample);
    std::optional<T> operator()(std::optional<T> sample);
    std::optional<T> get() const;

   private:
    std::array<T, N> samples_;
    std::atomic_bool ready_ = false;

    T current_output_            = 0;
    T current_sum_               = 0;
    unsigned int current_sample_ = 0;
};

template <typename T, unsigned int N>
std::optional<T> moving_average<T, N>::operator()(T sample) {
    bool all_sample_received = ready_;

    current_sum_ = current_sum_ + sample;
    if (all_sample_received) {
        current_sum_ -= samples_[current_sample_];
    }

    samples_[current_sample_] = sample;

    if (current_sample_ == N - 1) {
        current_sample_     = 0;
        all_sample_received = true;
    } else {
        current_sample_++;
    }

    if (!all_sample_received) {
        return {};
    }

    current_output_ = current_sum_ / N;
    ready_.store(true, std::memory_order_release);

    return current_output_;
}

template <typename T, unsigned int N>
std::optional<T> moving_average<T, N>::operator()(std::optional<T> sample) {
    if (sample.has_value()) {
        return (*this)(sample.value());
    }

    return {};
}

template <typename T, unsigned int N>
std::optional<T> moving_average<T, N>::get() const {
    if (!ready_.load(std::memory_order_consume)) {
        return {};
    }

    return current_output_;
}

} /* namespace dsp::filter */

#endif /* LIBDSP_INCLUDE_DSP_FILTER_MOVING_AVERAGE_HPP */
