//Color picker secondary window, used to select colors variance between black and the color selected at
//the color picker main window

#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include "../Vectors/Vector3.h"
#include "../Base/UI/ObjectUI.h"
#include <vector>
#include <functional>

class HorizontalSlider : public ObjectUI {
public:

    float currentValue;

    float textSpace = 15;
    dvec4 backgroundColor;
    dvec4 handleColor;
    dvec4 lineColor;

    HorizontalSlider(Transform2D transform, dvec4 backgroundColor, dvec4 handleColor);

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void render() override;

    void translate(dvec2 translationAmount);

    void addOnValueChangedListener(std::function<void(float value)> listener);

    void notifyOnValueChangedListeners();

    void setValues(float minValue, float maxValues, float steps);

    void setCurValue(float curValue);

private:
    float maxValue;
    float minValue;
    float steps;

    bool mouseDragging;
    bool mouseInside;
    dvec2 currentMousePosition;
    dvec2 lastMousePosition;

    float getCurrentValueT(dvec2 mousePosition);

    std::vector<std::function<void(float value)>> onValueChangedListeners;

    bool pointIntersectsObject(dvec2 point);
};

#endif