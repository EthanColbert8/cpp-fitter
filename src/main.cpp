#include <vector>
#include <iostream>
#include <string>

#include "polynomials.h"
#include "minimizer.h"

int main() {
    Quadratic* x_squared = new Quadratic(1.0f, -2.0f, 1.0f);
    Minimizer* minimizer = new Minimizer();

    std::cout << "Attempting minimization." << std::endl;

    float min_x = minimizer->minimize(x_squared, 0.5f, 2.5f, 1.0e-5f, 1.0e-3f, 100000);
    float min_y = x_squared->evaluate(min_x);

    std::cout << "Minimum coordinates are: x=" << min_x << ", y=" << min_y << std::endl;

    delete x_squared;
    delete minimizer;

    return 0;
}