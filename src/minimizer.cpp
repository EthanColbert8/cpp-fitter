#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "minimizer.h"

// Gotta declare helper functions up here.
//std::vector<float> normalize(std::vector<float> vec);
float mag(std::vector<float> vec);
//float fast_rsqrt(float x);

/**
 * Minimizer class implementation. 
 */
Minimizer::Minimizer(float tol, float step, int max_iter) : tol(tol), step(step), max_iter(max_iter) {}
Minimizer::Minimizer() : tol(1.0e-5f), step(1.0e-4f), max_iter(100000) {}

std::vector<float> Minimizer::minimize(Likelihood* func, std::vector<float> x, std::vector<float> y) {
    std::cout << "Reached minimize function with likelihood." << std::endl; // debug print

    std::vector<float> current_params = func->getParams();
    float value = func->evaluate(x, y);
    std::vector<float> grad = func->gradient(x, y);

    std::vector<float> min_params = current_params;
    float min_value = value;

    int current_iter = 0;
    while (mag(grad) > tol) {
        for (int i = 0; i < current_params.size(); i++) {
            current_params[i] -= step * grad[i];
        }

        func->setParams(current_params);

        value = func->evaluate(x, y);
        grad = func->gradient(x, y);

        if (value < min_value) {
            min_params = current_params;
            min_value = value;
        }

        current_iter++;
        if (current_iter >= max_iter) {
            std::cout << "Maximum iterations reached." << std::endl;
            break;
        }

        // Trying to debug why things don't seem to be updating.
        std::cout << "After " << current_iter << " iterations, gradient magnitude is: " << mag(grad) << std::endl;
        std::cout << "Current params: " << current_params[0] << ", " << current_params[1] << ", " << current_params[2] << std::endl;
        std::cout << "Minimum params: " << min_params[0] << ", " << min_params[1] << ", " << min_params[2] << std::endl;
        std::cout << "Current value: " << value << ", Minimum value: " << min_value << std::endl;
        std::cout << "Current gradient: " << grad[0] << ", " << grad[1] << ", " << grad[2] << std::endl;
        std::cout << '\n';
    }

    std::cout << "Finished in " << current_iter << " iterations. Gradient magnitude is: " << mag(grad) << std::endl; // debug print

    return min_params;
}

std::vector<float> Minimizer::minimize(Function* func, std::vector<float> init) {
    // std::cout << "Minimizer class minimize function reached." << std::endl; // debug print

    std::vector<float> params = init;
    float value = func->evaluate(params);
    std::vector<float> grad = func->gradient(params);

    std::vector<float> min_params = params;
    float min_value = value;

    int current_iter = 0;
    while (mag(grad) > tol) {

        for (int i = 0; i < params.size(); i++) {
            params[i] -= step * grad[i];
        }

        value = func->evaluate(params);
        grad = func->gradient(params);

        if (value < min_value) {
            min_params = params;
            min_value = value;
        }

        current_iter++;
        if (current_iter >= max_iter) {
            std::cout << "Maximum iterations reached." << std::endl;
            break;
        }

        // // Trying to debug why things don't seem to be updating.
        // std::cout << "After " << current_iter << " iterations, gradient magnitude is: " << mag(grad) << std::endl;
        // std::cout << "Current params: " << params[0] << ", " << params[1] << ", " << params[2] << std::endl;
        // std::cout << "Minimum params: " << min_params[0] << ", " << min_params[1] << ", " << min_params[2] << std::endl;
        // std::cout << "Current value: " << value << ", Minimum value: " << min_value << std::endl;
        // std::cout << "Current gradient: " << grad[0] << ", " << grad[1] << ", " << grad[2] << std::endl;
        // std::cout << '\n';
    }

    std::cout << "Finished in " << current_iter << " iterations. Gradient magnitude is: " << mag(grad) << std::endl; // debug print

    return min_params;
}

std::string Minimizer::toString() {
    std::ostringstream string_builder;
    string_builder << std::scientific << std::setprecision(2);

    string_builder << "Minimizer object. tol: " << tol << ", step: " << step << ", max_iter: " << max_iter;

    return string_builder.str();
}

// std::vector<float> normalize(std::vector<float> vec) {
//     std::vector<float> vec_out = vec; // should be doing a copy

//     float norm = 0.0f;
//     for (int i = 0; i < vec.size(); i++) {
//         norm += vec[i] * vec[i];
//     }
//     norm = fast_rsqrt(norm);

//     for (int i = 0; i < vec.size(); i++) {
//         vec_out[i] *= norm;
//     }

//     return vec_out;
// }

float mag(std::vector<float> vec) {
    float mag = 0.0f;
    for (int i = 0; i < vec.size(); i++) {
        mag += vec[i] * vec[i];
    }
    return std::sqrt(mag);
}

// /**
//  * Accesses the rsqrtss instruction on x86-64 processors to get the
//  * reciprocal square root faster than a standard sqrt call.
//  */
// float fast_rsqrt(float x) {
//     float rssqrt_x;
//     __asm__("rsqrtss %1, %0" : "=x" (rssqrt_x) : "x" (x));
//     return rssqrt_x;
// }

/*
Minimizer1D::Minimizer1D(float tol, float step, int max_iter) : tol(tol), step(step), max_iter(max_iter) {}
Minimizer1D::Minimizer1D() : tol(1.0e-5f), step(1.0e-4f), max_iter(100000) {}

float Minimizer1D::minimize(Function* func) {
    return minimize(func, 0.0f, 1000.0f);
}

float Minimizer1D::minimize(Function* func, float minx, float maxx) {
    //std::cout << "Minimizer1D class minimize function reached." << std::endl; // debug print

    float x = (minx + maxx) / 2.0f;
    float f = func->evaluate(x);
    float df = func->derivative(x);

    float min_value_x = x;
    float min_value_f = f;

    std::cout << "Initial guess: x = " << x << ", f(x) = " << f << std::endl;

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

    std::cout << "Finished in " << current_iter << " iterations. Gradient is: " << df << std::endl;

    return min_value_x;
}

std::string Minimizer1D::toString() {
    std::ostringstream string_builder;
    string_builder << std::scientific << std::setprecision(2);

    string_builder << "Minimizer1D object. tol: " << tol << ", step: " << step << ", max_iter: " << max_iter;

    return string_builder.str();
}
*/
