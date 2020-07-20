
#include "HorizontalSlider.h"
#include "../Rendering/Canvas/gl_canvas2d.h"
#include "../Utilities.h"
#include <iostream>
#include <sstream>

void HorizontalSlider::mouse(int button, int state, int wheel, int direction, int x, int y) {
    bool pointInside = pointIntersectsObject(dvec2(x,y));
    if (leftMouseDown(button, state) && pointInside) {
        mouseDragging = true;
    } else if (leftMouseUp(button, state)) {
        mouseDragging = false;
    }

    if (mouseDragging) {
        currentMousePosition = dvec2(x, y);
        if (x > transform.position.x + transform.scale.x)
            currentMousePosition.x = transform.position.x + transform.scale.x - textSpace;
        if (y > transform.position.y + transform.scale.y)
            currentMousePosition.y = transform.position.y + transform.scale.y;
        if (x < transform.position.x)
            currentMousePosition.x = transform.position.x;
        if (y < transform.position.y)
            currentMousePosition.y = transform.position.y;

        float t = getCurrentValueT(currentMousePosition);
        float value = lerp(minValue, maxValue, t);
        if (value != currentValue && t >= 0 && t <= 1) {
            currentValue = value;
            currentMousePosition = dvec2(lerp(transform.position.x, transform.position.x + transform.scale.x - textSpace, t), y);
            notifyOnValueChangedListeners();
        } else {
            currentMousePosition = lastMousePosition;
        }

        lastMousePosition = currentMousePosition;
    }

}

void HorizontalSlider::render() {
    CV::color(lineColor);
    CV::rect(transform.position.x, transform.position.y, transform.position.x + transform.scale.x - textSpace, transform.position.y + transform.scale.y);
    CV::color(backgroundColor);
    CV::rectFill(transform.position.x, transform.position.y, transform.position.x + transform.scale.x - textSpace, transform.position.y + transform.scale.y);
    CV::color(handleColor);
    CV::circleFill(currentMousePosition.x, transform.position.y + transform.scale.y / 2, transform.scale.y / 2, 30);
    std::stringstream label;
    label << std::fixed;
    label.precision(2);
    label << currentValue;
    CV::text(transform.position.x + transform.scale.x - textSpace + 1, transform.position.y + transform.scale.y / 4, label.str().c_str());
}


void HorizontalSlider::addOnValueChangedListener(std::function<void(float value)> listener) {
    this->onValueChangedListeners.push_back(listener);
}

void HorizontalSlider::notifyOnValueChangedListeners() {
    for (int i = 0; i < onValueChangedListeners.size(); i++) {
        this->onValueChangedListeners[i](currentValue);
    }
}

HorizontalSlider::HorizontalSlider(Transform2D transform,dvec4 backgroundColor, dvec4 handleColor) : ObjectUI(transform) {
    this->backgroundColor = backgroundColor;
    this->handleColor = handleColor;
    this->lineColor = backgroundColor;
    this->mouseDragging = false;
    this->currentMousePosition = {transform.position.x, transform.position.y};
}

bool HorizontalSlider::pointIntersectsObject(dvec2 point) {
    return isPointInsideBounds({point.x, point.y}, {transform.position.x, transform.position.y}, {transform.scale.x, transform.scale.y}) ||
           isPointInsideCircle(point, dvec2(currentMousePosition.x, transform.position.y + transform.scale.y / 2), transform.scale.y / 2);
}

void HorizontalSlider::setValues(float minValue, float maxValues, float steps) {
    this->minValue = minValue;
    this->maxValue = maxValues;
    this->steps = steps;
    this->currentValue = minValue;
    this->currentMousePosition = dvec2(lerp(transform.position.x, transform.position.x + transform.scale.x - textSpace, 0),
                                       this->currentMousePosition.y);
}

void HorizontalSlider::translate(dvec2 translationAmount) {
    this->transform.position += translationAmount;
    currentMousePosition = currentMousePosition + dvec2(translationAmount.x, translationAmount.y);
}

float HorizontalSlider::getCurrentValueT(dvec2 mousePosition) {
    float x = mousePosition.x - transform.position.x;
    float screenSteps = (transform.scale.x - textSpace) / steps;
    float t = x / screenSteps / steps;

    float tIncrement = 1 / steps;
    for (int i = 0; i <= steps; i++) {
        float value = i * tIncrement;
        if (value >= t) {
            t = round(value - tIncrement, value, t);
            break;
        }
    }
    return t;
}

void HorizontalSlider::setCurValue(float curValue) {

    currentValue = curValue;
    float t = (curValue - minValue) / (maxValue - minValue);
    std::cout << t << std::endl;
    currentMousePosition = dvec2(lerp(transform.position.x, transform.position.x +transform. scale.x - textSpace, t), currentMousePosition.y);
}
