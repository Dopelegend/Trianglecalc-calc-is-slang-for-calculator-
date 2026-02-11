//
// Created by tenna on 11/02/2026.
//

#ifndef TRIANGLECALCULATOR_TRIANGLE_H
#define TRIANGLECALCULATOR_TRIANGLE_H
#include <array>
#include <raylib.h>


class Triangle {
public:
    /**
     * The components of this triangle (sides and angles) formatted {a, b, c, A, B, C]
     */
    std::array<double, 6> sidesAndAngles = {-1, -1, -1, -1, -1, -1};
    void draw(bool update);

private:
    std::array<Vector2, 6> pxPositions = {};
};


#endif //TRIANGLECALCULATOR_TRIANGLE_H