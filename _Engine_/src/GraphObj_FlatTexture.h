#ifndef GRAPH_OBJ_FLAT_TEX_H
#define GRAPH_OBJ_FLAT_TEX_H

#include "GraphicsObject.h"

class Texture;

class GraphObj_FlatTexture : public GraphicsObject
{
public:
	Texture* pTexture;

	GraphObj_FlatTexture(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj, TextureName name);
	GraphObj_FlatTexture(const MeshNode* const _pMeshNode, const ShaderObject*);

	virtual ~GraphObj_FlatTexture();

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual void SetTexture(TextureName name, unsigned int modelMatIndex = UINT_MAX) override;
	virtual void SetTexture(Texture& text) override;

	virtual void Wash() override;
};

#endif