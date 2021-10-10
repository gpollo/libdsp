#include <cmath>
#include <iostream>

#include "dsp/rate-limiter.hpp"

int main() {
    dsp::rate_limiter<float> limit_positive_slope({}, 0.02F, 0.0001F);
    dsp::rate_limiter<float> limit_negative_slope(-0.01F, {}, 0.0001F);
    dsp::rate_limiter<float> limit_both_slope(-0.03F, 0.04F, 0.0001F);

    std::cout << ">title=Output Response vs. Rate Limiter Type" << std::endl;
    std::cout << ">x-axis=x" << std::endl;
    std::cout << ">y-axis=y" << std::endl;
    std::cout << ">x-min=0" << std::endl;
    std::cout << ">x-max=290" << std::endl;
    std::cout << ">y-min=-0.1" << std::endl;
    std::cout << ">y-max=1.1" << std::endl;

    float x = -10.0F;
    float y = 0.0F;

    for (unsigned int i = 0; i < 5; i++) {
        x += 1.0F;
        y = 0.0F;

        limit_positive_slope(x, y);
        limit_negative_slope(x, y);
        limit_both_slope(x, y);
    }

    for (unsigned int i = 0; i < 50; i++) {
        x += 1.0F;
        y = 0.0F;

        auto y1 = 1.1F + limit_positive_slope(x, y).value();
        auto y2 = 2.2F + limit_negative_slope(x, y).value();
        auto y3 = 3.3F + limit_both_slope(x, y).value();
        std::cout << x << " " << y << " " << y1 << " " << y2 << " " << y3 << std::endl;
    }

    for (unsigned int i = 0; i < 125; i++) {
        x += 1.0F;
        y = 1.0F;

        auto y1 = 1.1F + limit_positive_slope(x, y).value();
        auto y2 = 2.2F + limit_negative_slope(x, y).value();
        auto y3 = 3.3F + limit_both_slope(x, y).value();
        std::cout << x << " " << y << " " << y1 << " " << y2 << " " << y3 << std::endl;
    }

    for (unsigned int i = 0; i < 125; i++) {
        x += 1.0F;
        y = 0.0F;

        auto y1 = 1.1F + limit_positive_slope(x, y).value();
        auto y2 = 2.2F + limit_negative_slope(x, y).value();
        auto y3 = 3.3F + limit_both_slope(x, y).value();
        std::cout << x << " " << y << " " << y1 << " " << y2 << " " << y3 << std::endl;
    }

    return 0;
}