#ifndef CANVAS_OBJECT_H
#define CANVAS_OBJECT_H

#include "../Utilities.h"
#include "Interfaces/IMouse.h"
#include "Interfaces/ITransformable.h"
#include "Interfaces/IKeyboard.h"
#include "Interfaces/IRender.h"
#include "../Vectors/Vector3.h"

class CanvasObject : public IRender, public IKeyboard, public IMouse {
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

protected:
    bool isActive;
    int objectId;

private:
    int objectOrder;
    bool lastActiveState;
};

#endif
