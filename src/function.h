#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>

class Function {
    public:
        virtual void fit(std::vector<float> x, std::vector<float> y) = 0;
        virtual std::string print_params() = 0;
        virtual float evaluate(float x) = 0;
        
        virtual ~Function() {}
};

#endif