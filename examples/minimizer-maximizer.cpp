#include <cmath>
#include <iostream>

#include "dsp/maximizer.hpp"
#include "dsp/minimizer.hpp"

int main() {
    dsp::minimizer<float> min;
    dsp::maximizer<float> max;

    std::cout << ">title=Minimizer and Maximizer Outputs" << std::endl;
    std::cout << ">x-axis=x" << std::endl;
    std::cout << ">y-axis=y" << std::endl;
    std::cout << ">x-min=0" << std::endl;
    std::cout << ">x-max=2000" << std::endl;
    std::cout << ">y-min=-0.1" << std::endl;
    std::cout << ">y-max=1.1" << std::endl;

    float x = -1.0F;
    float y = 0.0F;

    for (unsigned int i = 0; i < 2001; i++) {
        x += 1.0F;
        y = x * std::sin((x / 180.0F) * M_PI);

        auto y1 = min(y);
        auto y2 = max(y);
        std::cout << x << " " << y << " " << y1 << " " << y2 << std::endl;
    }

    return 0;
}