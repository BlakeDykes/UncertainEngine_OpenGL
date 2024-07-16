#ifndef BOUDNING_NULL_H
#define BOUNDING_NULL_H

#ifndef	BOUNDING_OBJECT_H
#include "BoundingObject.h"
#endif

using namespace Uncertain;

class BoundingNull : public BoundingObject
{
public:
	BoundingNull() = default;
	BoundingNull(const BoundingNull&) = delete;
	BoundingNull& operator=(const BoundingNull&) = delete;
	virtual ~BoundingNull() = default;

	virtual void Set(BoundingObjectData& protoData);
	virtual void Set(Vec3* pPoints, unsigned int numPts);
	virtual void Set(Mat4& world);

	virtual void Update(Mat4& world, Mesh* pMesh);
	virtual void UpdateGraphicsObject(GraphicsObject* pGraphObj);
};


#endif // !BOUDNING_NULL_H
