#ifndef MOCK_CREATE_OBJECTS_H
#define MOCK_CREATE_OBJECTS_H

#include "CreateObjects.hpp"

#define MOCK_ACTION(x) void CreateObjects::_##x(){}

MOCK_ACTION(putObject);
MOCK_ACTION(putMessage);
MOCK_ACTION(putComment);

MOCK_ACTION(putBang);
MOCK_ACTION(putToggle);
MOCK_ACTION(putNumber);

#endif // MOCK_PATCH_CONTROLLER_H
