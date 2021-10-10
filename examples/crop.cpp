#include <cmath>
#include <iostream>

#include "dsp/crop.hpp"

int main() {
    dsp::crop::down<float> crop_down(0.10F, 0.0F);

    std::cout << ">title=Crop Down Output Response" << std::endl;
    std::cout << ">x-axis=x" << std::endl;
    std::cout << ">y-axis=y" << std::endl;
    std::cout << ">x-min=0" << std::endl;
    std::cout << ">x-max=700" << std::endl;
    std::cout << ">y-min=-0.1" << std::endl;
    std::cout << ">y-max=1.1" << std::endl;

    float x = 0.0F;
    float y = 0.0F;

    for (unsigned int i = 0; i < 700; i++) {
        x += 1.0F;
        y = 1.0F + std::sin((x / 180.0F) * M_PI);

        auto y1 = 2.0F + crop_down(y);
        std::cout << x << " " << y << " " << y1 << std::endl;
    }

    return 0;
}