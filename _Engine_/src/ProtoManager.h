#ifndef PROTO_MANAGER_H
#define PROTO_MANAGER_H

#include "ProtoNode.h"
#include "MeshData.pb.h"
#include "ModelData.pb.h"
#include "PCSTree.h"
#include "EngineNames.h"

namespace Uncertain
{
	class ProtoManager
	{
	public:

		ProtoManager(const ProtoManager&) = delete;
		ProtoManager& operator =(const ProtoManager&) = delete;

		static void Create();
		static void Destroy();

		static ProtoNode* Add(ModelName modelName, ProtoNode* pParent = nullptr);
		static ProtoNode* Add(ModelName modelName, TextureName textureName = TextureName::UNINITIALIZED, ArmatureName armatureName = ArmatureName::UNINITIALIZED, ProtoNode* pParent = nullptr);
		static void Remove(ProtoNode& pNode);
		static void PrintAll();

		static ProtoNode* FindByGLTFNodeIndex(ProtoNode& parent, unsigned int index);

	private:
		static ProtoManager* instance;

		ProtoManager();
		static ProtoManager* GetInstance();
		~ProtoManager();

		PCSTree* poRootTree;
	};

}

#endif // !PROTO_MANAGER_H
