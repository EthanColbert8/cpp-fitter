#ifndef POLYNOMIALS_H
#define POLYNOMIALS_H

#include "function.h"
#include <string>
#include <vector>

class Quadratic : public Function {
    private:
        float a;
        float b;
        float c;
    
    public:
        Quadratic(float a, float b, float c);
        Quadratic();

        void fit(std::vector<float> x, std::vector<float> y) override;
        std::string print_params() override;
        float evaluate(float x) override;
};


#endif