#ifndef POLYNOMIALS_H
#define POLYNOMIALS_H

#include "function.h"
#include <string>
#include <vector>

class Paraboloid3D : public Function {
    private:
        float ax;
        float bx;
        float ay;
        float by;
        float az;
        float bz;
        float c;
    
    public:
        static const int num_params = 7;

        Paraboloid3D(std::vector<float> params);
        Paraboloid3D();

        float evaluate(std::vector<float> x) override;
        float evaluate(float x, float y, float z); // few independent variables, this is feasible

        std::vector<float> gradient(std::vector<float> x) override;

        std::vector<float> getParams() override;
        void setParams(std::vector<float> new_params) override;

        std::string toString() override;
};

class Quadratic : public Function {
    private:
        // float a;
        // float b;
        // float c;
        std::vector<float> params;
    
    public:
        static const int num_params = 3;

        Quadratic(float a, float b, float c);
        Quadratic(std::vector<float> init_params);
        Quadratic();

        void fit(std::vector<float> x, std::vector<float> y);
        float evaluate(std::vector<float> x) override;
        float evaluate(float x); // single-variable function can also take single value as argument

        std::vector<float> gradient(std::vector<float> x) override;

        std::vector<float> getParams() override;
        void setParams(std::vector<float> new_params) override;

        std::string toString() override;
};

#endif
