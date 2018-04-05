#include "UIToggle.h"

UIToggle::UIToggle()
{
    observer.callback = [this](){
        _value = std::stoi(observer.data().getStringAt(0));
    };
}
