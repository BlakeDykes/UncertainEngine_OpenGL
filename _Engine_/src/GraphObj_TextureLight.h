#ifndef GRAPH_OBJ_TEXTURE_LIGHT_H
#define GRAPH_OBJ_TEXTURE_LIGHT_H

#include "GraphicsObject.h"
#include "EngineNames.h"

class Texture;

using namespace Uncertain;

class GraphObj_TextureLight : public GraphicsObject
{
public:
	Texture* pTexture;
	Vec4* poLightColor;
	Vec3* poLightPos;
	Vec4* poBaseColor;

	GraphObj_TextureLight() = delete;
	GraphObj_TextureLight(const GraphObj_TextureLight&) = delete;
	GraphObj_TextureLight& operator=(const GraphObj_TextureLight&) = delete;
	virtual ~GraphObj_TextureLight();

	GraphObj_TextureLight(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj);


	GraphObj_TextureLight(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj,
		TextureName textName, Vec4& lightColor, Vec3& lightPos);

	virtual void SetTexture(TextureName name, unsigned int modelMatIndex = UINT_MAX) override;
	virtual void SetTexture(Texture& text) override;
	virtual void SetLightColor(const Vec4& lightColor) override;
	virtual void SetLightPos(const Vec3& lightPos) override;

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual void Wash() override;
};

#endif