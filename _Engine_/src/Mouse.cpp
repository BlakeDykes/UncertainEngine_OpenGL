#include "Mouse.h"
#include "Game.h"

extern Game* pGame;

Mouse::Mouse()
{
}

bool Mouse::GetKeyState(Button button) const
{
	bool value;

	if (pGame->GetMouseButton(button) == GLFW_PRESS)
	{
		value = true;
	}
	else
	{
		value = false;
	}

	return value;
}

void Mouse::GetCursorPos()
{
	pGame->GetCursorPos(this->xPos, this->yPos);
}