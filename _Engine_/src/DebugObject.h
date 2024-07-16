#ifndef DEBUG_OBSERVER_H
#define DEBUG_OBSERVER_H

class GameObjectFont;

class DebugObject
{
public:
	
	static const unsigned int MESSAGE_BUFFER_SIZE = 128;

	DebugObject(GameObjectFont& debugFont);

	DebugObject() = delete;
	DebugObject(const DebugObject&) = delete;
	GameObjectFont& operator = (const DebugObject&) = delete;
	virtual ~DebugObject();

	void Display(const char* pMessage = nullptr);

	void SetMessage(const char* message, const char* pre, const char* post);

	void Wash() { this->pGameObjectFont = nullptr; }

private:
	GameObjectFont* pGameObjectFont;
	char MessageBuffer[MESSAGE_BUFFER_SIZE];

};

#endif // !DEBUG_OBSERVER_H
