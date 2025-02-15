#ifndef LIKELIHOOD_H
#define LIKELIHOOD_H

#include <vector>

#include "function.h"

class Likelihood {
    protected:
        Function* funcToFit;

    public:
        virtual float evaluate(std::vector<float> x, std::vector<float> y) = 0;
        virtual std::vector<float> gradient(std::vector<float> x, std::vector<float> y) = 0;
};

class ChiSquareLikelihood : public Likelihood {
    public:
        ChiSquareLikelihood(Function* func);
        ChiSquareLikelihood();
};

#endif