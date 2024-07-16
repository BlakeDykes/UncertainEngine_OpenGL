#include "ShaderManager.h"
#include "DLinkManager.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::ShaderManager(int initialReserved, int deltaGrow)
	:ManagerBase(*new DLinkManager(), *new DLinkManager())
{
	this->pCompNode = new ShaderObject();

	this->SetReserve(initialReserved, deltaGrow);
}

ShaderManager::~ShaderManager()
{
	this->Clear();
	delete this->pCompNode;
}

void ShaderManager::Create(bool initAll, int initialReserved, int deltaGrow)
{
	assert(!instance);

	if (!instance)
	{
		instance = new ShaderManager(initialReserved, deltaGrow);

		if (initAll)
		{
			instance->InitAll();
		}
		else
		{
			Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::NULL_SHADER);
		}
	}
}

void ShaderManager::Destroy()
{
	ShaderManager* inst = ShaderManager::GetInstance();

	delete inst;

	ShaderManager::instance = nullptr;
}

ShaderObject* ShaderManager::Add(ShaderObject::ShaderType type, ShaderName name)
{
	ShaderManager* inst = ShaderManager::GetInstance();

	ShaderObject* pNode = (ShaderObject*)inst->BaseAdd();
	assert(pNode);

	pNode->Set(type, name, GetFileName(name));

	return pNode;
}

ShaderObject* ShaderManager::Find(ShaderName name)
{
	ShaderManager* inst = ShaderManager::GetInstance();

	inst->pCompNode->Name = name;

	return (ShaderObject*)inst->BaseFind(*inst->pCompNode);
}

void ShaderManager::Remove(ShaderObject& pNode)
{
	ShaderManager* inst = ShaderManager::GetInstance();

	inst->BaseRemove(pNode);
}

void ShaderManager::PrintAll()
{
	ShaderManager* inst = ShaderManager::GetInstance();

	Trace::out("\n");
	Trace::out("--------------------------\n");
	Trace::out("----- Active Shaders -----\n");
	Trace::out("--------------------------\n");

	inst->BasePrintAll();
}

NodeBase* ShaderManager::CreateNode()
{
	return new ShaderObject();
}

ShaderManager* ShaderManager::GetInstance()
{
	assert(instance);

	return instance;
}

void ShaderManager::InitAll()
{
	this->Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::COLOR_LIGHT);
	this->Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::COLOR_CONST);
	this->Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::COLOR_PHONG);
	this->Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::TEXTURE_SIMPLE);
	this->Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::TEXTURE_POINT_LIGHT);
	this->Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::SKIN_TEXT_POINT_LIGHT);
	this->Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::SPRITE_FLAT);
	this->Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::UI_FLAT);
	this->Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::FONT_FLAT);
	this->Add(ShaderObject::ShaderType::GRAPHICS, ShaderName::NULL_SHADER);

	this->Add(ShaderObject::ShaderType::COMPUTE, ShaderName::COMPUTE_BONE_WORLD);
	this->Add(ShaderObject::ShaderType::COMPUTE, ShaderName::COMPUTE_ANIM_MIXER);
}

void ShaderManager::Clear()
{
	this->BaseClear();
}