#ifndef GRAPH_OBJ_UI_H
#define GRAPH_OBJ_UI_H

#include "GraphicsObject.h"
#include "Image.h"

class GraphObj_UI : public GraphicsObject
{
public:
	GraphObj_UI(const MeshNode* const _pMeshNode, const ShaderObject* const _pShader, Uncertain::Image* const _pImage);

	GraphObj_UI() = delete;
	GraphObj_UI(const GraphObj_UI&) = delete;
	GraphObj_UI& operator=(const GraphObj_UI&) = delete;
	virtual ~GraphObj_UI();

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual void Wash() override;

	Mat4* poMat4_uv;
	Image* pImage;
};

#endif // !GRAPH_OBJ_UI_H
