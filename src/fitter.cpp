#include <vector>
#include <iostream>
#include <string>

#include "polynomials.h"

int main() {
    int nums[4] = {0, 10, 20, 30};

    for (int i = 0; i < 4; i++) {
        std::cout << "Next num: " << nums[i] << "\n";
    }

    return 0;
}