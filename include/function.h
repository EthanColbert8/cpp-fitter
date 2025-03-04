#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>

class Function {
    public:
        static const int num_params;

        //virtual void fit(std::vector<float> x, std::vector<float> y) = 0;
        
        virtual float evaluate(std::vector<float> x) = 0;
        virtual std::vector<float> gradient(std::vector<float> x) = 0;
        
        virtual std::vector<float> getParams() = 0;
        virtual void setParams(std::vector<float> new_params) = 0;

        virtual std::string toString() = 0;
        
        virtual ~Function() {}
};

#endif
