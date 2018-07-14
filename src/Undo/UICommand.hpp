#ifndef UICommand_hpp
#define UICommand_hpp

#include <functional>
#include <string>

#include <vector>

#include <memory>

class UICommand;

typedef std::shared_ptr<UICommand> UICommandPtr;

class UICommand {
    std::function<void(void)> _do;
    std::function<void(void)> _undo;
    std::string _actionName;

public:
    UICommand(std::string name, std::function<void(void)> doAction, std::function<void(void)> undoAction);

    void operator()();
    void undo();

    std::string& actionName();
    static UICommandPtr makePtr(std::string name, std::function<void(void)> doAction, std::function<void(void)> undoAction);
};

#endif
