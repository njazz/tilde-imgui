#ifndef ARRANGEOBJECTS_H
#define ARRANGEOBJECTS_H

#include <vector>

#include "IUAction.hpp"

using namespace std;

class UiObjectBase;
typedef std::vector<UiObjectBase*> objectVec;

///> static class for arranging objects
class ArrangeObjects {
private:
    ArrangeObjects();

public:
    static void alignLeft(objectVec* v);
    static void alignRight(objectVec* v);

    static void alignTop(objectVec* v);
    static void alignBottom(objectVec* v);

    static void alignCenter(objectVec* v);

    static void distributeHorizontal(objectVec* v);
    static void distributeVertical(objectVec* v);

    // new
    static void alignToGrid(objectVec* v, int gridSize);
    static void tidyUp(objectVec* v);

};

class PdPatchViewController;

class ArrangeMenuActions{
    PdPatchViewController* _controller = 0;
public:
    ArrangeMenuActions(PdPatchViewController* vc):_controller(vc){};

    IU_ACTION(arrangeDHAction);
    IU_ACTION(arrangeDVAction);

    IU_ACTION(arrangeLeftAction);
    IU_ACTION(arrangeCenterAction);
    IU_ACTION(arrangeRightAction);
    IU_ACTION(arrangeTopAction);
    IU_ACTION(arrangeBottomAction);
};

#endif // ARRANGEOBJECTS_H
