#include <array>
#include <cmath>
#include <cstring>
#include <list>

#include "raylib.h"
#include "../include/TextBox.h"
#include "../include/TriangleCalculator.h"
#include "../include/Triangle.h"


int main() {
    TextBox sideA(250, 50, 100, 500, 4, WHITE, {224, 224, 222, 255}, "Side a");
    sideA.setOnlyNumbers(true);
    TextBox sideB(250, 50, 100, 570, 4, WHITE, {224, 224, 222, 255}, "Side b");
    sideB.setOnlyNumbers(true);
    TextBox sideC(250, 50, 100, 640, 4, WHITE, {224, 224, 222, 255}, "Side c");
    sideC.setOnlyNumbers(true);
    TextBox angleA(250, 50, 400, 500, 4, WHITE, {224, 224, 222, 255}, "Vinkel A");
    angleA.setOnlyNumbers(true);
    TextBox angleB(250, 50, 400, 570, 4, WHITE, {224, 224, 222, 255}, "Vinkel B");
    angleB.setOnlyNumbers(true);
    TextBox angleC(250, 50, 400, 640, 4, WHITE, {224, 224, 222, 255}, "Vinkel C");
    angleC.setOnlyNumbers(true);

    Triangle triangle;
    bool drawTriangle = false;

    InitWindow(1920, 1080, "Trekantsberegner");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Check for text inputs
        bool textChanged = false;
        std::vector<TextBox*> textboxes = TextBox::getAll();
        for (auto textBox : textboxes) {
            if (textBox->contains(GetMouseX(), GetMouseY())) {
                SetMouseCursor(MOUSE_CURSOR_IBEAM);
                if (!textChanged) {
                    textChanged = textBox->inputText();
                }
                else {
                    textBox->inputText();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (!textBox->text.empty()) {
                        textBox->text.pop_back();
                        textChanged = true;
                    }
                }
            }
        }

        // Try to calculate sides if there have been any text inputs
        if (textChanged) {
            std::array<double, 6> calculated = TriangleCalculator::Calculate(std::array{
                sideA.getNumber(),
                sideB.getNumber(),
                sideC.getNumber(),
                angleA.getNumber(),
                angleB.getNumber(),
                angleC.getNumber()
            });

            triangle.sidesAndAngles = calculated;
            if (calculated[0] != -1 && calculated[0] != sideA.getNumber()) {
                sideA.placeholderText = std::to_string(calculated[0]);
            }
            if (calculated[1] != -1 && calculated[1] != sideB.getNumber()) {
                sideB.placeholderText = std::to_string(calculated[1]);
            }
            if (calculated[2] != -1 && calculated[2] != sideC.getNumber()) {
                sideC.placeholderText = std::to_string(calculated[2]);
            }
            if (calculated[3] != -1 && calculated[3] != angleA.getNumber()) {
                angleA.placeholderText = std::to_string(calculated[3]);
            }
            if (calculated[4] != -1 && calculated[4] != angleB.getNumber()) {
                angleB.placeholderText = std::to_string(calculated[4]);
            }
            if (calculated[5] != -1 && calculated[5] != angleC.getNumber()) {
                angleC.placeholderText = std::to_string(calculated[5]);
            }
            drawTriangle = true;
            for (int i = 0; i < 6; i++) {
                if (calculated[i]==-1.00) {
                    drawTriangle = false;
                }
            }
        };

        if (drawTriangle && textChanged) {
            triangle.draw(true);
        }
        else if (drawTriangle) {
            triangle.draw(false);
        }

        for (auto textBox : textboxes) {
            textBox->draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
