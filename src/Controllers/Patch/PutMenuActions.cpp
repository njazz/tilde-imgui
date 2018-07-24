#include "PutMenuActions.hpp"
#include "PdPatchViewController.hpp"

void PutMenuActions::_createObject(std::string s)
{
    if (!_controller) return;
    auto obj = _controller->createObject(s, 150, 150);
    _controller->setMovingObject(obj);
}

void PutMenuActions::_putObject()
{
    _createObject("");
}

void PutMenuActions::_putMessage()
{
    _createObject("ui.msg");
}

void PutMenuActions::_putComment()
{
    // todo
}

void PutMenuActions::_putBang()
{
    _createObject("ui.bang");
}

void PutMenuActions::_putToggle()
{
    _createObject("ui.toggle");
}

void PutMenuActions::_putNumber()
{
    _createObject("ui.float");
}
