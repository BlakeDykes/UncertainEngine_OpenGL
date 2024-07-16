#ifndef GAME_OBJECT_MAN_H
#define GAME_OBJECT_MAN_H

#include "ManagerBase.h"
#include "PCSTree.h"
#include "EngineNames.h"
#include "MathEngine.h"
#include "GraphObj_PhongColor.h"
#include "ProtoNode.h"
#include "Camera.h"
#include "_Time.h"
#include "GameObjectAnim.h"
#include "GameObjectFont.h"
#include "AnimController.h"
#include "BoneMap.h"
#include "Font.h"

class GameObject;
class UIManager;
class UINode;
class GameObjectUI;
class GameObjectUIElement;
class GameObjectUIRoot;
class GameObjectFont;
class CommandQueue;

namespace Uncertain
{
	class GameObjectManager
	{
	public:

		const static bool GENERATE_BOUNDING_GRAPHICS = true;
		const static bool DRAW_BOUNDING_GRAPHICS = false;


		GameObjectManager(const GameObjectManager&) = delete;
		GameObjectManager& operator =(const GameObjectManager&) = delete;

		static void Create();
		static void Destroy();

		static void Update(_Time currentTime);
		static void Draw(void);

		//static GameObject* Add(MeshName meshName, ShaderName shaderName, TextureName textureName,
		//						MaterialName materialName, const char* const objName, 
		//						GameObject* pParent = nullptr, bool generateBoundingGraphics = GENERATE_BOUNDING_GRAPHICS);

		//static GameObject* Add(MeshName meshName, ShaderName shaderName,
		//						MaterialName materialName, const char* const objName, 
		//						GameObject* pParent = nullptr, bool generateBoundingGraphics = GENERATE_BOUNDING_GRAPHICS);

		static GameObject* Add(ProtoNode& protoNode, ShaderName shaderName, MaterialName materialName, const char* pName = nullptr,
								TextureName textureName = TextureName::UNINITIALIZED, GameObject* pParent = nullptr, 
								bool generateBoundingGraphics = GENERATE_BOUNDING_GRAPHICS);

		static GameObjectAnim* Add(ProtoNode& protoNode, ShaderName shaderName, MaterialName materialName,
									AnimController& animController, const char* pName = nullptr,
									TextureName textureName = TextureName::UNINITIALIZED, GameObject* pParent = nullptr,
									bool generateBoundingGraphics = GENERATE_BOUNDING_GRAPHICS);

		static GameObject* Add(Image& image, ShaderName shaderName, GameObject* pParent = nullptr, bool generateBoundingGraphics = GENERATE_BOUNDING_GRAPHICS);

		static GameObject* AddRoot2D(const char* const rootName, GameObject* pParent = nullptr);
		static GameObject* AddRoot3D(const char* const rootName, GameObject* pParent = nullptr);
		

		static void Remove(GameObject& pNode);

		static void ToggleBoundingObjects();

		static void SetScale(GameObject* pObj, const Vec3& scale);
		static void SetPos(GameObject* pObj, const Vec3& pos);
		static void SetRot(GameObject* pObj, const Quat& q);
		static void SetLocalRot(GameObject* pObj, const Vec3& r);
		static void SetLocalPos(GameObject* pObj, const Vec3& pos);
		static void SetDeltaRot(GameObject* pObj, const Vec3& q);

		static void SetLightColor(GameObject* pObj, const Vec4& color);
		static void SetLightPos(GameObject* pObj, const Vec3& pos);
		static void SetPhongData(GameObject* pObj, const PhongData& data);
		static void SetTexture(GameObject* pObj, TextureName name);

		static void SetMessage(GameObjectFont* pObj, const char* pMessage);
		
		static void PrintAll();

		// UI manager functions
		class UI
		{
		private:
			friend UIManager;

			static GameObjectUIRoot* AddRoot(UINode& uiNode, const char* const name);
			static GameObjectUIElement* Add(Image& imageName, ShaderName shaderName, GameObjectUI* pParent, bool generateBoundingGraphics = GENERATE_BOUNDING_GRAPHICS);
			static GameObjectFont* Add(Font& font, const char* const pMessage, ShaderName shaderName, GameObjectUI* pParent, bool generateBoundingGraphics = GENERATE_BOUNDING_GRAPHICS);
			static void Remove(GameObjectUIElement& pNode);
			static void InsertUIObject(GameObjectUI* pUINode, GameObject* pParent);
		};

	private:
		static GameObjectManager* instance;

		GameObjectManager();
		static GameObjectManager* GetInstance();
		~GameObjectManager();

		static void InsertProtoChildren(ProtoNode& pNode, GameObjectAnim* pParent, ShaderName shaderName, MaterialName materialName,
			AnimController& animController, BoneMap* boneMap, TextureName textureName, bool generateBoundingGraphics = GENERATE_BOUNDING_GRAPHICS);

		PCSTree* poRootTree;
		bool DrawBoundingObjects;
		CommandQueue* pCommandQueue;

	};
}


#endif // !GAME_OBJECT_MAN_H
