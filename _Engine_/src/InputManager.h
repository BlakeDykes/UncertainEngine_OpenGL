#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Keyboard.h"
#include "Mouse.h"
#include "MathEngine.h"
#include "AnimController.h"

class GameObject;

class InputManager
{
public:

	const static unsigned int MOUSE_BUTTONS_TO_CHECK = (unsigned int)Mouse::Button::SIZE;
	const static unsigned int KEYBOARD_KEYS_TO_CHECK = (unsigned int)Keyboard::Key::SIZE;
	const static unsigned int EDIT_MODIFIERS_TO_CHECK = 6;

	const float EDIT_TRANS_SPEED = 0.001f;
	const float EDIT_ROT_SPEED	 = 0.5f;
	const float EDIT_SCALE_SPEED = 0.001f;

	const static Keyboard::Key EDIT_TRANS_KEY	= Keyboard::Key::KEY_T;
	const static Keyboard::Key EDIT_ROT_KEY		= Keyboard::Key::KEY_R;
	const static Keyboard::Key EDIT_SCALE_KEY	= Keyboard::Key::KEY_S;

	const static Keyboard::Key EDIT_X_KEY				= Keyboard::Key::KEY_ARROW_RIGHT;
	const static Keyboard::Key EDIT_NEG_X_KEY			= Keyboard::Key::KEY_ARROW_LEFT;
	const static Keyboard::Key EDIT_Y_KEY				= Keyboard::Key::KEY_ARROW_DOWN;
	const static Keyboard::Key EDIT_NEG_Y_KEY			= Keyboard::Key::KEY_ARROW_UP;
	const static Keyboard::Key EDIT_Z_KEY				= Keyboard::Key::KEY_INSERT;
	const static Keyboard::Key EDIT_NEG_Z_KEY			= Keyboard::Key::KEY_DELETE;
	const static Keyboard::Key EDIT_UNIFORM_SCALE_KEY	=	Keyboard::Key::KEY_SLASH;

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	~InputManager();

	static void Create();
	static void Destroy();

	static bool SetEditObject(GameObject& obj, Keyboard::Key editKey);

	static void PrintControls();
	static void Update();

	static Keyboard* GetKeyboard();
	static Mouse* GetMouse();

private:

	struct KeyPress
	{
		Keyboard::Key K;

		KeyPress()
		: K(Keyboard::Key::UNINITIALIZED), LastPress(false), NewPress(false)
		{}

		KeyPress(Keyboard::Key k)
			: K(k), LastPress(false), NewPress(false)
		{}

		bool Pressed() const { return this->LastPress; }
		bool IsNewPress() const { return NewPress; }

		void SetPressed(bool p);

	private:
		bool LastPress;
		bool NewPress;

	};

	struct MousePress
	{
		Mouse::Button B;

		MousePress()
		: B(Mouse::Button::UNINITIALIZED), LastPress(false), NewPress(false)
		{ }

		MousePress(Mouse::Button b)
			: B(b), LastPress(false)
		{}

		bool Pressed() const { return LastPress; }
		bool IsNewPress() const { return NewPress; }

		void SetPressed(bool p);

	private:
		bool LastPress;
		bool NewPress;

	};

	struct EditModifiers
	{
		const KeyPress* K;

		enum
		{
			TRANSLATE,
			ROTATE,
			SCALE
		};

		EditModifiers()
			: K(nullptr), pEditObject(nullptr)
			{}

		EditModifiers(const KeyPress& k)
			: K(&k), pEditObject(nullptr)
		{}

		void SetObj(GameObject& obj) { this->pEditObject = &obj; }

		bool IsEditing() const { return K->Pressed(); }

		void Translate(const Vec3& v);
		void Rotate(const Vec3& v);
		void Scale(const Vec3& v, bool uniformScale);

	private:
		GameObject* pEditObject;
	};

	InputManager();
	static InputManager* GetInstance();
	void UpdateMouse();
	void UpdateKey();

	bool CheckKeyPress(const Keyboard* state, KeyPress& keyPress);
	bool CheckMouseButtonPress(const Mouse* state, MousePress& mousePress);
	bool isEditing() const { return this->bIsEditing; }

	bool CheckAndApplyEdits();
	bool CheckAndSetEditMods(Vec3& vOut, bool& uniformScaleOut);

	static InputManager* instance;
	Keyboard* poKeyboard;
	Mouse* poMouse;

	KeyPress LastKeyPress[KEYBOARD_KEYS_TO_CHECK];
	MousePress LastMousePress[MOUSE_BUTTONS_TO_CHECK];
	EditModifiers CurrentEditModifiers[EDIT_MODIFIERS_TO_CHECK];

	bool bIsEditing;
};

#endif