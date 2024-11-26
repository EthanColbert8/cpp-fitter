#include <vector>
#include <iostream>
#include <string>

#include "polynomials.h"

int main() {
    Quadratic* x_squared = new Quadratic();

    std::cout << "Initial parameters: " << x_squared->toString() << std::endl;

    std::vector<float> x_values = {1.0f, 2.0f, 3.0f, 4.0f};
    std::vector<float> y_values = {2.0f, 5.0f, 10.0f, 17.0f};

    x_squared->fit(x_values, y_values);

    delete x_squared;

    return 0;
}