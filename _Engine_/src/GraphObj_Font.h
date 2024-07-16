#ifndef GRAPH_OBJ_FONT_H
#define GRAPH_OBJ_FONT_H

#include "GraphicsObject.h"
#include "Font.h"

class UIStyle;

class GraphObj_Font : public GraphicsObject
{
public:

	struct DynamicVec2
	{
		float x;
		float y;

		void Set(float _x, float _y);
	};

	GraphObj_Font(const MeshNode* const _pMeshNode, const ShaderObject* const _pShader);

	GraphObj_Font() = delete;
	GraphObj_Font(const GraphObj_Font&) = delete;
	GraphObj_Font& operator=(const GraphObj_Font&) = delete;
	virtual ~GraphObj_Font();

	virtual void Render() override;

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual Mat4* GetScreenRect() const override { return this->poScreenRect; }
	
	virtual void SetFont(Font& font) override;
	virtual void SetMessage(const char* const _pMessage) override;
	virtual void SetLightColor(const Vec4& lightColor) override;
	virtual void SetUIStyle(const UIStyle& uiStyle) override;

	virtual void Wash() override;

	Font* pFont;
	const char* pMessage;
	DynamicVec2* poVerts;
	Vec4* poLightColor;
	float StartingX;
	Mat4* poScreenRect;
	const UIStyle* pUIStyle;

private:
	void SetScreenRect(float x, float y, float width, float height);

};

#endif // !GRAPH_OBJ_FONT_H
