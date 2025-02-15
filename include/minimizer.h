#ifndef MINIMIZER_H
#define MINIMIZER_H

#include <vector>
#include <string>

#include "function.h"

class Minimizer {
    public:
        Minimizer();

        float minimize(Function* func);
        float minimize(Function* func, float minx, float maxx);
        float minimize(Function* func, float minx, float maxx, float tol, float step, int max_iter);
        std::string toString();

        virtual ~Minimizer() {}
};

#endif