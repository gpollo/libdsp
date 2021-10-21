#ifndef LIBDSP_INCLUDE_DSP_WINDUP_NONE_HPP
#define LIBDSP_INCLUDE_DSP_WINDUP_NONE_HPP

namespace dsp::windup {

/**
 * This simple functor disable the integrator windup in a PID control loop.
 */
template <typename T>
class none {
   public:
    using type = T;

    type operator()(type timestamp, type error, type integrator_value);
};

template <typename T>
typename none<T>::type none<T>::operator()(type timestamp, type error, type integrator_value) {
    return integrator_value;
}

} /* namespace dsp::windup */

#endif /* LIBDSP_INCLUDE_DSP_WINDUP_NONE_HPP */