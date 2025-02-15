#include <iostream>
#include <stdexcept>
// #include <vector>
// #include <string>
// #include <sstream>
// #include <iomanip>

#include "minimizer.h"

Minimizer::Minimizer() {}

float Minimizer::minimize(Function* func) {
    return minimize(func, 0.0f, 1000.0f, 1.0e-5f, 1.0e-4f, 100000);
}

float Minimizer::minimize(Function* func, float minx, float maxx) {
    return minimize(func, minx, maxx, 1.0e-5f, 1.0e-4f, 100000);
}

float Minimizer::minimize(Function* func, float minx, float maxx, float tol, float step, int max_iter) {
    //std::cout << "Minimizer class minimize function reached." << std::endl; // debug print

    float x = (minx + maxx) / 2.0f;
    float f = func->evaluate(x);
    float df = func->derivative(x);

    float min_value_x = x;
    float min_value_f = f;

    int current_iter = 0;
    while (std::abs(df) > tol) {
        // The core of the method: minimize the function by stepping down the gradient.
        x -= step * df;
        f = func->evaluate(x);
        df = func->derivative(x);

        if (f < min_value_f) {
            min_value_x = x;
            min_value_f = f;
        }

        current_iter++;
        if (current_iter > max_iter) {
            std::cout << "Maximum iterations reached." << std::endl;
            break;
        }
    }

    std::cout << "Finished in " << current_iter << " iterations." << std::endl;

    return min_value_x;
}

std::string Minimizer::toString() {
    return "Minimizer object";
}