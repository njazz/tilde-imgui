#ifndef UICommand_hpp
#define UICommand_hpp

#include <functional>
#include <string>

#include <vector>
class UICommand{
    std::function<void(void)> _do;
    std::function<void(void)> _undo;
    std::string _actionName;
public:
  UICommand(std::string name , std::function<void(void)> doAction, std::function<void(void)> undoAction)
  {
        _do = doAction;
        _undo = undoAction;
        _actionName = name;
  }

  void operator()(){
      _do();
  }

  void undo(){
      _undo();
  }
};

#endif
