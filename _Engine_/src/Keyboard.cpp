#include "Game.h"
#include "Keyboard.h"

extern Game* pGame;

bool Keyboard::GetKeyState(Keyboard::Key key) const
{
	bool value;

	if (pGame->GetKey(key) == GLFW_PRESS)
	{
		value = true;
	}
	else
	{
		value = false;
	}

	return value;
}
