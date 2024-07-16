#ifndef BOUDNING_OBJECT_H
#define BOUNDING_OBJECT_H

#include "MathEngine.h"

class GraphicsObject;
class BoundingObjectData;
class Mesh;

using namespace Uncertain;

class BoundingObject
{
public:
	virtual ~BoundingObject() = default;

	virtual void Set(BoundingObjectData& protoData) = 0;
	virtual void Set(Vec3* pPoints, unsigned int numPts) = 0;
	virtual void Set(Mat4& world) = 0;

	virtual void Update(Mat4& world, Mesh* pMesh) = 0;
	virtual void UpdateGraphicsObject(GraphicsObject* pGraphObj) = 0;	
};


#endif // !BOUDNING_OBJECT_H
