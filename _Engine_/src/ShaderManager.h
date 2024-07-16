#ifndef SHADER_MAN_H
#define SHADER_MAN_H

#include "ManagerBase.h"
#include "EngineNames.h"
#include "ShaderObject.h"


class ShaderManager : public ManagerBase
{
public:
	ShaderManager() = delete;
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator =(const ShaderManager&) = delete;

	static void Create(bool intitAll, int initialReserved = 5, int deltaGrow = 5);
	static void Destroy();

	static ShaderObject* Add(ShaderObject::ShaderType type, ShaderName name);
	static ShaderObject* Find(ShaderName name);
	static void Remove(ShaderObject& pNode);
	static void PrintAll();

protected:
	virtual NodeBase* CreateNode() override;

private:
	ShaderManager(int initialReserved, int deltaGrow);
	virtual ~ShaderManager();
	static ShaderManager* GetInstance();
	void InitAll();
	void Clear();

	static ShaderManager* instance;
	ShaderObject* pCompNode;
};

#endif // !SHADER_MAN_H
