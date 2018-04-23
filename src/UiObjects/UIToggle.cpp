#include "UIToggle.h"

UIToggle::UIToggle()
{
    observer.callback = [this](){
        _value = std::stoi(observer.data().getStringAt(0));
    };

    mouseDownAction.setCallback([this](){
        //printf("m\n");
        //_value = !_value;
        //if (pdObject)
        //    pdObject->sendFloat(_value);
    });
}
