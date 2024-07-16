#include "BoundingSphere.h"
#include "Mesh.h"
#include "GraphicsObject.h"
#include "BoundingObjectData.h"


BoundingSphere::BoundingSphere()
	: poCenter(new Vec3()), Radius(0.0f), pad{ 0 }
{
}

BoundingSphere::~BoundingSphere()
{
	delete this->poCenter;
}

void BoundingSphere::Set(BoundingObjectData& protoData)
{
	assert(protoData.BoundingType == BoundingObjectData::BOUNDING_TYPE::SPHERE);
	this->poCenter->set(*protoData.poCenter);
	this->Radius = protoData.Radius;
}

void BoundingSphere::Set(Vec3* pPoints, unsigned int numPts)
{
	assert(pPoints);

	this->SphereFromDistantPoints(pPoints, numPts);

	for (unsigned int i = 0; i < numPts; i++)
	{
		this->ExpandSphereToFit(pPoints[i]);
	}
}

void BoundingSphere::Set(Mat4& world)
{
	AZUL_UNUSED_VAR(world);

	// Only used in 2D
	assert(false);
}

void BoundingSphere::Update(Mat4& world, Mesh* pMesh)
{
	BoundingSphere* pMeshSphere = (BoundingSphere*)pMesh->poBounding;

	Vec3 aOut = Vec3(*pMeshSphere->poCenter * world);
	Vec3 bOut = Vec3((*pMeshSphere->poCenter + Vec3(1.0f, 0.0f, 0.0f)) * world);

	this->Radius = (bOut - aOut).len() * pMeshSphere->Radius;
	*this->poCenter = aOut;
}

void BoundingSphere::UpdateGraphicsObject(GraphicsObject* pGraphObj)
{
	pGraphObj->SetScale(
		Vec3(this->Radius,
			this->Radius,
			this->Radius)
	);
	pGraphObj->SetTrans(*this->poCenter);

}

void BoundingSphere::MostSeparatedPoints(unsigned int& minIndex, unsigned int& maxIndex, Vec3* pt, unsigned int numPts)
{
	unsigned int minx = 0;
	unsigned int maxx = 0;
	unsigned int miny = 0;
	unsigned int maxy = 0;
	unsigned int minz = 0;
	unsigned int maxz = 0;

	for (unsigned int i = 0; i < numPts; i++)
	{
		if (pt[i][x] < pt[minx][x])
			minx = i;
		if (pt[i][x] > pt[maxx][x])
			maxx = i;
		if (pt[i][y] < pt[miny][y])
			miny = i;
		if (pt[i][y] > pt[maxy][y])
			maxy = i;
		if (pt[i][z] < pt[minz][z])
			minz = i;
		if (pt[i][z] > pt[maxz][z])
			maxz = i;
	}

	MinMaxData data[6];

	data[0].v.set(pt[minx]);
	data[1].v.set(pt[miny]);
	data[2].v.set(pt[minz]);
	data[3].v.set(pt[maxx]);
	data[4].v.set(pt[maxy]);
	data[5].v.set(pt[maxz]);

	data[0].index = minx;
	data[1].index = miny;
	data[2].index = minz;
	data[3].index = maxx;
	data[4].index = maxy;
	data[5].index = maxz;

	float maxDist = 0.0f;
	float tempDist;

	for (int i = 0; i < 6; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			tempDist = (data[i].v - data[j].v).len();
			if (tempDist > maxDist)
			{
				maxDist = tempDist;
				minIndex = data[i].index;
				maxIndex = data[j].index;
			}
		}
	}
}

void BoundingSphere::SphereFromDistantPoints(Vec3* pt, unsigned int numPts)
{
	unsigned int min = 0;
	unsigned int max = 0;
	this->MostSeparatedPoints(min, max, pt, numPts);

	*this->poCenter = (pt[min] + pt[max]) * 0.5f;
	this->Radius = sqrtf((pt[max] - *this->poCenter).dot(pt[max] - *this->poCenter));
}

void BoundingSphere::ExpandSphereToFit(Vec3& p)
{
	float distance2 = (p - *this->poCenter).dot(p - *this->poCenter);

	if (distance2 > this->Radius * this->Radius)
	{
		float distance = sqrtf(distance2);
		float newRadius = (this->Radius + distance) * 0.5f;
		float centerAdjustment = (newRadius - this->Radius) / distance;
		this->Radius = newRadius;
		*this->poCenter += (p - *this->poCenter) * centerAdjustment;
	}
}

