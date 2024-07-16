#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"
#include "RenderMaterial.h"
#include "MeshNode.h"
#include "Font.h"
#include "SSBO.h"

using namespace Uncertain;

struct PhongData;
class Texture;
class UIStyle;

class GraphicsObject : public RenderMaterial
{
public:

	static const Vec4 DEFAULT_LIGHT_COLOR;
	static const Vec3 DEFAULT_LIGHT_POS;

	GraphicsObject(MaterialName name, const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj, bool isNull = false);

	GraphicsObject() = delete;
	GraphicsObject(const GraphicsObject&) = delete;
	GraphicsObject operator =(const GraphicsObject&) = delete;
	virtual ~GraphicsObject();

	virtual void Render();

	Mesh* GetMesh() const { return this->pMeshNode->GetMesh(); }
	unsigned int GetMeshNodeIndex() const { return this->pMeshNode->GetNodeIndex(); }
	Uncertain::Mat4& GetWorld() { return *this->poWorld; }
	void SetWorld(const Uncertain::Mat4& _world) { *this->poWorld = _world; }

	virtual Uncertain::Mat4* GetScreenRect() const { assert(false); return nullptr; }
	virtual void SetTexture(TextureName name, unsigned int modelMatIndex = UINT_MAX);
	virtual void SetTexture(Texture& text);
	virtual void SetLightColor(const Vec4& lightColor);
	virtual void SetLightPos(const Vec3& lightPos);
	virtual void SetPhongData(const PhongData& _pData);
	virtual void SetFont(Font& font);
	virtual void SetMessage(const char* const _pMessage);
	virtual void SetBoneWorldResultBuffer(SSBO& boneResultBuffer);
	virtual void SetUIStyle(const UIStyle& uiStyle);

	virtual void SetScale(const Vec3& v);
	virtual void SetTrans(const Vec3& v);

	virtual void Print() override;
	virtual void Wash() override;

	bool IsNull() const { return bIsNull; }

protected:
	virtual void SetDataGPU() override;

	const MeshNode* pMeshNode;
	Uncertain::Mat4* poWorld;
	const ShaderObject* pShaderObj;
	bool bIsNull;
};


#endif