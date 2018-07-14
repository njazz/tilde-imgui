#include "UndoStack.hpp"

UndoStack::UndoStack() {}

void UndoStack::doAction(UICommandPtr c)
{
    _stack.push_back(c);
    (*c)();
    _undoListIndex = _stack.size() - 1;
    // todo: limit undo size
}

void UndoStack::undoLastAction()
{
    if (canUndo()) {

        _stack[_undoListIndex]->undo();
        _undoListIndex--;
    }
}

void UndoStack::redoLastAction()
{
    if (canRedo()) {
        _undoListIndex++;
        (*_stack[_undoListIndex])();
    }
}

std::vector<std::string> UndoStack::undoActionsList()
{
    std::vector<std::string> ret;

    for (int i = 0; i < undoActionCount(); i++) {
        auto o = _stack[i];
        ret.push_back(o->actionName());
    }

    return ret;
}

int UndoStack::undoActionCount() { return _undoListIndex + 1; }

bool UndoStack::canRedo()
{
    if (_undoListIndex < -1)
        return false;
    if (_undoListIndex >= ((int)_stack.size() - 1))
        return false;
    return true;
}
bool UndoStack::canUndo()
{
    if (_undoListIndex <= -1)
        return false;
    if (_undoListIndex > (_stack.size() - 1))
        return false;

    return true;
}

// -----

std::string UndoStack::undoActionName()
{
    if (canUndo()) {

        return _stack[_undoListIndex]->actionName();
    }
    return "";
}

std::string UndoStack::redoActionName()
{
    if (canRedo()) {

        return _stack[_undoListIndex + 1]->actionName();
    }
    return "";
}
