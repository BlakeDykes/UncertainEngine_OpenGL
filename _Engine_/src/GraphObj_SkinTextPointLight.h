#ifndef GRAPH_OBJ_SKIN_TEXT_POINT_LIGHT_H
#define GRAPH_OBJ_SKIN_TEXT_POINT_LIGHT_H

#include "GraphicsObject.h"
#include "EngineNames.h"

class Texture;

using namespace Uncertain;

class GraphObj_SkinTextPointLight : public GraphicsObject
{
public:
	SSBO* pBoneResultBuffer;
	Texture* pTexture;
	Vec4* poLightColor;
	Vec3* poLightPos;
	Vec4* poBaseColor;

	GraphObj_SkinTextPointLight() = delete;
	GraphObj_SkinTextPointLight(const GraphObj_SkinTextPointLight&) = delete;
	GraphObj_SkinTextPointLight& operator=(const GraphObj_SkinTextPointLight&) = delete;
	virtual ~GraphObj_SkinTextPointLight();

	GraphObj_SkinTextPointLight(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj, SSBO& boneResultBuffer);

	virtual void SetTexture(TextureName name, unsigned int modelMatIndex = UINT_MAX) override;
	virtual void SetTexture(Texture& text) override;
	virtual void SetLightColor(const Vec4& lightColor) override;
	virtual void SetLightPos(const Vec3& lightPos) override;
	virtual void SetBoneWorldResultBuffer(SSBO& boneResultBuffer) override;

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual void Wash() override;
};

#endif // !GRAPH_OBJ_SKIN_TEXT_POINT_LIGHT_H