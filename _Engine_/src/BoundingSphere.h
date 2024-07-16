#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#ifndef	BOUNDING_OBJECT_H
#include "BoundingObject.h"
#endif

using namespace Uncertain;

class BoundingSphere : public BoundingObject, public Align16
{
	struct MinMaxData
	{
		Vec3 v;
		unsigned int index;
		int pad[3];
	};

public:
	BoundingSphere();
	BoundingSphere(const BoundingSphere&) = delete;
	BoundingSphere& operator = (const BoundingSphere&) = delete;
	virtual ~BoundingSphere();

	virtual void Set(BoundingObjectData& protoData);
	virtual void Set(Vec3* pPoints, unsigned int numPts);
	virtual void Set(Mat4& world);
	virtual void Update(Mat4& world, Mesh* pMesh);
	virtual void UpdateGraphicsObject(GraphicsObject* pGraphObj);
	
	// Data: ---------------------------------
	Vec3* poCenter;
	float Radius;
	float pad[3];

private:
	void MostSeparatedPoints(unsigned int& minIndex, unsigned int& maxIndex, Vec3* pt, unsigned int numPts);
	void SphereFromDistantPoints(Vec3* pt, unsigned int numPts);
	void ExpandSphereToFit(Vec3& p);
};

#endif

// --- End of File ---
