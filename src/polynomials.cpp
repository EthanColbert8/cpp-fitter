#include <iostream>
#include <vector>
#include <string>

#include "polynomials.h"

Quadratic::Quadratic(float a, float b, float c) : a(a), b(b), c(c) {}
Quadratic::Quadratic() : a(1.0f), b(0.0f), c(0.0f) {}

void Quadratic::fit(std::vector<float> x, std::vector<float> y) {
    std::cout << "Quadratic class fit function reached.\n";
}

// HERE: implement other functions of Quadratic class.