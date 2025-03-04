#ifndef LIKELIHOODS_H
#define LIKELIHOODS_H

#include <vector>

#include "function.h"

class Likelihood : public Function {
    protected:
        Function* funcToFit;

    public:
        static const int num_params = -1;

        virtual float evaluate(std::vector<float> x, std::vector<float> y) = 0;
        virtual std::vector<float> gradient(std::vector<float> x, std::vector<float> y) = 0;

        virtual ~Likelihood() {}
};

class ChiSquareLikelihood : public Likelihood {
    public:
        ChiSquareLikelihood(Function* func);
        ChiSquareLikelihood();

        float evaluate(std::vector<float> x) override;
        std::vector<float> gradient(std::vector<float> x) override;

        float evaluate(std::vector<float> x, std::vector<float> y) override;
        std::vector<float> gradient(std::vector<float> x, std::vector<float> y) override;

        std::vector<float> getParams() override;
        void setParams(std::vector<float> new_params) override;

        std::string toString() override;
};

#endif
