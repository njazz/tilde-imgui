#ifndef ARRANGEOBJECTS_H
#define ARRANGEOBJECTS_H

#include <vector>

using namespace std;

class UiObjectBase;
typedef std::vector<UiObjectBase*> objectVec;

// static class for arranging objects
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
};

#endif // ARRANGEOBJECTS_H
