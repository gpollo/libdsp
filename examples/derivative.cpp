#include <iostream>

#include "dsp/derivative.hpp"
#include "dsp/math.hpp"

template <typename T>
T function(T x) {
    return dsp::math::sin(x) * dsp::math::cos(x) * dsp::math::cos(x) / (x * x + 1);
}

int main() {
    dsp::derivative<float> first_order;
    dsp::derivative<float> second_order;

    std::cout << ">title=Derivative Examples" << std::endl;
    std::cout << ">x-axis=time" << std::endl;
    std::cout << ">y-axis=position" << std::endl;
    std::cout << ">x-min=-5" << std::endl;
    std::cout << ">x-max=5" << std::endl;

    float x = -5.10F;

    for (unsigned int i = 0; i < 10; i++) {
        x += 0.01F;

        second_order(x, first_order(x, function(x)));
    }

    for (unsigned int i = 0; i < 1000; i++) {
        x += 0.01F;
        auto y   = function(x);
        auto yp  = first_order(x, y).value();
        auto ypp = second_order(x, yp).value();

        std::cout << x << " " << y << " " << (yp - 2.0F) << " " << (ypp - 5.0F) << std::endl;
    }

    return 0;
}