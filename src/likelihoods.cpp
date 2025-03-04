#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "likelihoods.h"

/**
 * ChiSquareLikelihood class implementation.
 */
ChiSquareLikelihood::ChiSquareLikelihood(Function* func) {
    funcToFit = func;
}
ChiSquareLikelihood::ChiSquareLikelihood() {
    funcToFit = nullptr;
}

float ChiSquareLikelihood::evaluate(std::vector<float> x) {
    if (funcToFit == nullptr) {
        throw std::runtime_error("Function to fit not set.");
    }

    throw std::runtime_error("ChiSquareLikelihood::evaluate(std::vector<float> x) not implemented.");
}

std::vector<float> ChiSquareLikelihood::gradient(std::vector<float> x) {
    if (funcToFit == nullptr) {
        throw std::runtime_error("Function to fit not set.");
    }

    throw std::runtime_error("ChiSquareLikelihood::gradient(std::vector<float> x) not implemented.");
}

float ChiSquareLikelihood::evaluate(std::vector<float> x, std::vector<float> y) {
    if (funcToFit == nullptr) {
        throw std::runtime_error("Function to fit not set.");
    }

    int N = x.size();

    if (N != y.size()) {
        throw std::runtime_error("Vectors of x and y values not of equal length.");
    }

    float chi_square = 0.0f;

    for (int i = 0; i < N; i++) {
        float y_fit = funcToFit->evaluate({x[i]});
        chi_square += ((y[i] - y_fit) * (y[i] - y_fit));
    }

    return chi_square;
}

std::vector<float> ChiSquareLikelihood::gradient(std::vector<float> x, std::vector<float> y) {
    if (funcToFit == nullptr) {
        throw std::runtime_error("Function to fit not set.");
    }

    int N = x.size();

    if (N != y.size()) {
        throw std::runtime_error("Vectors of x and y values not of equal length.");
    }

    //int num_params = funcToFit->num_params; // something's wrong here, not sure what
    int num_params = funcToFit->getParams().size();

    std::vector<float> gradient = std::vector<float>(num_params, 0.0f);

    // The core: each term in the gradient of chi-squared is
    // 2 * (y_fit - y) * (gradient of the function to fit wrt the corresponding parameter).
    for (int i = 0; i < N; i++) {
        float y_fit = funcToFit->evaluate({x[i]});
        std::vector<float> func_gradient = funcToFit->gradient({x[i]});


        for (int j = 0; j < num_params; j++) {
            gradient[j] += 2.0f * (y_fit - y[i]) * func_gradient[j];
        }
    }

    return gradient;
}

std::vector<float> ChiSquareLikelihood::getParams() {
    return funcToFit->getParams();
}

void ChiSquareLikelihood::setParams(std::vector<float> new_params) {
    funcToFit->setParams(new_params);
}

std::string ChiSquareLikelihood::toString() {
    std::stringstream string_builder;
    string_builder << "Chi-square likelihood function with function to fit: " << funcToFit->toString();
    return string_builder.str();
}