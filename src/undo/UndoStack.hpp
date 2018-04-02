#ifndef UndoStack_hpp
#define UndoStack_hpp

#include "UICommand.hpp"

#include <vector>
class UndoStack {

    std::vector<UICommand*> _stack;
    int _undoListIndex;

public:
    void doAction(UICommand* c)
    {
        _stack.push_back(c);
        (*c)();
        _undoListIndex = _stack.size() - 1;
        // todo: limit undo size
    }

    void undoLastAction()
    {
        if (_undoListIndex < -1)
            return;
        if (_undoListIndex > (_stack.size() - 1))
            return;
        _stack[_undoListIndex]->undo();
        _undoListIndex--;
    }
    void redoLastAction()
    {
        if (_undoListIndex < -1)
            return;
        if (_undoListIndex > (_stack.size() - 1))
            return;
        (*_stack[_undoListIndex])();
        _undoListIndex++;
    }
};
#endif
