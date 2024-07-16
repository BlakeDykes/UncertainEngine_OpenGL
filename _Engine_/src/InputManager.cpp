#include "InputManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include <stdlib.h>
#include <time.h>
#include "AnimManager.h"
#include "PlayerManager.h"

using namespace Uncertain;

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
	: poKeyboard(new Keyboard()), poMouse(new Mouse()), bIsEditing(false)
{
	srand(1);

		// Key press checkers
		this->LastKeyPress[Keyboard::Key::KEY_SPACE]			= KeyPress(Keyboard::Key::KEY_SPACE);
		this->LastKeyPress[Keyboard::Key::KEY_APOSTROPHE]		= KeyPress(Keyboard::Key::KEY_APOSTROPHE);
		this->LastKeyPress[Keyboard::Key::KEY_COMMA]			= KeyPress(Keyboard::Key::KEY_COMMA);
		this->LastKeyPress[Keyboard::Key::KEY_MINUS]			= KeyPress(Keyboard::Key::KEY_MINUS);
		this->LastKeyPress[Keyboard::Key::KEY_PERIOD]			= KeyPress(Keyboard::Key::KEY_PERIOD);
		this->LastKeyPress[Keyboard::Key::KEY_SLASH]			= KeyPress(Keyboard::Key::KEY_SLASH);
		this->LastKeyPress[Keyboard::Key::KEY_0]				= KeyPress(Keyboard::Key::KEY_0);
		this->LastKeyPress[Keyboard::Key::KEY_1]				= KeyPress(Keyboard::Key::KEY_1);
		this->LastKeyPress[Keyboard::Key::KEY_2]				= KeyPress(Keyboard::Key::KEY_2);
		this->LastKeyPress[Keyboard::Key::KEY_3]				= KeyPress(Keyboard::Key::KEY_3);
		this->LastKeyPress[Keyboard::Key::KEY_4]				= KeyPress(Keyboard::Key::KEY_4);
		this->LastKeyPress[Keyboard::Key::KEY_5]				= KeyPress(Keyboard::Key::KEY_5);
		this->LastKeyPress[Keyboard::Key::KEY_6]				= KeyPress(Keyboard::Key::KEY_6);
		this->LastKeyPress[Keyboard::Key::KEY_7]				= KeyPress(Keyboard::Key::KEY_7);
		this->LastKeyPress[Keyboard::Key::KEY_8]				= KeyPress(Keyboard::Key::KEY_8);
		this->LastKeyPress[Keyboard::Key::KEY_9]				= KeyPress(Keyboard::Key::KEY_9);
		this->LastKeyPress[Keyboard::Key::KEY_SEMICOLON]		= KeyPress(Keyboard::Key::KEY_SEMICOLON);
		this->LastKeyPress[Keyboard::Key::KEY_EQUAL]			= KeyPress(Keyboard::Key::KEY_EQUAL);
		this->LastKeyPress[Keyboard::Key::KEY_A]				= KeyPress(Keyboard::Key::KEY_A);
		this->LastKeyPress[Keyboard::Key::KEY_B]				= KeyPress(Keyboard::Key::KEY_B);
		this->LastKeyPress[Keyboard::Key::KEY_C]				= KeyPress(Keyboard::Key::KEY_C);
		this->LastKeyPress[Keyboard::Key::KEY_D]				= KeyPress(Keyboard::Key::KEY_D);
		this->LastKeyPress[Keyboard::Key::KEY_E]				= KeyPress(Keyboard::Key::KEY_E);
		this->LastKeyPress[Keyboard::Key::KEY_F]				= KeyPress(Keyboard::Key::KEY_F);
		this->LastKeyPress[Keyboard::Key::KEY_G]				= KeyPress(Keyboard::Key::KEY_G);
		this->LastKeyPress[Keyboard::Key::KEY_H]				= KeyPress(Keyboard::Key::KEY_H);
		this->LastKeyPress[Keyboard::Key::KEY_I]				= KeyPress(Keyboard::Key::KEY_I);
		this->LastKeyPress[Keyboard::Key::KEY_J]				= KeyPress(Keyboard::Key::KEY_J);
		this->LastKeyPress[Keyboard::Key::KEY_K]				= KeyPress(Keyboard::Key::KEY_K);
		this->LastKeyPress[Keyboard::Key::KEY_L]				= KeyPress(Keyboard::Key::KEY_L);
		this->LastKeyPress[Keyboard::Key::KEY_M]				= KeyPress(Keyboard::Key::KEY_M);
		this->LastKeyPress[Keyboard::Key::KEY_N]				= KeyPress(Keyboard::Key::KEY_N);
		this->LastKeyPress[Keyboard::Key::KEY_O]				= KeyPress(Keyboard::Key::KEY_O);
		this->LastKeyPress[Keyboard::Key::KEY_P]				= KeyPress(Keyboard::Key::KEY_P);
		this->LastKeyPress[Keyboard::Key::KEY_Q]				= KeyPress(Keyboard::Key::KEY_Q);
		this->LastKeyPress[Keyboard::Key::KEY_R]				= KeyPress(Keyboard::Key::KEY_R);
		this->LastKeyPress[Keyboard::Key::KEY_S]				= KeyPress(Keyboard::Key::KEY_S);
		this->LastKeyPress[Keyboard::Key::KEY_T]				= KeyPress(Keyboard::Key::KEY_T);
		this->LastKeyPress[Keyboard::Key::KEY_U]				= KeyPress(Keyboard::Key::KEY_U);
		this->LastKeyPress[Keyboard::Key::KEY_V]				= KeyPress(Keyboard::Key::KEY_V);
		this->LastKeyPress[Keyboard::Key::KEY_W]				= KeyPress(Keyboard::Key::KEY_W);
		this->LastKeyPress[Keyboard::Key::KEY_X]				= KeyPress(Keyboard::Key::KEY_X);
		this->LastKeyPress[Keyboard::Key::KEY_Y]				= KeyPress(Keyboard::Key::KEY_Y);
		this->LastKeyPress[Keyboard::Key::KEY_Z]				= KeyPress(Keyboard::Key::KEY_Z);
		this->LastKeyPress[Keyboard::Key::KEY_LEFT_BRACKET]		= KeyPress(Keyboard::Key::KEY_LEFT_BRACKET);
		this->LastKeyPress[Keyboard::Key::KEY_BACKSLASH]		= KeyPress(Keyboard::Key::KEY_BACKSLASH);
		this->LastKeyPress[Keyboard::Key::KEY_RIGHT_BRACKET]	= KeyPress(Keyboard::Key::KEY_RIGHT_BRACKET);
		this->LastKeyPress[Keyboard::Key::KEY_GRAVE_ACCENT]		= KeyPress(Keyboard::Key::KEY_GRAVE_ACCENT);
		this->LastKeyPress[Keyboard::Key::KEY_ARROW_UP]			= KeyPress(Keyboard::Key::KEY_ARROW_UP);
		this->LastKeyPress[Keyboard::Key::KEY_ARROW_DOWN]		= KeyPress(Keyboard::Key::KEY_ARROW_DOWN);
		this->LastKeyPress[Keyboard::Key::KEY_ARROW_LEFT]		= KeyPress(Keyboard::Key::KEY_ARROW_LEFT);
		this->LastKeyPress[Keyboard::Key::KEY_ARROW_RIGHT]		= KeyPress(Keyboard::Key::KEY_ARROW_RIGHT);
		this->LastKeyPress[Keyboard::Key::KEY_ESCAPE]			= KeyPress(Keyboard::Key::KEY_ESCAPE);
		this->LastKeyPress[Keyboard::Key::KEY_ENTER]			= KeyPress(Keyboard::Key::KEY_ENTER);
		this->LastKeyPress[Keyboard::Key::KEY_TAB]				= KeyPress(Keyboard::Key::KEY_TAB);
		this->LastKeyPress[Keyboard::Key::KEY_BACKSPACE]		= KeyPress(Keyboard::Key::KEY_BACKSPACE);
		this->LastKeyPress[Keyboard::Key::KEY_INSERT]			= KeyPress(Keyboard::Key::KEY_INSERT);
		this->LastKeyPress[Keyboard::Key::KEY_DELETE]			= KeyPress(Keyboard::Key::KEY_DELETE);
		this->LastKeyPress[Keyboard::Key::KEY_LEFT_SHIFT]		= KeyPress(Keyboard::Key::KEY_LEFT_SHIFT);
		this->LastKeyPress[Keyboard::Key::KEY_LEFT_CONTROL]		= KeyPress(Keyboard::Key::KEY_LEFT_CONTROL);
		this->LastKeyPress[Keyboard::Key::KEY_LEFT_ALT]			= KeyPress(Keyboard::Key::KEY_LEFT_ALT);
		this->LastKeyPress[Keyboard::Key::KEY_RIGHT_SHIFT]		= KeyPress(Keyboard::Key::KEY_RIGHT_SHIFT);
		this->LastKeyPress[Keyboard::Key::KEY_RIGHT_CONTROL]	= KeyPress(Keyboard::Key::KEY_RIGHT_CONTROL);
		this->LastKeyPress[Keyboard::Key::KEY_RIGHT_ALT]		= KeyPress(Keyboard::Key::KEY_RIGHT_ALT);

		// Mouse button press checkers
		this->LastMousePress[Mouse::Button::BUTTON_1]			= MousePress(Mouse::Button::BUTTON_1);
		this->LastMousePress[Mouse::Button::BUTTON_2]			= MousePress(Mouse::Button::BUTTON_2);
		this->LastMousePress[Mouse::Button::BUTTON_3]			= MousePress(Mouse::Button::BUTTON_3);
		this->LastMousePress[Mouse::Button::BUTTON_4]			= MousePress(Mouse::Button::BUTTON_4);
		this->LastMousePress[Mouse::Button::BUTTON_5]			= MousePress(Mouse::Button::BUTTON_5);
		this->LastMousePress[Mouse::Button::BUTTON_6]			= MousePress(Mouse::Button::BUTTON_6);
		this->LastMousePress[Mouse::Button::BUTTON_7]			= MousePress(Mouse::Button::BUTTON_7);
		this->LastMousePress[Mouse::Button::BUTTON_8]			= MousePress(Mouse::Button::BUTTON_8);

		// Edit enable button press checkers
		this->CurrentEditModifiers[0]							= EditModifiers(LastKeyPress[Keyboard::KEY_LEFT_SHIFT]);
		this->CurrentEditModifiers[1]							= EditModifiers(LastKeyPress[Keyboard::KEY_LEFT_CONTROL]);
		this->CurrentEditModifiers[2]							= EditModifiers(LastKeyPress[Keyboard::KEY_LEFT_ALT]);
		this->CurrentEditModifiers[3]							= EditModifiers(LastKeyPress[Keyboard::KEY_RIGHT_SHIFT]);
		this->CurrentEditModifiers[4]							= EditModifiers(LastKeyPress[Keyboard::KEY_RIGHT_CONTROL]);
		this->CurrentEditModifiers[5]							= EditModifiers(LastKeyPress[Keyboard::KEY_RIGHT_ALT]);

}

InputManager::~InputManager()
{
	delete this->poKeyboard;
	delete this->poMouse;
}

void InputManager::Create()
{
	assert(!instance);

	if (!instance)
	{
		instance = new InputManager();
	}
}

void InputManager::Destroy()
{
	InputManager* inst = InputManager::GetInstance();

	delete inst;

	InputManager::instance = nullptr;
}

void InputManager::PrintControls()
{
}

void InputManager::Update()
{

	InputManager* inst = InputManager::GetInstance();

	inst->UpdateMouse();
	inst->UpdateKey();

}

void InputManager::UpdateMouse()
{
	Mouse* mouse = GetMouse();

	for (unsigned int i = 0; i < MOUSE_BUTTONS_TO_CHECK; i++)
	{
		CheckMouseButtonPress(mouse, LastMousePress[i]);
	}

	if (LastMousePress[Mouse::BUTTON_LEFT].IsNewPress())
	{
		CameraManager::CycleActive3D();
	}

	if (LastMousePress[Mouse::BUTTON_RIGHT].IsNewPress())
	{
		GameObjectManager::ToggleBoundingObjects();
	}
}

void InputManager::UpdateKey()
{

	Keyboard* key = GetKeyboard();
	assert(key);

	for (unsigned int i = 0; i < KEYBOARD_KEYS_TO_CHECK; i++)
	{
		if (CheckKeyPress(key, LastKeyPress[i]))
		{
			PlayerManager::ExecuteAction(LastKeyPress[i].K);
		}
	}

	CheckAndApplyEdits();
	// Disable camera movements while editing
	if (!isEditing())
	{

		////// -------------------------------------------------------
		////// Camera ------------------------------------------------
		////// -------------------------------------------------------
		if (LastKeyPress[Keyboard::KEY_Z].IsNewPress())
		{
			CameraManager::ResetDefault();
		}

		if (LastKeyPress[Keyboard::KEY_P].IsNewPress())
		{
			CameraManager::PrintActive3DCam();
		}
	
	if (LastKeyPress[Keyboard::KEY_ARROW_RIGHT].Pressed())
		{
			CameraManager::Rotate(Axis::NEG_Y, Camera::TYPE::PERSPECTIVE_3D);
		}

		if (LastKeyPress[Keyboard::KEY_ARROW_LEFT].Pressed())
		{
			CameraManager::Rotate(Axis::Y, Camera::TYPE::PERSPECTIVE_3D);
		}

		if (LastKeyPress[Keyboard::KEY_ARROW_DOWN].Pressed())
		{
			CameraManager::Rotate(Axis::X, Camera::TYPE::PERSPECTIVE_3D);
		}

		if (LastKeyPress[Keyboard::KEY_ARROW_UP].Pressed())
		{
			CameraManager::Rotate(Axis::NEG_X, Camera::TYPE::PERSPECTIVE_3D);

		}

		if (LastKeyPress[Keyboard::KEY_W].Pressed())
		{
			CameraManager::Translate(Axis::Z, Camera::TYPE::PERSPECTIVE_3D);
		}

		if (LastKeyPress[Keyboard::KEY_S].Pressed())
		{
			CameraManager::Translate(Axis::NEG_Z, Camera::TYPE::PERSPECTIVE_3D);
		}

		if (LastKeyPress[Keyboard::KEY_Q].Pressed())
		{
			CameraManager::Translate(Axis::Y, Camera::TYPE::PERSPECTIVE_3D);
		}

		if (LastKeyPress[Keyboard::KEY_E].Pressed())
		{
			CameraManager::Translate(Axis::NEG_Y, Camera::TYPE::PERSPECTIVE_3D);
		}

		if (LastKeyPress[Keyboard::KEY_A].Pressed())
		{
			CameraManager::Translate(Axis::NEG_X, Camera::TYPE::PERSPECTIVE_3D);
		}

		if (LastKeyPress[Keyboard::KEY_D].Pressed())
		{
			CameraManager::Translate(Axis::X, Camera::TYPE::PERSPECTIVE_3D);
		}

		if (LastKeyPress[Keyboard::KEY_I].Pressed())
		{
			Camera3D* pActive = CameraManager::GetActive3D();
			pActive->adjustFieldOfView(true);
		}

		if (LastKeyPress[Keyboard::KEY_O].Pressed())
		{
			Camera3D* pActive = CameraManager::GetActive3D();
			pActive->adjustFieldOfView(false);
		}
	}

	



	////// -------------------------------------------------------
	////// Animation ---------------------------------------------
	////// -------------------------------------------------------
	if (LastKeyPress[Keyboard::KEY_EQUAL].Pressed())
	{
		AnimManager::AdjustAll(DIRECTION::UP);
	}
	if (LastKeyPress[Keyboard::KEY_MINUS].Pressed())
	{
		AnimManager::AdjustAll(DIRECTION::DOWN);
	}
	if (LastKeyPress[Keyboard::KEY_BACKSPACE].IsNewPress())
	{
		AnimManager::ReverseAll();
	}
	if (LastKeyPress[Keyboard::KEY_BACKSLASH].IsNewPress())
	{
		AnimManager::TogglePlayAll();
	}
}

bool InputManager::CheckKeyPress(const Keyboard* state, KeyPress& keyPress)
{
	if (keyPress.K == Keyboard::UNINITIALIZED)
	{
		return false;
	}

	keyPress.SetPressed(state->GetKeyState(keyPress.K));

	return keyPress.Pressed();
}

bool InputManager::CheckMouseButtonPress(const Mouse* state, MousePress& mousePress)
{
	if (mousePress.B == Mouse::UNINITIALIZED)
	{
		return false;
	}

	mousePress.SetPressed(state->GetKeyState(mousePress.B));

	return mousePress.Pressed();
}

bool InputManager::CheckAndApplyEdits()
{
	this->bIsEditing = false;

	for (unsigned int i = 0; i < EDIT_MODIFIERS_TO_CHECK; i++)
	{
		if (CurrentEditModifiers[i].IsEditing())
		{
			this->bIsEditing = true;

			Vec3 v;
			bool uniformScale;
			
			if (CheckAndSetEditMods(v, uniformScale))
			{
				if (LastKeyPress[EDIT_TRANS_KEY].Pressed())
				{
					CurrentEditModifiers[i].Translate(v);
				}
				if (LastKeyPress[EDIT_ROT_KEY].Pressed())
				{
					CurrentEditModifiers[i].Rotate(v);
				}
				if (LastKeyPress[EDIT_SCALE_KEY].Pressed())
				{
					CurrentEditModifiers[i].Scale(v, uniformScale);
				}
			}
		}
	}

	return false;
}

bool InputManager::CheckAndSetEditMods(Vec3& vOut, bool& uniformScaleOut)
{
	float x, y, z;

	// vOut.x
	if (LastKeyPress[EDIT_X_KEY].Pressed())
	{
		x = EDIT_TRANS_SPEED;
	}
	else if (LastKeyPress[EDIT_NEG_X_KEY].Pressed())
	{
		x = -EDIT_TRANS_SPEED;
	}
	else
	{
		x = 0.0f;
	}

	// vOut.y
	if (LastKeyPress[EDIT_Y_KEY].Pressed())
	{
		y = EDIT_TRANS_SPEED;
	}
	else if (LastKeyPress[EDIT_NEG_Y_KEY].Pressed())
	{
		y = -EDIT_TRANS_SPEED;
	}
	else
	{
		y = 0.0f;
	}

	// vOut.z
	if (LastKeyPress[EDIT_Z_KEY].Pressed())
	{
		z = EDIT_TRANS_SPEED;
	}
	else if (LastKeyPress[EDIT_NEG_Z_KEY].Pressed())
	{
		z = -EDIT_TRANS_SPEED;
	}
	else
	{
		z = 0.0f;
	}

	if (x == 0.0f && y == 0.0f && z == 0.0f)
	{
		return false;
	}

	vOut.set(x, y, z);
	uniformScaleOut = LastKeyPress[EDIT_UNIFORM_SCALE_KEY].Pressed();

	return true;
}

bool InputManager::SetEditObject(GameObject& obj, Keyboard::Key editKey)
{
	InputManager* inst = InputManager::GetInstance();

	for (unsigned int i = 0; i < EDIT_MODIFIERS_TO_CHECK; i++)
	{
		if (inst->CurrentEditModifiers[i].K->K == editKey)
		{
			inst->CurrentEditModifiers[i].SetObj(obj);
			return true;
		}
	}

	return false;
}

Keyboard* InputManager::GetKeyboard()
{
	InputManager* inst = InputManager::GetInstance();

	return inst->poKeyboard;
}

Mouse* InputManager::GetMouse()
{
	InputManager* inst = InputManager::GetInstance();

	return inst->poMouse;
}


InputManager* InputManager::GetInstance()
{
	assert(instance);

	return instance;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// KeyPress implementation begins
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void InputManager::KeyPress::SetPressed(bool p)
{
	NewPress = (p == true && LastPress == false) ? true : false;
	LastPress = p;
}

void InputManager::MousePress::SetPressed(bool p)
{
	NewPress = (p == true && LastPress == false) ? true : false;
	LastPress = p;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// EditModifiers implementation begins
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void InputManager::EditModifiers::Translate(const Vec3& v)
{
	this->pEditObject->AdjustTrans(v);

	const Vec3* objV = this->pEditObject->GetLocalTrans();

	char nameBuff[128];
	pEditObject->GetName(nameBuff, 128);

	Trace::out("%s Local Translate - (%f, %f, %f)\n", nameBuff, objV->x(), objV->y(), objV->z());
}

void InputManager::EditModifiers::Rotate(const Vec3& v)
{
	this->pEditObject->AdjustLocalRot(v);

	const Vec3* objV = this->pEditObject->GetLocalRot();

	char nameBuff[128];
	pEditObject->GetName(nameBuff, 128);

	Trace::out("%s Local Rotate - (%f, %f, %f)\n", nameBuff, objV->x(), objV->y(), objV->z());
}

void InputManager::EditModifiers::Scale(const Vec3& v, bool uniformScale)
{
	if (uniformScale)
	{
		this->pEditObject->AdjustScale(Vec3(v.y(), v.y(), v.y()));
	}
	else
	{
		this->pEditObject->AdjustScale(v);
	}

	const Vec3* objV = this->pEditObject->GetLocalScale();

	char nameBuff[128];
	pEditObject->GetName(nameBuff, 128);

	Trace::out("%s Local Scale - (%f, %f, %f)\n", nameBuff, objV->x(), objV->y(), objV->z());
}
