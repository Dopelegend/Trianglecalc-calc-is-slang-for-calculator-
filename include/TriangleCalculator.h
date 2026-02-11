
#ifndef TRIANGLECALCULATOR_TRIANGLECALCULATOR_H
#define TRIANGLECALCULATOR_TRIANGLECALCULATOR_H
#include <vector>


class TriangleCalculator {
public:
    static std::array<double, 6> Calculate(std::array<double, 6> sidesAndAngles);
};


#endif //TRIANGLECALCULATOR_TRIANGLECALCULATOR_H