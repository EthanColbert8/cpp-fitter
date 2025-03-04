#ifndef MINIMIZER_H
#define MINIMIZER_H

#include <vector>
#include <string>

#include "function.h"
#include "likelihoods.h"

class Minimizer {
    private:
        float tol;
        float step;
        int max_iter;

    public:
        Minimizer(float tol, float step, int max_iter);
        Minimizer();

        //std::vector<float> minimize(Function* func);
        std::vector<float> minimize(Likelihood* func, std::vector<float> x, std::vector<float> y);
        std::vector<float> minimize(Function* func, std::vector<float> init);

        std::string toString();

        virtual ~Minimizer() {}
};

// class Minimizer1D {
//     private:
//         float tol;
//         float step;
//         int max_iter;
    
//     public:
//         Minimizer1D(float tol, float step, int max_iter);
//         Minimizer1D();

//         float minimize(Function* func);
//         float minimize(Function* func, float minx, float maxx);
//         //float minimize(Function* func, float minx, float maxx, float tol, float step, int max_iter);

//         std::string toString();

//         virtual ~Minimizer1D() {}
// };

#endif
