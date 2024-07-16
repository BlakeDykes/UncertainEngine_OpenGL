#ifndef MOUSE_H
#define MOUSE_H

class Mouse
{
public:
	enum Button
	{
		BUTTON_1 = 0,
		BUTTON_2 = 1,
		BUTTON_3 = 2,
		BUTTON_4 = 3,
		BUTTON_5 = 4,
		BUTTON_6 = 5,
		BUTTON_7 = 6,
		BUTTON_8 = 7,
		BUTTON_LEFT = BUTTON_1,
		BUTTON_RIGHT = BUTTON_2,
		BUTTON_MIDDLE = BUTTON_3,


		SIZE = BUTTON_8 + 1,
		UNINITIALIZED = 999
	};

	float xPos;
	float yPos;

	Mouse();
	bool GetKeyState(Button button) const;
	void GetCursorPos();
};

#endif // !MOUSE_H
