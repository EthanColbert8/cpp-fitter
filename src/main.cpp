#include <vector>
#include <iostream>
#include <string>
#include <cmath>

#include "polynomials.h"
#include "minimizer.h"
#include "likelihoods.h"

int main() {

    float correct_a = 1.5f;
    float correct_b = 2.0f;
    float correct_c = -1.0f;

    Quadratic* quadratic = new Quadratic();
    ChiSquareLikelihood* chi_square = new ChiSquareLikelihood(quadratic);
    Minimizer* minimizer = new Minimizer(1.0e-6f, 0.1f, 100000);

    std::vector<float> x_values = std::vector<float>(100, 0.0f);
    std::vector<float> y_values = std::vector<float>(100, 0.0f);
    for (int i = 0; i < 100; i++) {
        x_values[i] = i * 0.02f - 1.0f;
        y_values[i] = ((correct_a * x_values[i] * x_values[i]) + (correct_b * x_values[i]) + correct_c);
    }

    // std::vector<float> init = {1.0f, 0.0f, 0.0f};

    std::cout << "Printing initial model predictions." << std::endl;

    for (int i = 0; i < 20; i++) {
        float x = x_values[i];
        float y = quadratic->evaluate(x);
        std::cout << "x: " << x << ", prediction: " << y << ", true y: " << y_values[i] << std::endl;
    }
    std::cout << "\n";

    std::cout << "Attempting minimization." << std::endl;

    std::vector<float> min_params = minimizer->minimize(chi_square, x_values, y_values);
    float min_value = chi_square->evaluate(x_values, y_values);

    std::cout << "Minimization complete. Minimum value is: " << min_value << std::endl;
    std::cout << "Final parameters: " << min_params[0] << ", " << min_params[1] << ", " << min_params[2] << std::endl;

    delete quadratic;
    delete chi_square;
    delete minimizer;

    return 0;
}
