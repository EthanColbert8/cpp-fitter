#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "polynomials.h"

Quadratic::Quadratic(float a, float b, float c) : a(a), b(b), c(c) {}
Quadratic::Quadratic() : a(1.0f), b(0.0f), c(0.0f) {}

void Quadratic::fit(std::vector<float> x, std::vector<float> y) {
    std::cout << "Quadratic class fit function reached." << std::endl; // debug print
    if (x.size() != y.size()) {
        throw std::runtime_error("Arrays of x and y values not of equal length.");
    }

    int N = x.size();

    float x0 = static_cast<float>(N); // to multiply/divide by floats
    float x1 = 0.0f;
    float x2 = 0.0f;
    float x3 = 0.0f;
    float x4 = 0.0f;
    float y0 = 0.0f;
    float y1 = 0.0f;
    float y2 = 0.0f;

    for (int i = 0; i < N; i++) {
        x1 += x[i];
        x2 += (x[i] * x[i]);
        x3 += (x[i] * x[i] * x[i]);
        x4 += (x[i] * x[i] * x[i] * x[i]);

        y0 += y[i];
        y1 += (y[i] * x[i]);
        y2 += (y[i] * x[i] * x[i]);
    }

    float denominator = (x2*x2*x2 - 2.0f*x1*x2*x3 + x0*x3*x3 + x1*x1*x4 - x0*x2*x4);

    a = (x2*x2*y0 - x1*x3*y0 - x1*x2*y1 + x0*x3*y1 + x1*x1*y2 - x0*x2*y2) / denominator;
    b = (x1*x4*y0 - x2*x3*y0 + x2*x2*y1 - x0*x4*y1 - x1*x2*y2 + x0*x3*y2) / denominator;
    c = (x3*x3*y0 - x2*x4*y0 - x2*x3*y1 + x1*x4*y1 + x2*x2*y2 - x1*x3*y2) / denominator;

    std::cout << "Finished fit. Parameters updated to: " << toString() << std::endl; // debug print
}

float Quadratic::evaluate(float x) {
    return ((a*x*x) + (b*x) + c);
}

std::string Quadratic::toString() {
    std::ostringstream string_builder;
    string_builder << std::fixed << std::setprecision(3);

    string_builder << "a: " << a << ", b: " << b << ", c: " << c;

    return string_builder.str();
}