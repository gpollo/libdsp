#ifndef LIBDSP_INCLUDE_DSP_PID_HPP
#define LIBDSP_INCLUDE_DSP_PID_HPP

#include <optional>

#include "dsp/derivative.hpp"
#include "dsp/integral.hpp"

namespace dsp {

/**
 * This functor integrates the input signal.
 *
 * The integrator windup template parameter `W` must provide the following types/method:
 *
 *    using type = ...;
 *    type operator()(type timestamp, type error, type integrator_value);
 *
 * The derivative input filter template parameter `F` must provide the following types/method:
 *
 *    using type = ...;
 *    std::optional<type> operator()(type sample);
 */
template <typename T, typename W, typename F>
class pid {
   public:
    static_assert(std::is_same<T, typename W::type>::value, "integrator windup must use the same type");
    static_assert(std::is_same<T, typename F::type>::value, "derivative filter must use the same type");

    pid(T k_p, T k_i, T k_d);
    std::optional<T> operator()(T timestamp, T error);
    std::optional<T> operator()(std::optional<T> timestamp, std::optional<T> error);

   private:
    T k_p_;
    T k_i_;
    T k_d_;

    dsp::integral<T> integrate_;
    dsp::derivative<T> derivate_;
    W integrator_windup_;
    F derivative_low_pass_filter_;
};

template <typename T, typename W, typename F>
pid<T, W, F>::pid(T k_p, T k_i, T k_d) : k_p_(k_p), k_i_(k_i), k_d_(k_d) {}

template <typename T, typename W, typename F>
std::optional<T> pid<T, W, F>::operator()(T timestamp, T error) {
    auto error_area_opt = integrate_(timestamp, error);
    if (!error_area_opt.has_value()) {
        return {};
    }
    auto error_area = error_area_opt.value();

    auto error_filtered_opt = derivative_low_pass_filter_(error);
    if (!error_filtered_opt.has_value()) {
        return {};
    }
    auto error_filtered = error_filtered_opt.value();

    auto error_slope_opt = derivate_(timestamp, error_filtered);
    if (!error_slope_opt.has_value()) {
        return {};
    }
    auto error_slope = error_slope_opt.value();

    T p = k_p_ * error;
    T i = k_i_ * error_area;
    T d = k_d_ * error_slope;

    return p + i + d;
}

template <typename T, typename W, typename F>
std::optional<T> pid<T, W, F>::operator()(std::optional<T> timestamp, std::optional<T> error) {
    if (timestamp.has_value() && error.has_value()) {
        return (*this)(timestamp.value(), error.value());
    }

    return {};
}

} /* namespace dsp */

#endif /* LIBDSP_INCLUDE_DSP_PID_HPP */
