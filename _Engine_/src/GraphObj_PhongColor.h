#ifndef GRAPH_OBJ_PHONG_H
#define GRAPH_OBJ_PHONG_H

#include "GraphicsObject.h"
#include "EngineNames.h"

struct PhongData : public Align16
{
	Vec3 LightPos = Vec3(0.0f, 1.0f, 0.0f);
	Vec4 LightColor = Vec4(1.0f, 0.0f, 1.0f, 1.0f);
	Vec3 KeyLightPos = Vec3(1.0f, 1.0f, 0.0f);
	Vec3 ViewPos = Vec3(0.0f, 0.0f, -4.5f);
	float KeySpecularIntensity = 1.0f;
	float KeyHighlightSize = 1.0f;
	float AmbientStrength = .5f;

	void Clear();
};


class GraphObj_PhongColor : public GraphicsObject
{
public:
	PhongData* pData;

	GraphObj_PhongColor() = delete;
	GraphObj_PhongColor(const GraphObj_PhongColor&) = delete;
	GraphObj_PhongColor& operator=(const GraphObj_PhongColor&) = delete;
	virtual ~GraphObj_PhongColor();

	GraphObj_PhongColor(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj);

	virtual void SetLightColor(const Vec4& lightColor) override;
	virtual void SetLightPos(const Vec3& lightPos) override;
	virtual void SetPhongData(const PhongData& data) override;

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual void Wash() override;
};

#endif // !
