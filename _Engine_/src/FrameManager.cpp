#include "FrameManager.h"
#include "FrameBucket.h"
#include "DLinkManager.h"
#include "ProtoData_Wrapper.h"

namespace Uncertain
{

	FrameManager* FrameManager::instance = nullptr;

	FrameManager::FrameManager(int initialReserved, int deltaGrow)
		:ManagerBase(*new DLinkManager(), *new DLinkManager())
	{
		this->SetReserve(initialReserved, deltaGrow);
	}

	FrameManager::~FrameManager()
	{
		this->BaseClear();
		delete this->pCompNode;
	}


	void FrameManager::Create(int initialReserved, int deltaGrow)
	{
		assert(initialReserved >= 0);
		assert(deltaGrow > 0);
		assert(!instance);

		if (!instance)
		{
			instance = new FrameManager(initialReserved, deltaGrow);

			instance->pCompNode = new FrameBucket();
		}
	}

	void FrameManager::Destroy()
	{
		FrameManager* inst = FrameManager::GetInstance();

		delete inst;

		instance = nullptr;
	}

	FrameBucket* FrameManager::Add(AnimName name)
	{
		FrameManager* inst = FrameManager::GetInstance();

		FrameBucket* pNode = (FrameBucket*)inst->BaseAdd();

		AnimData anim;
		ProtoData_Wrapper::ReadFromFile(GetFileName(name), anim);

		pNode->Set(name, anim);

		return pNode;
	}

	FrameBucket* FrameManager::Find(AnimName name)
	{
		FrameManager* inst = FrameManager::GetInstance();

		inst->pCompNode->SetName(name);

		return (FrameBucket*)inst->BaseFind(*inst->pCompNode);
		
	}

	void FrameManager::Remove(FrameBucket& pNode)
	{
		FrameManager* inst = FrameManager::GetInstance();

		inst->BaseRemove(pNode);
	}


	NodeBase* FrameManager::CreateNode()
	{
		return new FrameBucket();
	}

	FrameManager* FrameManager::GetInstance()
	{
		assert(instance);
		return instance;
	}

	void FrameManager::Clear()
	{
		this->BaseClear();
	}
}
