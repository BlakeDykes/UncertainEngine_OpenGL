#include "BoundingRect.h"
#include "GraphicsObject.h"
#include "BoundingObjectData.h"
#include "Mesh.h"

BoundingRect::BoundingRect()
	: pWorld(nullptr)
{
}

BoundingRect::~BoundingRect()
{
}

void BoundingRect::Set(BoundingObjectData& protoData)
{
	// Not needed since normalizing 2D
	AZUL_UNUSED_VAR(protoData);
}

void BoundingRect::Set(Vec3* pPoints, unsigned int numPts)
{
	// used in 3D
	AZUL_UNUSED_VAR(pPoints);
	AZUL_UNUSED_VAR(numPts);
	assert(false);
}

void BoundingRect::Set(Mat4& world)
{
	this->pWorld = &world;
}

void BoundingRect::Update(Mat4& world, Mesh* pMesh)
{
	AZUL_UNUSED_VAR(pMesh);
	AZUL_UNUSED_VAR(world);
}

void BoundingRect::UpdateGraphicsObject(GraphicsObject* pGraphObj)
{
	pGraphObj->SetWorld(*this->pWorld);
}
