//
// Created by tenna on 11/02/2026.
//

#include "../include/Triangle.h"

#include <cmath>
#include <raylib.h>
#include <string>


void Triangle::draw(const bool update) {

    // Check if no new calculation are necessary
    if (!update) {
        std::string texts[6] = {
            "a = "+std::to_string(sidesAndAngles[0]),
            "b = "+std::to_string(sidesAndAngles[1]),
            "c = "+std::to_string(sidesAndAngles[2]),
            "A = "+std::to_string(sidesAndAngles[3]),
            "B = "+std::to_string(sidesAndAngles[4]),
            "C = "+std::to_string(sidesAndAngles[5])
        };
        // Side a
        DrawText(texts[0].c_str(),
            pxPositions[0].x+20,
            pxPositions[0].y,
            20, BLACK);
        // Side b
        DrawText(texts[1].c_str(),
            pxPositions[1].x,
            pxPositions[1].y+20,
            20, BLACK);
        // Side c
        DrawText(texts[2].c_str(),
            pxPositions[2].x-MeasureText(texts[2].c_str(), 20)-20,
            pxPositions[2].y-20,
            20, BLACK);
        // Angle A
        DrawText(texts[3].c_str(),
                 pxPositions[3].x - MeasureText(texts[3].c_str(), 20) - 20,
                 pxPositions[3].y + 20,
                 20, BLACK);
        // Angle B
        DrawText(texts[4].c_str(),
                 pxPositions[4].x,
                 pxPositions[4].y - 20,
                 20, BLACK);
        // Angle C
        DrawText(texts[5].c_str(),
                 pxPositions[5].x + 20,
                 pxPositions[5].y + 20,
                 20, BLACK);

        DrawTriangleLines(pxPositions[3], pxPositions[4], pxPositions[5], BLACK);
        return;
    }

    // Get the biggest side for scaling
    double biggestSide = -1;
    for (int i = 0; i < 3; i++) {
        if (sidesAndAngles[i] > biggestSide) {
            biggestSide = sidesAndAngles[i];
        }
    }


    // Get scaling and draw triangle if possible.

    if (biggestSide != -1 && sidesAndAngles[0] != -1 && sidesAndAngles[1] != -1 && sidesAndAngles[2] != -1) {
        std::string texts[6] = {std::to_string(sidesAndAngles[0]),
            std::to_string(sidesAndAngles[1]),
            std::to_string(sidesAndAngles[2]),
            std::to_string(sidesAndAngles[3]),
            std::to_string(sidesAndAngles[4]),
            std::to_string(sidesAndAngles[5])};

        double scaling = 600 / biggestSide;

        // Angle A
        pxPositions[3] = {700, 800};
        DrawText(texts[3].c_str(),
            pxPositions[3].x-MeasureText(texts[3].c_str(), 20)-20,
            pxPositions[3].y+20,
            20, BLACK);

        // Angle B
        pxPositions[4] = {static_cast<float>(700.0 + sidesAndAngles[2]*std::cos(sidesAndAngles[3]*M_PI/180)*scaling),
            static_cast<float>(700.0 - sidesAndAngles[2]*std::sin(sidesAndAngles[3]*M_PI/180)*scaling)};
        DrawText(texts[4].c_str(),
            pxPositions[4].x,
            pxPositions[4].y - 20,
            20, BLACK);

        // Angle C
        pxPositions[5] = {static_cast<float>(700.0 + sidesAndAngles[1]*scaling), 800};
        DrawText(
            texts[5].c_str(),
            pxPositions[5].x + 20,
            pxPositions[5].y + 20,
            20, BLACK);

        // Get midpoints and draw side values
        // Side a
        pxPositions[0] = {(pxPositions[4].x + pxPositions[5].x)/2, (pxPositions[4].y + pxPositions[5].y)/2};
        DrawText(texts[0].c_str(),
            pxPositions[0].x+20,
            pxPositions[0].y,
            20, BLACK);
        // Side b
        pxPositions[1] = {(pxPositions[3].x + pxPositions[5].x)/2, (pxPositions[3].y + pxPositions[5].y)/2};
        DrawText(texts[1].c_str(),
            pxPositions[1].x,
            pxPositions[1].y+20,
            20, BLACK);
        // Side c
        pxPositions[2] = {(pxPositions[3].x + pxPositions[4].x)/2, (pxPositions[3].y + pxPositions[4].y)/2};
        DrawText(texts[2].c_str(),
            pxPositions[2].x-MeasureText(texts[2].c_str(), 20)-20,
            pxPositions[2].y-20,
            20, BLACK);

        // Triangle
        DrawTriangleLines(pxPositions[3], pxPositions[4], pxPositions[5], BLACK);

    }
};

