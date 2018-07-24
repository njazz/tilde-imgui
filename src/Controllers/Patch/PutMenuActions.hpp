#ifndef CREATEOBJECTS_H
#define CREATEOBJECTS_H

#include "IUAction.hpp"

class PdPatchViewController;

class PutMenuActions{
  PdPatchViewController* _controller = 0;

  void _createObject(std::string s);

public:
  PutMenuActions(PdPatchViewController* vc):_controller(vc){};

  IU_ACTION(putObject);
  IU_ACTION(putMessage);
  IU_ACTION(putComment);

  IU_ACTION(putBang);
  IU_ACTION(putToggle);
  IU_ACTION(putNumber);
};

#endif
