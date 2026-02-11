#include <utility>

#include "../include/TextBox.h"

#include <algorithm>
#include <iostream>
#include <math.h>
#include <ostream>
#include <stdexcept>

std::vector<TextBox*> TextBox::textBoxes;

TextBox::TextBox(float width, float height, float posX, float posY, float lineThickness, Color lineColor,
                 Color backgroundColor, std::string placeholderText)
    : width(width), height(height),
      posX(posX),
      posY(posY),
      lineThickness(lineThickness),
      lineColor(lineColor),
      backgroundColor(backgroundColor),
      placeholderText(std::move(placeholderText)){
    textBoxes.push_back(this);
}


void TextBox::draw() const {
    // DrawLineEx({posX, posY}, {posX+width, posY}, lineThickness, color);
    // DrawLineEx({posX+lineThickness/2, posY}, {posX+lineThickness/2, posY+height}, lineThickness, color);
    // DrawLineEx({posX, posY+height}, {posX+width, posY+height}, lineThickness, color);
    // DrawLineEx({posX+width-lineThickness/2, posY}, {posX+width-lineThickness/2, posY+height}, lineThickness, color);

    DrawRectangleLinesEx(Rectangle(posX, posY, width, height), lineThickness, lineColor);
    DrawRectangle(posX+lineThickness, posY+lineThickness, width-lineThickness*2, height-lineThickness*2, backgroundColor);
    if (!text.empty()) {
        float textHeight = MeasureTextEx(GetFontDefault(), text.c_str(), 20, 1).y;
        DrawText(text.c_str(), posX+lineThickness*1.5, posY+(height-textHeight)/2, 20, WHITE);
    }
    else {
        float textHeight = MeasureTextEx(GetFontDefault(), placeholderText.c_str(), 20, 1).y;
        DrawText(placeholderText.c_str(), posX+lineThickness*1.5, posY+(height-textHeight)/2, 20, GRAY);
    }

}

/**
 *
 * Checks whether a coordinate is within this textBox.
 *
 * @param x The x-coordinate
 * @param y The y-coordinate
 */
bool TextBox::contains(float x, float y) const {
    return x > posX && x < posX+width && y > posY-lineThickness*2 && y < posY+height-lineThickness*2;
}

/**
 *
 * Gets this textBox's input as a double. If empty this will return -1.
 *
 * @return The input or -1.
 */
double TextBox::getNumber() const {
    std::string number = text;
    if (number.empty()) {
        return -1;
    }
    try {
        std::replace(number.begin(), number.end(), ',', '.');
        return std::stod(number);
    }
    catch (const std::invalid_argument& e) {
        return -1;
    }
}

/**
 * Gets all text input in this tick (using GetCharPressed) and adds it to the textBox
 */
bool TextBox::inputText() {
    bool success = false;
    int key = GetCharPressed();
    if (onlyNumbers) {
        while ((key != 0 && key <= 57 && key >= 48) || key == 44 || key == 46) {
            if ((key == 44 || key == 46) && (text.find('.')!=std::string::npos || text.find(',')!=std::string::npos)) {
                key = GetCharPressed();
                continue;
            }
            text += static_cast<char>(key);
            success = true;
            key = GetCharPressed();
        }
    }
    else {
        while (key != 0) {
            text += static_cast<char>(key);
            success = true;
            key = GetCharPressed();
        }
    }
    return success;
}


void TextBox::setText(std::string_view newText) {
    text = newText.data();
}

std::vector<TextBox *> TextBox::getAll() {
    return textBoxes;
}

/**
 *
 * Sets whether this textBox should only accept number inputs (including decimals with both "," and ".").
 *
 * @param on
 */
void TextBox::setOnlyNumbers(bool on) {
    onlyNumbers = on;
}
