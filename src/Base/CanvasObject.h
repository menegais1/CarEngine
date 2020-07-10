#ifndef CANVAS_OBJECT_H
#define CANVAS_OBJECT_H

#include "../Utilities.h"
#include "IMouse.h"
#include "ITransformable.h"
#include "IKeyboard.h"
#include "IRender.h"
#include "../Vectors/Vector3.h"

class CanvasObject : public IRender, public IKeyboard, public IMouse, public ITransformable {
public:

    bool isValid;
    void keyboard(int key) override;

    void keyboardUp(int key) override;

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void render() override;

    virtual void setObjectOrder(int zIndex);

    int getObjectOrder();

    CanvasObject();

    virtual ~CanvasObject();

    virtual void setActive(bool isActive);

    bool getActive();

    bool checkIfCanExecuteCallback();

    virtual bool pointIntersectsObject(dvec3 point) = 0;


protected:
    bool isActive;
    int objectId;

private:
    int objectOrder;
    bool lastActiveState;
};

#endif
