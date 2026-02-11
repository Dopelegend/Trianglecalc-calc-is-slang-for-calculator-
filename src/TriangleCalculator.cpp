
#include "../include/TriangleCalculator.h"

#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>


/**
 *
 * Calculates all 3 sides and all 3 angles of a triangle using some combination of inputs. This returns -1 for any sides that couldn't be calculated.
 *
 * @param sidesAndAngles Every side and angle that's (-1 for ones that aren't). This should be formatted {a, b, c, A, B, C}.
 * @return Every calculated angle and side (-1 for ones that couldn't be calculated). This is formatted {a, b, c, A, B, C}.
 */
std::array<double, 6> TriangleCalculator::Calculate(std::array<double, 6> sidesAndAngles) {
    bool rerun = false;
    std::array<double, 6> result = sidesAndAngles;

    for (int i = 0; i < 6; i++) {
        double triangleComponent = sidesAndAngles[i];

        // Check whether we already have this component.
        if (triangleComponent != -1) {
            result[i] = triangleComponent;
            continue;
        }

        if (i <= 2) {
            // This is a side
            // Attempt to find necessary information for law of cosines
            std::array<double, 2> otherSides{};
            int idx = 0;
            for (int j = 0; j < 3; j++) {
                if (j != i) {
                    otherSides[idx] = sidesAndAngles[j];
                    idx++;

                }
            }

            if (sidesAndAngles[i+3]!=-1 && otherSides[0] != -1 && otherSides[1] != -1) {
                result[i] = std::sqrt(otherSides[0]*otherSides[0]+otherSides[1]*otherSides[1]-2*otherSides[0]*otherSides[1]*std::cos(sidesAndAngles[i+3]*M_PI/180));
                rerun = true;
            }
        }
        if (i > 2) {
            std::array<double, 4> otherComponents{};
            int idx = 0;

            for (int j = 3; j < 6; j++) {
                if (j != i) {
                    otherComponents[idx] = sidesAndAngles[j-3];
                    otherComponents[idx+2] = sidesAndAngles[j];
                    idx++;
                }
            }
            // Check if we have the other 2 angles.
            if (sidesAndAngles[i] == -1 && otherComponents[2] != -1 && otherComponents[3] != -1) {
                result[i] = 180-(otherComponents[2]+otherComponents[3]);
                rerun = true;
                continue;
            }

            // Attempt to use law of cosine
            if (otherComponents[0] != -1 && otherComponents[1] != -1 && sidesAndAngles[i-3] != -1) {
                result[i] = std::acos((otherComponents[0]*otherComponents[0]+
                    otherComponents[1]*otherComponents[1]-
                    sidesAndAngles[i-3]*sidesAndAngles[i-3])
                    /
                    (2*otherComponents[0]*otherComponents[1]))*180/M_PI;

                rerun = true;
            }

        }
    }
    bool done = true;
    for (int i = 0; i < 6; i++) {
        if (result[i] == -1) {
            done = false;
            break;
        }
    }
    if (!done && rerun) {
        return Calculate(result);
    }
    return result;
}
