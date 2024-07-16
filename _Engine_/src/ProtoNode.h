#ifndef PROTO_NODE_H
#define PROTO_NODE_H

#include "PCSNode.h"
#include "NodeBase.h"
#include "ModelData.h"

class Texture;
class MeshNode;

namespace Uncertain
{
	class ArmData;

	class ProtoNode : public PCSNode
	{
	public:
		ProtoNode(const char* const protoName, unsigned int nodeIndex, MeshNode* mesh,
					Texture* text, ArmData* arm, ProtoNode* rootProto);
		ProtoNode();
		ProtoNode(const char* pName);
		ProtoNode(const ProtoNode&) = delete;
		ProtoNode& operator=(const ProtoNode&) = delete;
		virtual ~ProtoNode();

		void SetTexture(Texture* pText);
		ProtoNode* GetRootProto() const { return this->pRootProto; }
		
		void SetArmatureData(ArmData& armData) {this->pArmData = &armData; }
		ArmData* GetArmatureData() const {return this->pArmData; }

		const char* GetName();
		void Print();
		virtual void Wash() override;

		unsigned int NodeIndex;
		MeshNode* pMesh;
		Texture* pTexture;
		ArmData* pArmData;
		ProtoNode* pRootProto;

		char Name[ModelData::MODEL_NAME_SIZE];
	};

}

#endif // !PROTO_NODE_H
