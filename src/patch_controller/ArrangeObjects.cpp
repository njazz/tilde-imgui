// (c) 2017 Alex Nadzharov
// License: GPL3

#include "ArrangeObjects.h"
#include "UiObjects/UIObject.hpp"

#include "math.h"

ArrangeObjects::ArrangeObjects()
{
}

void ArrangeObjects::alignLeft(objectVec* v)
{
    int x = 32768; //big enough lol

    for (auto obj : *v) {
        if (x > obj->getX())
            x = obj->getX();
    }
    for (auto obj : *v) {
        obj->getX() = x;
    }
}

void ArrangeObjects::alignRight(objectVec* v)
{
    int x = 0;

    for (auto obj : *v) {
        if (x < obj->getX())
            x = obj->getX();
    }
    for (auto obj : *v) {
        obj->getX() = x;
    }
}

void ArrangeObjects::alignBottom(objectVec* v)

{
    int y = 0;

    for (auto obj : *v) {
        if (y < obj->getY())
            y = obj->getY();
    }
    for (auto obj : *v) {
        obj->getY() = y;
    }
}

void ArrangeObjects::alignTop(objectVec* v)
{
    int y = 32768; //big enough lol

    for (auto obj : *v) {
        if (y > obj->getY())
            y = obj->getY();
    }
    for (auto obj : *v) {
        obj->getY() = y;
    }
}

void ArrangeObjects::alignCenter(objectVec* v)
{
    int x = 0; //big enough lol
    int c = 0;

    for (auto obj : *v) {
        //if (x > obj->getX())
        x += obj->getX();
        c++;
    }

    if (c == 0)
        return;

    x = x / c;

    for (auto obj : *v) {
        obj->getX() = x;
    }
}

void ArrangeObjects::distributeHorizontal(objectVec* v)
{

    int min_x = 32768; //big enough lol

    for (auto obj : *v) {
        if (min_x > obj->getY())
            min_x = obj->getY();
    }

    int max_x = 0;

    for (auto obj : *v) {
        if (max_x < obj->getY())
            max_x = obj->getY();
    }

    int i = 0;

    for (auto obj : *v) {

        int nx = floor(float(i) / float(v->size()) * float(max_x - min_x) + min_x);

        obj->getX() = nx;
        i++;
    }
}

void ArrangeObjects::distributeVertical(objectVec* v)
{

    int min_y = 32768; //big enough lol

    for (auto obj : *v) {
        if (min_y > obj->getY())
            min_y = obj->getY();
    }

    int max_y = 0;

    for (auto obj : *v) {
        if (max_y < obj->getY())
            max_y = obj->getY();
    }

    int i = 0;

    for (auto obj : *v) {

        int ny = floor(float(i) / float(v->size()) * float(max_y - min_y) + min_y);

        obj->getY() = ny;
        i++;
    }
}
