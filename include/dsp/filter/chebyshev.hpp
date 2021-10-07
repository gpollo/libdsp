#ifndef LIBDSP_INCLUDE_DSP_FILTER_CHEBYCHEV_HPP
#define LIBDSP_INCLUDE_DSP_FILTER_CHEBYCHEV_HPP

#include <array>
#include <type_traits>

#include "dsp/filter/recursive.hpp"
#include "dsp/math.hpp"

namespace dsp::filter::chebyshev {

namespace impl {

template <typename Settings, bool HighPass>
struct chebyshev_coefficient {
    using type         = typename Settings::type;
    using coefficients = filter::recursive_coefficients<type, Settings::POLE_COUNT + 1, Settings::POLE_COUNT>;

    static constexpr unsigned int POLE_COUNT     = Settings::POLE_COUNT;
    static constexpr float PERCENT_RIPPLE        = Settings::PERCENT_RIPPLE;
    static constexpr float SAMPLING_FREQUENCY_HZ = Settings::SAMPLING_FREQUENCY_HZ;
    static constexpr float CUTOFF_FREQUENCY_HZ   = Settings::CUTOFF_FREQUENCY_HZ;
    static constexpr float CUTOFF                = CUTOFF_FREQUENCY_HZ / SAMPLING_FREQUENCY_HZ;

    static_assert(POLE_COUNT % 2 == 0, "pole count must be an odd number");
    static_assert(POLE_COUNT >= 2, "pole count must not be below 2");
    static_assert(POLE_COUNT <= 20, "pole count must not be above 20");
    static_assert(std::is_scalar<type>::value, "type must be scalar");

    struct subroutine_results {
        type a0_;
        type a1_;
        type a2_;
        type b1_;
        type b2_;
    };

    static constexpr subroutine_results subroutine(unsigned int pp) {
        /* NOLINTNEXTLINE(readability-isolate-declaration) */
        type a0 = 0, a1 = 0, a2 = 0, b1 = 0, b2 = 0;
        /* NOLINTNEXTLINE(readability-isolate-declaration) */
        type rp = 0, ip = 0, es = 0, vx = 0, kx = 0;
        /* NOLINTNEXTLINE(readability-isolate-declaration) */
        type t = 0, w = 0, m = 0, d = 0, k = 0, x0 = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
        type fc = static_cast<type>(CUTOFF);
        type np = static_cast<type>(POLE_COUNT);
        type pr = static_cast<type>(PERCENT_RIPPLE);
        type pi = math::get_pi<type>();

        /* calculate the pole location on the unit circle */
        rp = -math::cos(pi / (np * 2.0) + (pp - 1.0) * pi / np);
        ip = math::sin(pi / (np * 2.0) + (pp - 1.0) * pi / np);

        /* wrap from a circule to an ellipse */
        if (pr > 0) {
            es = math::sqrt(math::square<type>(100.0 / (100.0 - pr)) - 1);
            vx = (1.0 / np) * math::ln((1.0 / es) + math::sqrt((1.0 / math::square<type>(es)) + 1.0));
            kx = (1.0 / np) * math::ln((1.0 / es) + math::sqrt((1.0 / math::square<type>(es)) - 1.0));
            kx = (math::exp(kx) + math::exp(-kx)) / 2;
            rp = rp * ((math::exp(vx) - math::exp(-vx)) / 2.0) / kx;
            ip = ip * ((math::exp(vx) + math::exp(-vx)) / 2.0) / kx;
        }

        /* s-domain to z-domain conversion */
        t  = 2.0 * math::tan(1.0 / 2.0);
        w  = 2.0 * pi * fc;
        m  = math::square<type>(rp) + math::square<type>(ip);
        d  = 4.0 - 4.0 * rp * t + m * math::square<type>(t);
        x0 = math::square<type>(t) / d;
        x1 = 2.0 * math::square<type>(t) / d;
        x2 = math::square<type>(t) / d;
        y1 = (8.0 - 2.0 * m * math::square<type>(t)) / d;
        y2 = (-4.0 - 4.0 * rp * t - m * math::square<type>(t)) / d;

        /* low-pass to low-pass or low-pass to high-pass transform */
        if (HighPass) {
            k = -math::cos(w / 2.0 + 1.0 / 2.0) / math::cos(w / 2.0 - 1.0 / 2.0);
        } else {
            k = math::sin(1.0 / 2.0 - w / 2.0) / math::sin(1.0 / 2.0 + w / 2.0);
        }

        d  = 1.0 + y1 * k - y2 * math::square<type>(k);
        a0 = (x0 - x1 * k + x2 * math::square<type>(k)) / d;
        a1 = (-2.0 * x0 * k + x1 + x1 * math::square<type>(k) - 2.0 * x2 * k) / d;
        a2 = (x0 * math::square<type>(k) - x1 * k + x2) / d;
        b1 = (2.0 * k + y1 + y1 * math::square<type>(k) - 2.0 * y2 * k) / d;
        b2 = (-(math::square<type>(k)) - y1 * k + y2) / d;

        if (HighPass) {
            a1 = -a1;
            b1 = -b1;
        }

        return {.a0_ = a0, .a1_ = a1, .a2_ = a2, .b1_ = b1, .b2_ = b2};
    }

    static constexpr coefficients get() {
        /* NOLINTNEXTLINE(readability-isolate-declaration) */
        std::array<type, 22> a{}, b{}, ta{}, tb{};

        for (int i = 0; i < 22; i++) {
            a[i] = 0;
            b[i] = 0;
        }

        a[2] = 1;
        b[2] = 1;

        for (unsigned int pp = 1; pp <= POLE_COUNT / 2; pp++) {
            auto r = subroutine(pp);

            /* add the coefficients to the cascade */
            for (unsigned int i = 0; i < 22; i++) {
                ta[i] = a[i];
                tb[i] = b[i];
            }

            for (unsigned int i = 2; i < 22; i++) {
                a[i] = r.a0_ * ta[i] + r.a1_ * ta[i - 1] + r.a2_ * ta[i - 2];
                b[i] = tb[i] - r.b1_ * tb[i - 1] - r.b2_ * tb[i - 2];
            }
        }

        /* finish combining coefficients */
        b[2] = 0;
        for (unsigned int i = 0; i < 20; i++) {
            a[i] = a[i + 2];
            b[i] = -b[i + 2];
        }

        /* normalize the gain */
        type sa = 0;
        type sb = 0;
        for (unsigned int i = 0; i < 20; i++) {
            if (HighPass) {
                sa = sa + a[i] * math::pow<type>(-1.0, i);
                sb = sb + b[i] * math::pow<type>(-1.0, i);
            } else {
                sa = sa + a[i];
                sb = sb + b[i];
            }
        }

        type gain = sa / (1.0 - sb);
        for (unsigned int i = 0; i < 20; i++) {
            a[i] = a[i] / gain;
        }

        /* copy the coefficients into the output value */

        coefficients coefficients{};

        for (unsigned int i = 0; i < POLE_COUNT + 1; i++) {
            coefficients.a_[i] = a[i];
        }

        for (unsigned int i = 0; i < POLE_COUNT; i++) {
            coefficients.b_[i] = b[i + 1];
        }

        return coefficients;
    }
};

} /* namespace impl */

/**
 * The template parameter `Settings` must provide the following types/methods.
 *
 *    using type = ...;
 *    static constexpr unsigned int POLE_COUNT     = ...;
 *    static constexpr float PERCENT_RIPPLE        = ...;
 *    static constexpr float SAMPLING_FREQUENCY_HZ = ...;
 *    static constexpr float CUTOFF_FREQUENCY_HZ   = ...;
 *
 * This data structure is safe for one writer and multiple readers executing concurrently.
 */
template <typename Settings>
using low_pass = recursive<typename Settings::type, Settings::POLE_COUNT + 1, Settings::POLE_COUNT,
                           impl::chebyshev_coefficient<Settings, false>>;

/**
 * The template parameter `Settings` must provide the following types/methods.
 *
 *    using type = ...;
 *    static constexpr unsigned int POLE_COUNT     = ...;
 *    static constexpr float PERCENT_RIPPLE        = ...;
 *    static constexpr float SAMPLING_FREQUENCY_HZ = ...;
 *    static constexpr float CUTOFF_FREQUENCY_HZ   = ...;
 *
 * This data structure is safe for one writer and multiple readers executing concurrently.
 */
template <typename Settings>
using high_pass = recursive<typename Settings::type, Settings::POLE_COUNT + 1, Settings::POLE_COUNT,
                            impl::chebyshev_coefficient<Settings, true>>;

} /* namespace dsp::filter::chebyshev */

#endif /* LIBDSP_INCLUDE_DSP_FILTER_CHEBYCHEV_HPP */