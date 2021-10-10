#ifndef LIBDSP_INCLUDE_DSP_PARTIAL_LINEAR_MAP_HPP
#define LIBDSP_INCLUDE_DSP_PARTIAL_LINEAR_MAP_HPP

#include <optional>

namespace dsp {

/**
 * This simple functor provides a linear mapping only in a specific region.
 * The following graph shows an example of an ascending mapping.
 *
 *     ^ y
 *     |
 *     |          p2--------
 *     |          /
 *     |         /
 *     |--------p1
 *     |                    x
 *     +-------------------->
 *
 * The mapping is between p1 = (x1, y1) and p2 = (x2, y2).
 */
template <typename T>
class partial_linear_map {
   public:
    partial_linear_map(T x1, T x2, T y1, T y2);

    T operator()(T x) const;
    std::optional<T> operator()(std::optional<T> x) const;

    void set_x1(std::optional<T> x);
    void set_x2(std::optional<T> x);
    void set_y1(std::optional<T> y);
    void set_y2(std::optional<T> y);

   private:
    T x1_;
    T x2_;
    T y1_;
    T y2_;
};

template <typename T>
partial_linear_map<T>::partial_linear_map(T x1, T x2, T y1, T y2) : x1_(x1), x2_(x2), y1_(y1), y2_(y2) {}

template <typename T>
T partial_linear_map<T>::operator()(T x) const {
    if (x < x1_) {
        return y1_;
    }

    if (x > x2_) {
        return y2_;
    }

    T delta_x = x2_ - x1_;
    T delta_y = y2_ - y1_;
    T y       = ((delta_y * (x - x1_)) / delta_x) + y1_;

    return y;
}

template <typename T>
std::optional<T> partial_linear_map<T>::operator()(std::optional<T> x) const {
    if (x.has_value()) {
        return (*this)(x.value());
    }

    return {};
}

template <typename T>
inline void partial_linear_map<T>::set_x1(std::optional<T> x) {
    x1_ = x.has_value() ? x.value() : x1_;
}

template <typename T>
inline void partial_linear_map<T>::set_x2(std::optional<T> x) {
    x2_ = x.has_value() ? x.value() : x2_;
}

template <typename T>
inline void partial_linear_map<T>::set_y1(std::optional<T> y) {
    y1_ = y.has_value() ? y.value() : y1_;
}

template <typename T>
inline void partial_linear_map<T>::set_y2(std::optional<T> y) {
    y2_ = y.has_value() ? y.value() : y2_;
}

} /* namespace dsp */

#endif /* LIBDSP_INCLUDE_DSP_PARTIAL_LINEAR_MAP_HPP */
