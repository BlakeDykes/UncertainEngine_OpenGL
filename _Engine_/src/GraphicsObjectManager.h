#ifndef GRAPHICS_OBJ_MAN_H
#define GRAPHICS_OBJ_MAN_H

#include "ManagerBase.h"
#include "EngineNames.h"
#include "GraphicsObjects_Wrapper.h"
#include "ProtoNode.h"
#include "Camera.h"
#include "AnimController.h"
#include "Armature.h"

class GraphicsObjectNode;
class GraphicsObject;
class ShaderObject;

using namespace Uncertain;

class GraphicsObjectManager : public ManagerBase
{
public:

	GraphicsObjectManager(const GraphicsObjectManager&) = delete;
	GraphicsObjectManager& operator =(const GraphicsObjectManager&) = delete;

	static void Create(int initialReserve = 5, int deltaGrow = 5);
	static void Destroy();

	static GraphicsObjectNode* Add(MeshName meshName, ShaderName shaderName, MaterialName matName, bool generateBoundingSphere);
	static GraphicsObjectNode* Add(ProtoNode& protoNode, ShaderName shaderName, MaterialName matName, bool generateBoundingSphere, Armature* armature = nullptr);
	static GraphicsObjectNode* Add(Image& imageName, ShaderName shaderName, MaterialName matName, bool generateBoundingSphere);
	static GraphicsObjectNode* Add(Font& font, const char* const pMessage, ShaderName shaderName, MaterialName matName, bool generateBoundingSphere);
	static void Remove(GraphicsObjectNode& graphObj);
	
	static void PrintAll();

protected:
	virtual NodeBase* CreateNode() override;

private:
	GraphicsObjectManager(int initialReserve, int deltaGrow);
	static GraphicsObjectManager* GetInstance();
	virtual ~GraphicsObjectManager();
	GraphicsObject* GenerateMaterial(MaterialName matName, MeshNode& meshNode, ShaderObject& shader, Image* pImage = nullptr, Armature* armature = nullptr);

	static GraphicsObjectManager* instance;

	GraphicsObjectNode* poCompNode;
	MATERIAL_ID MaterialCount;

};


#endif // !GRAPHICS_OBJ_MAN_H
