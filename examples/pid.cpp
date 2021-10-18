#include <iostream>
#include <random>

#include "dsp/filter/all-pass.hpp"
#include "dsp/filter/windowed-sinc.hpp"
#include "dsp/math.hpp"
#include "dsp/pid.hpp"
#include "dsp/rate-limiter.hpp"
#include "dsp/window/hamming.hpp"

template <typename T>
class mass_spring_damper {
   public:
    T operator()(const T timestamp, const T force) {
        T step         = timestamp - last_timestamp_;
        T acceleration = (force / mass_) - (spring_ / mass_) * last_position_ - (damper_ / mass_) * last_speed_;
        T speed        = last_speed_ + step * acceleration;
        T position     = last_position_ + step * speed;

        last_timestamp_ = timestamp;
        last_position_  = position;
        last_speed_     = speed;

        return position;
    }

   private:
    const T mass_   = static_cast<T>(1);
    const T spring_ = static_cast<T>(10);
    const T damper_ = static_cast<T>(20);

    T last_timestamp_ = static_cast<T>(0);
    T last_position_  = static_cast<T>(0);
    T last_speed_     = static_cast<T>(0);
};

template <typename T, unsigned int N>
class filter_settings {
   public:
    using type                                   = T;
    using window                                 = dsp::window::hamming_coefficients<T, N>;
    static constexpr unsigned int SAMPLE_COUNT   = N;
    static constexpr float SAMPLING_FREQUENCY_HZ = static_cast<T>(1000);
    static constexpr float CUTOFF_FREQUENCY_HZ   = static_cast<T>(10);
};

int main() {
    std::cout.precision(10);
    std::random_device random_device{};
    std::mt19937 random_generator{random_device()};
    std::normal_distribution<double> noise{0.0, 0.001};

    using low_pass_filter = dsp::filter::windowed_sinc::low_pass<filter_settings<double, 19>>;

    dsp::pid<double, dsp::filter::all_pass<double>> control1(500.0, 0.0, 0.0);
    dsp::pid<double, dsp::filter::all_pass<double>> control2(350.0, 100.0, 50.0);
    dsp::pid<double, dsp::filter::all_pass<double>> control3(350.0, 0.0, 100.0);
    dsp::pid<double, low_pass_filter> control4(350.0, 0.0, 100.0);

    dsp::rate_limiter<double> limiter1(-10.0, 10.0, 0.00001);
    dsp::rate_limiter<double> limiter2(-10.0, 10.0, 0.00001);
    dsp::rate_limiter<double> limiter3(-10.0, 10.0, 0.00001);
    dsp::rate_limiter<double> limiter4(-10.0, 10.0, 0.00001);

    mass_spring_damper<double> plant1;
    mass_spring_damper<double> plant2;
    mass_spring_damper<double> plant3;
    mass_spring_damper<double> plant4;

    std::cout << ">title=Mass-Spring-Damper System vs. PID Settings" << std::endl;
    std::cout << ">x-axis=Time (s)" << std::endl;
    std::cout << ">y-axis=Position (m)" << std::endl;
    std::cout << ">x-min=0" << std::endl;
    std::cout << ">x-max=20" << std::endl;
    std::cout << ">title-4=$K_p=500$, $K_i=\\phantom{0}\\phantom{0}0$, $K_d=\\phantom{0}\\phantom{0}0$" << std::endl;
    std::cout << ">title-5=$K_p=350$, $K_i=100$, $K_d=\\phantom{0}50$" << std::endl;
    std::cout << ">title-6=$K_p=350$, $K_i=\\phantom{0}\\phantom{0}0$, $K_d=100$" << std::endl;
    std::cout << ">title-7=$K_p=350$, $K_i=\\phantom{0}\\phantom{0}0$, $K_d=100$, filtered" << std::endl;

    double time   = -20;
    double target = 0.0F;

    double error1 = 0.0;
    double error2 = 0.0;
    double error3 = 0.0;
    double error4 = 0.0;

    double position1 = 0.0;
    double position2 = 0.0;
    double position3 = 0.0;
    double position4 = 0.0;

    for (unsigned int i = 0; i < 20; i++) {
        time += 1.0;
        error1 = 0.0;
        error2 = 0.0;
        error3 = 0.0;
        error4 = 0.0;

        control1(time, error1);
        control2(time, error2);
        control3(time, error3);
        control4(time, error4);

        limiter1(time, 0.0);
        limiter2(time, 0.0);
        limiter3(time, 0.0);
        limiter4(time, 0.0);
    }

    target = 0.1;
    for (unsigned int i = 0; i < 10000; i++) {
        time += 0.001;
        error1 = target - position1;
        error2 = target - position2;
        error3 = target - position3;
        error4 = target - position4;

        auto force1 = limiter1(time, control1(time, error1).value()).value();
        auto force2 = limiter2(time, control2(time, error2).value()).value();
        auto force3 = limiter3(time, control3(time, error3).value()).value();
        auto force4 = limiter4(time, control4(time, error4).value()).value();

        force1 = std::min(std::max(-10.0, force1), 10.0);
        force2 = std::min(std::max(-10.0, force2), 10.0);
        force3 = std::min(std::max(-10.0, force3), 10.0);
        force4 = std::min(std::max(-10.0, force4), 10.0);

        position1 = plant1(time, force1) + noise(random_generator);
        position2 = plant2(time, force2) + noise(random_generator);
        position3 = plant3(time, force3) + noise(random_generator);
        position4 = plant4(time, force4) + noise(random_generator);

        std::cout << time;
        // std::cout << " " << (force1 / 100.0 - 0.0);
        // std::cout << " " << (force2 / 100.0 - 0.5);
        // std::cout << " " << (force3 / 100.0 - 1.0);
        // std::cout << " " << (force4 / 100.0 - 1.5);
        std::cout << " " << (target - 0.0);
        std::cout << " " << (target - 0.5);
        std::cout << " " << (target - 1.0);
        std::cout << " " << (target - 1.5);
        std::cout << " " << (position1 - 0.0);
        std::cout << " " << (position2 - 0.5);
        std::cout << " " << (position3 - 1.0);
        std::cout << " " << (position4 - 1.5);
        std::cout << std::endl;
    }

    target = -0.2;
    for (unsigned int i = 0; i < 10000; i++) {
        time += 0.001;
        error1 = target - position1;
        error2 = target - position2;
        error3 = target - position3;
        error4 = target - position4;

        auto force1 = limiter1(time, control1(time, error1).value()).value();
        auto force2 = limiter2(time, control2(time, error2).value()).value();
        auto force3 = limiter3(time, control3(time, error3).value()).value();
        auto force4 = limiter4(time, control4(time, error4).value()).value();

        force1 = std::min(std::max(-10.0, force1), 10.0);
        force2 = std::min(std::max(-10.0, force2), 10.0);
        force3 = std::min(std::max(-10.0, force3), 10.0);
        force4 = std::min(std::max(-10.0, force4), 10.0);

        position1 = plant1(time, force1) + noise(random_generator);
        position2 = plant2(time, force2) + noise(random_generator);
        position3 = plant3(time, force3) + noise(random_generator);
        position4 = plant4(time, force4) + noise(random_generator);

        std::cout << time;
        // std::cout << " " << (force1 / 100.0 - 0.0);
        // std::cout << " " << (force2 / 100.0 - 0.5);
        // std::cout << " " << (force3 / 100.0 - 1.0);
        // std::cout << " " << (force4 / 100.0 - 1.5);
        std::cout << " " << (target - 0.0);
        std::cout << " " << (target - 0.5);
        std::cout << " " << (target - 1.0);
        std::cout << " " << (target - 1.5);
        std::cout << " " << (position1 - 0.0);
        std::cout << " " << (position2 - 0.5);
        std::cout << " " << (position3 - 1.0);
        std::cout << " " << (position4 - 1.5);
        std::cout << std::endl;
    }

    return 0;
}