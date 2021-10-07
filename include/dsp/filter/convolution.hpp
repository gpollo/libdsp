#ifndef LIBDSP_INCLUDE_DSP_FILTER_CONVOLUTION_HPP
#define LIBDSP_INCLUDE_DSP_FILTER_CONVOLUTION_HPP

#include <array>
#include <atomic>
#include <optional>
#include <type_traits>

namespace dsp::filter {

/**
 * This functor provides a convolution-based filter.
 *
 * The template parameter `Coefficients` must provide the following types/methods.
 *
 *    static constexpr std::array<T, N> get();
 *
 * This data structure is safe for one writer and multiple readers executing concurrently.
 */
template <typename T, unsigned int N, typename Coefficients>
class convolution {
   public:
    using type = T;

    std::optional<T> operator()(T sample);
    std::optional<T> operator()(std::optional<T> sample);
    std::optional<T> get() const;

   private:
    static constexpr std::array<T, N> COEFFICIENTS = Coefficients::get();
    std::array<T, N> samples_{};
    std::atomic_bool ready_ = false;

    T current_output_            = 0;
    unsigned int current_sample_ = 0;
};

template <typename T, unsigned int N, typename Coefficients>
std::optional<T> convolution<T, N, Coefficients>::operator()(T sample) {
    bool all_sample_received = ready_;

    samples_[current_sample_] = sample;
    if (current_sample_ == N - 1) {
        all_sample_received = true;
    }

    current_sample_ = (current_sample_ + 1) % N;
    if (!all_sample_received) {
        return {};
    }

    T sum = 0;
    for (unsigned int i = 0; i < N; i++) {
        unsigned int j = (current_sample_ + i) % N;
        sum += COEFFICIENTS[i] * samples_[j];
    }

    current_output_ = sum;
    ready_.store(true, std::memory_order_release);

    return sum;
}

template <typename T, unsigned int N, typename Coefficients>
std::optional<T> convolution<T, N, Coefficients>::operator()(std::optional<T> sample) {
    if (sample.has_value()) {
        return (*this)(sample.value());
    }

    return {};
}

template <typename T, unsigned int N, typename Coefficients>
std::optional<T> convolution<T, N, Coefficients>::get() const {
    if (!ready_.load(std::memory_order_consume)) {
        return {};
    }

    return current_output_;
}

} /* namespace dsp::filter */

#endif /* LIBDSP_INCLUDE_DSP_FILTER_CONVOLUTION_HPP */