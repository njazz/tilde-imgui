#include "UICommand.hpp"

UICommand::UICommand(std::string name, std::function<void(void)> doAction, std::function<void(void)> undoAction)
{
    _do = doAction;
    _undo = undoAction;
    _actionName = name;
}

void UICommand::operator()()
{
    _do();
}

void UICommand::undo()
{
    _undo();
}

std::string& UICommand::actionName() { return _actionName; };

 UICommandPtr UICommand::makePtr(std::string name, std::function<void(void)> doAction, std::function<void(void)> undoAction)
{
    return std::make_shared<UICommand>(name, doAction, undoAction);
}
