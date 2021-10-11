#ifndef LIBDSP_INCLUDE_DSP_FILTER_RECURSIVE_HPP
#define LIBDSP_INCLUDE_DSP_FILTER_RECURSIVE_HPP

#include <array>
#include <atomic>
#include <optional>

namespace dsp::filter {

template <typename T, unsigned int AN, unsigned int BN>
struct recursive_coefficients {
    std::array<T, AN> a_;
    std::array<T, BN> b_;
};

/**
 * This functor provides a convolution-based filter.
 *
 * The template parameter `Coefficients` must provide the following types/methods.
 *
 *    using type = ...;
 *    static constexpr recursive_coefficients<T, AN, BN> get();
 *
 * This data structure is safe for one writer and multiple readers executing concurrently.
 */
template <typename T, unsigned int AN, unsigned int BN, typename Coefficients>
class recursive {
   public:
    using type = T;

    static_assert(std::is_same<T, typename Coefficients::type>::value, "coefficients must use the same type");

    std::optional<T> operator()(T sample);
    std::optional<T> operator()(std::optional<T> sample);
    std::optional<T> get() const;

   private:
    const recursive_coefficients<T, AN, BN> COEFFICIENTS = Coefficients::get();
    std::array<T, AN> input_samples_;
    std::array<T, BN> output_samples_;
    std::atomic_bool ready_ = false;
    T current_output_       = 0;

    unsigned int current_input_sample_  = 0;
    unsigned int current_output_sample_ = 0;
};

template <typename T, unsigned int AN, unsigned int BN, typename Coefficients>
std::optional<T> recursive<T, AN, BN, Coefficients>::operator()(T sample) {
    input_samples_[current_input_sample_] = sample;

    bool ready = ready_;
    if (!ready) {
        output_samples_[current_output_sample_] = 0;

        if (AN > BN) {
            if (current_input_sample_ == AN - 1) {
                ready = true;
            }
        } else {
            if (current_output_sample_ == BN - 1) {
                ready = true;
            }
        }
    }

    current_input_sample_  = (current_input_sample_ + 1) % AN;
    current_output_sample_ = (current_output_sample_ + 1) % BN;

    if (!ready) {
        return {};
    }

    type sum = 0;
    for (unsigned int i = 0; i < AN; i++) {
        unsigned int j = (current_input_sample_ - i + AN - 1) % AN;
        sum += COEFFICIENTS.a_[i] * input_samples_[j];
    }

    for (unsigned int i = 0; i < BN; i++) {
        unsigned int j = (current_output_sample_ - i + BN - 1) % BN;
        sum += COEFFICIENTS.b_[i] * output_samples_[j];
    }

    current_output_ = sum;
    ready_.store(true, std::memory_order_release);

    output_samples_[current_output_sample_] = current_output_;

    return sum;
}

template <typename T, unsigned int AN, unsigned int BN, typename Coefficients>
std::optional<T> recursive<T, AN, BN, Coefficients>::operator()(std::optional<T> sample) {
    if (sample.has_value()) {
        return (*this)(sample.value());
    }

    return {};
}

template <typename T, unsigned int AN, unsigned int BN, typename Coefficients>
std::optional<T> recursive<T, AN, BN, Coefficients>::get() const {
    if (!ready_.load(std::memory_order_consume)) {
        return {};
    }

    return current_output_;
}

} /* namespace dsp::filter */

#endif /* LIBDSP_INCLUDE_DSP_FILTER_RECURSIVE_HPP */