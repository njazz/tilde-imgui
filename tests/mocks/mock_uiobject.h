#ifndef MOCK_UIOBJECT_H
#define MOCK_UIOBJECT_H

#include "UIObject.hpp"
#include "UIObjectBase.hpp"
#include "UIPatchcord.hpp"

//UiObjectBase::UiObjectBase(){};
//void UiObjectBase::updateFromPdObject(){};
//void UiObjectBase::_drawBackground() {};
//void UiObjectBase::draw(){};

// ******* object
void UIObject::draw(){};
void UIObject::drawObjectContents(){};
void UIObject::finishedEditingText(){}
void UIObject::clearEditText(){};
void UIObject::onMouseDoubleClickEdited(ImVec2 pos){};

//void UIObject::onMouseDoubleClickEdited(ImVec2 pos){};

#endif // MOCK_UIOBJECT_H
