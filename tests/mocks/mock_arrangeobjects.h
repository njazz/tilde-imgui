#ifndef MOCK_ARRANGE_H
#define MOCK_ARRANGE_H

#include "ArrangeObjects.h"

void ArrangeObjects::alignLeft(objectVec* v) {}
void ArrangeObjects::alignRight(objectVec* v) {}

void ArrangeObjects::alignTop(objectVec* v) {}
void ArrangeObjects::alignBottom(objectVec* v) {}

void ArrangeObjects::alignCenter(objectVec* v) {}

void ArrangeObjects::distributeHorizontal(objectVec* v) {}
void ArrangeObjects::distributeVertical(objectVec* v) {}

// new
void ArrangeObjects::alignToGrid(objectVec* v, int gridSize) {}
void ArrangeObjects::tidyUp(objectVec* v) {}


//

#undef MOCK_ACTION
#define MOCK_ACTION(x) void ArrangeMenuActions::_##x(){}

MOCK_ACTION(arrangeDHAction);
MOCK_ACTION(arrangeDVAction);

MOCK_ACTION(arrangeLeftAction);
MOCK_ACTION(arrangeCenterAction);
MOCK_ACTION(arrangeRightAction);
MOCK_ACTION(arrangeTopAction);
MOCK_ACTION(arrangeBottomAction);

#endif // MOCK_ARRANGE_H
