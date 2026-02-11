#ifndef TRIANGLECALCULATOR_TEXTBOX_H
#define TRIANGLECALCULATOR_TEXTBOX_H
#include <raylib.h>
#include <string>
#include <vector>


class TextBox {
    public:
    float width, height, posX, posY, lineThickness;
    Color lineColor, backgroundColor;
    std::string text, placeholderText;

    TextBox(float width, float height, float posX, float posY, float lineThickness, Color lineColor, Color backgroundColor, std::string placeholderText);
    void draw() const;
    bool contains(float x, float y) const;
    bool inputText();
    void setOnlyNumbers(bool onlyNumbers);
    double getNumber() const;
    static std::vector<TextBox*> getAll();
    void setText(std::string_view text);
    private:
        bool onlyNumbers = false;
        static std::vector<TextBox*> textBoxes;
};


#endif //TRIANGLECALCULATOR_TEXTBOX_H