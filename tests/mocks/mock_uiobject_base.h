#ifndef MOCK_UIOBJECT_BASE_H
#define MOCK_UIOBJECT_BASE_H

#include "UIObject.hpp"
#include "UIObjectBase.hpp"
#include "UIPatchcord.hpp"

UiObjectBase::UiObjectBase(){};
void UiObjectBase::updateFromPdObject(){};
void UiObjectBase::_drawBackground() {};
void UiObjectBase::draw(){};


// todo: move
// ******* patchcord

void UIPatchcord::_drawContents(){}


#endif // MOCK_UIOBJECT_BASE_H
