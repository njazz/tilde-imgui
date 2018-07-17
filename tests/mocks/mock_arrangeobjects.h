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

#endif // MOCK_ARRANGE_H
