#include "Base.h"
#include "Button.h"

namespace gameplay
{

Button::Button()
{
}

Button::~Button()
{
}

Button* Button::create(const char* id, Theme::Style* style)
{
    Button* button = new Button();

    button->_id = id;
    button->_style = style;

    return button;
}

Button* Button::create(Theme::Style* style, Properties* properties)
{
    Button* button = new Button();
    button->initialize(style, properties);

    return button;
}

bool Button::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    if (!isEnabled())
    {
        return false;
    }

    switch (evt)
    {
    case Touch::TOUCH_PRESS:
        if (x > _clipBounds.x && x <= _clipBounds.x + _clipBounds.width &&
            y > _clipBounds.y && y <= _clipBounds.y + _clipBounds.height)
        {
            setState(Control::ACTIVE);
            notifyListeners(Listener::PRESS);
            return _consumeInputEvents;
        }
        else
        {
            setState(Control::NORMAL);
        }
        break;

    case Touch::TOUCH_RELEASE:
        notifyListeners(Listener::RELEASE);
        if (x > _clipBounds.x && x <= _clipBounds.x + _clipBounds.width &&
            y > _clipBounds.y && y <= _clipBounds.y + _clipBounds.height)
        {
            setState(Control::FOCUS);
            notifyListeners(Listener::CLICK);
            return _consumeInputEvents;
        }
        else
        {
            setState(Control::NORMAL);
        }
        break;

    case Touch::TOUCH_MOVE:
        return _consumeInputEvents;
    }

    return false;
}

}