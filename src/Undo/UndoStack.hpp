#ifndef UndoStack_hpp
#define UndoStack_hpp

#include "UICommand.hpp"

#include <vector>
class UndoStack {

    std::vector<UICommandPtr> _stack;
    int _undoListIndex =-1;

public:
    UndoStack();

    void doAction(UICommandPtr c);

    void undoLastAction();
    void redoLastAction();

    std::vector<std::string> undoActionsList();

    int undoActionCount();

    bool canRedo();
    bool canUndo();

    std::string undoActionName();
    std::string redoActionName();

};
#endif
