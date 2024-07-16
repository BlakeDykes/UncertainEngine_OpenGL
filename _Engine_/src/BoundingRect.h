#ifndef BOUNDING_RECT_H
#define BOUNDING_RECT_H

#ifndef	BOUNDING_OBJECT_H
#include "BoundingObject.h"
#endif

using namespace Uncertain;

class BoundingRect : public BoundingObject, public Align16
{
public:
	BoundingRect();
	BoundingRect(const BoundingRect&) = delete;
	BoundingRect& operator=(const BoundingRect&) = delete;
	virtual ~BoundingRect();

	virtual void Set(BoundingObjectData& protoData);
	virtual void Set(Vec3* pPoints, unsigned int numPts);
	virtual void Set(Mat4& world);
	virtual void Update(Mat4& world, Mesh* pMesh);
	virtual void UpdateGraphicsObject(GraphicsObject* pGraphObj);

	Mat4* pWorld;
};

#endif // !BOUNDING_RECT_H
