#ifndef GRAPH_OBJ_SPRITE_H
#define GRAPH_OBJ_SPRITE_H

#include "GraphicsObject.h"
#include "Image.h"

class Texture;

class GraphObj_Sprite : public GraphicsObject
{
public:

	GraphObj_Sprite(const MeshNode* const _pMeshNode, const ShaderObject* const _pShader, Image* const _pImage);

	GraphObj_Sprite() = delete;
	GraphObj_Sprite(const GraphObj_Sprite&) = delete;
	GraphObj_Sprite& operator=(const GraphObj_Sprite&) = delete;
	virtual ~GraphObj_Sprite();

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;


	virtual void Wash() override;

	Image* pImage;
	Mat4* poMatrix_uv;
	Mat4* poMatrix_orig;
};

#endif