#include "BoundingNull.h"


void BoundingNull::Set(BoundingObjectData& protoData) { AZUL_UNUSED_VAR(protoData); }
void BoundingNull::Set(Vec3* pPoints, unsigned int numPts) { AZUL_UNUSED_VAR(pPoints); AZUL_UNUSED_VAR(numPts); }
void BoundingNull::Set(Mat4& world) { AZUL_UNUSED_VAR(world); }

void BoundingNull::Update(Mat4& world, Mesh* pMesh) { AZUL_UNUSED_VAR(world); AZUL_UNUSED_VAR(pMesh); }

void BoundingNull::UpdateGraphicsObject(GraphicsObject* pGraphObj) { AZUL_UNUSED_VAR(pGraphObj); }