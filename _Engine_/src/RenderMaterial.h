#ifndef RENDER_MATERIAL_H
#define RENDER_MATERIAL_H

#include "EngineNames.h"
#include "sb7.h"

class RenderMaterial
{
public:
	const MATERIAL_ID GetID() const { return this->MatID; }
	void SetID(MATERIAL_ID id) { this->MatID = id; }

	virtual const char* GetName() { return Stringify(this->Name); }
	virtual bool Compare(RenderMaterial& pNode) { return this->MatID == pNode.MatID; };

	virtual void Print() = 0;
	virtual void Wash() = 0;

	MaterialName Name;
protected:
	RenderMaterial() = delete;
	RenderMaterial(const RenderMaterial&) = delete;
	RenderMaterial& operator=(const RenderMaterial&) = delete;
	virtual ~RenderMaterial() = default;

	RenderMaterial(MaterialName name) : Name(name), MatID(-1) {}


	virtual void SetState() = 0;
	virtual void SetDataGPU() = 0;
	virtual void Draw() = 0;
	virtual void RestoreState() = 0;

	MATERIAL_ID MatID;
};

#endif