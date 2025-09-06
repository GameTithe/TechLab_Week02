#include "InputManager.h"

int tempaa=0;
Mouse::Mouse()
{
	tempaa++;
}

bool InputManager::IsDown(MouseButton button) const
{
	switch(button)
	{
	case MouseButton::Right:
	{
		return mouse.RightDown;
	}
	break;

	case MouseButton::Left:
	{
		return mouse.LeftDown;
	}
	break;

	}
}