#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "polynomials.h"

/**
 * Paraboloid3D class implementation.
 */
Paraboloid3D::Paraboloid3D(std::vector<float> params) {
    if (params.size() != 7) {
        throw std::runtime_error("Parameter vector must have length 7.");
    }

    ax = params[0];
    bx = params[1];
    ay = params[2];
    by = params[3];
    az = params[4];
    bz = params[5];
    c = params[6];
}
Paraboloid3D::Paraboloid3D() : ax(1.0f), bx(0.0f), ay(1.0f), by(0.0f), az(1.0f), bz(0.0f), c(0.0f) {}

float Paraboloid3D::evaluate(std::vector<float> x) {
    if (x.size() != 3) {
        throw std::runtime_error("Input vector must have length 3.");
    }

    float x_value = x[0];
    float y_value = x[1];
    float z_value = x[2];

    return ((ax*x_value*x_value) + (bx*x_value) + (ay*y_value*y_value) + (by*y_value) + (az*z_value*z_value) + (bz*z_value) + c);
}

float Paraboloid3D::evaluate(float x, float y, float z) {
    return ((ax*x*x) + (bx*x) + (ay*y*y) + (by*y) + (az*z*z) + (bz*z) + c);
}

std::vector<float> Paraboloid3D::gradient(std::vector<float> x) {
    if (x.size() != 3) {
        throw std::runtime_error("Input vector must have length 3.");
    }

    float x_value = x[0];
    float y_value = x[1];
    float z_value = x[2];

    float dx = (2.0f * ax * x_value) + bx;
    float dy = (2.0f * ay * y_value) + by;
    float dz = (2.0f * az * z_value) + bz;

    std::vector<float> gradient = {dx, dy, dz};
    return gradient;
}

std::vector<float> Paraboloid3D::getParams() {
    std::vector<float> params = {ax, bx, ay, by, az, bz, c};
    return params;
}

void Paraboloid3D::setParams(std::vector<float> new_params) {
    if (new_params.size() != 7) {
        throw std::runtime_error("Parameter vector must have length 7.");
    }

    ax = new_params[0];
    bx = new_params[1];
    ay = new_params[2];
    by = new_params[3];
    az = new_params[4];
    bz = new_params[5];
    c = new_params[6];
}

std::string Paraboloid3D::toString() {
    std::ostringstream string_builder;
    string_builder << std::fixed << std::setprecision(3);

    string_builder << "3D paraboloid. ax: " << ax << ", bx: " << bx << ", ay: " << ay << ", by: " << by << ", az: " << az << ", bz: " << bz << ", c: " << c;

    return string_builder.str();
}

/**
 * Quadratic class implementation.
 */
Quadratic::Quadratic(std::vector<float> init_params) {
    if (init_params.size() != 3) {
        throw std::runtime_error("Parameter vector must have length 3.");
    }

    params = init_params;
}
Quadratic::Quadratic(float a, float b, float c) {
    params = {a, b, c};
}
Quadratic::Quadratic() {
    params = {1.0f, 0.0f, 0.0f};
}

/**
 * Performs an exact chi-square fit of the quadratic to data,
 * given as vectors of x and y values.
 */
void Quadratic::fit(std::vector<float> x, std::vector<float> y) {
    //std::cout << "Quadratic class fit function reached." << std::endl; // debug print

    int N = x.size();

    if (N != y.size()) {
        throw std::runtime_error("Vectors of x and y values not of equal length.");
    }

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

    float a = (x2*x2*y0 - x1*x3*y0 - x1*x2*y1 + x0*x3*y1 + x1*x1*y2 - x0*x2*y2) / denominator;
    float b = (x1*x4*y0 - x2*x3*y0 + x2*x2*y1 - x0*x4*y1 - x1*x2*y2 + x0*x3*y2) / denominator;
    float c = (x3*x3*y0 - x2*x4*y0 - x2*x3*y1 + x1*x4*y1 + x2*x2*y2 - x1*x3*y2) / denominator;
    params = {a, b, c};

    //std::cout << "Finished fit. Parameters updated to: " << toString() << std::endl; // debug print
}

float Quadratic::evaluate(std::vector<float> x) {
    float x_value = x[0];
    return ((params[0]*x_value*x_value) + (params[1]*x_value) + params[2]);
}

float Quadratic::evaluate(float x) {
    return ((params[0]*x*x) + (params[1]*x) + params[2]);
}

std::vector<float> Quadratic::gradient(std::vector<float> x) {
    float x_value = x[0];

    float da = x_value*x_value;
    float db = x_value;
    float dc = 1.0f;

    std::vector<float> gradient = {da, db, dc};
    return gradient;
}

std::vector<float> Quadratic::getParams() {
    return params; 
}

void Quadratic::setParams(std::vector<float> new_params) {
    if (new_params.size() != 3) {
        throw std::runtime_error("Parameter vector must have length 3.");
    }

    params = new_params;
}

std::string Quadratic::toString() {
    std::ostringstream string_builder;
    string_builder << std::fixed << std::setprecision(3);

    string_builder << "Quadratic polynomial. a: " << params[0] << ", b: " << params[1] << ", c: " << params[2];

    return string_builder.str();
}