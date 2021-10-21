#ifndef LIBDSP_INCLUDE_DSP_WINDUP_BOUND_HPP
#define LIBDSP_INCLUDE_DSP_WINDUP_BOUND_HPP

namespace dsp::windup {

/**
 * This simple functor bounds the integrator value in a PID control loop.
 *
 * The template parameter `Settings` must provide the following types/attributes.
 *
 *    using type = ...;
 *    static constexpr type MIN = ...;
 *    static constexpr type MAX = ...;
 */
template <typename Settings>
class bound {
   public:
    using type = typename Settings::type;

    type operator()(type timestamp, type error, type integrator_value);
};

template <typename Settings>
typename bound<Settings>::type bound<Settings>::operator()(type timestamp, type error, type integrator_value) {
    if (integrator_value < Settings::MIN) {
        return Settings::MIN;
    }

    if (Settings::MAX < integrator_value) {
        return Settings::MAX;
    }

    return integrator_value;
}

} /* namespace dsp::windup */

#endif /* LIBDSP_INCLUDE_DSP_WINDUP_BOUND_HPP */