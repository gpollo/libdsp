#include <cmath>
#include <iostream>

#include "dsp/delay-digital-signal.hpp"

int main() {
    dsp::delay_digital_signal<float> rising(dsp::delay_digital_signal<float>::event::RISING_EDGE, 30.0F);
    dsp::delay_digital_signal<float> falling(dsp::delay_digital_signal<float>::event::FALLING_EDGE, 30.0F);

    std::cout << ">title=Output Response vs. Event Type" << std::endl;
    std::cout << ">x-axis=x" << std::endl;
    std::cout << ">y-axis=y" << std::endl;
    std::cout << ">x-min=0" << std::endl;
    std::cout << ">x-max=290" << std::endl;
    std::cout << ">y-min=-0.1" << std::endl;
    std::cout << ">y-max=1.1" << std::endl;

    float x = -50.0F;
    bool y  = false;

    for (unsigned int i = 0; i < 50; i++) {
        x += 1.0F;
        y = false;

        rising(x, y);
        falling(x, y);
    }

    for (unsigned int i = 0; i < 50; i++) {
        x += 1.0F;
        y = false;

        auto y1 = 1.1F + (rising(x, y).value() ? 1.0F : 0.0F);
        auto y2 = 2.2F + (falling(x, y).value() ? 1.0F : 0.0F);
        std::cout << x << " " << y << " " << y1 << " " << y2 << std::endl;
    }

    for (unsigned int i = 0; i < 125; i++) {
        x += 1.0F;
        y = true;

        auto y1 = 1.1F + (rising(x, y).value() ? 1.0F : 0.0F);
        auto y2 = 2.2F + (falling(x, y).value() ? 1.0F : 0.0F);
        std::cout << x << " " << y << " " << y1 << " " << y2 << std::endl;
    }

    for (unsigned int i = 0; i < 125; i++) {
        x += 1.0F;
        y = false;

        auto y1 = 1.1F + (rising(x, y).value() ? 1.0F : 0.0F);
        auto y2 = 2.2F + (falling(x, y).value() ? 1.0F : 0.0F);
        std::cout << x << " " << y << " " << y1 << " " << y2 << std::endl;
    }

    return 0;
}