#ifndef BONE_H
#define BONE_H

#include "MathEngine.h"
#include "AnimData.h"

namespace Uncertain
{
	struct Bone : public Align16
	{
		Vec3 T;
		Quat R;
		Vec3 S;

		Bone()
			:T(0.0f, 0.0f, 0.0f), R(0.0f, 0.0f, 0.0f, 1.0f), S(1.0f, 1.0f, 1.0f)
		{
		}

		Bone(AnimData::Node& node)
		{
			T.set(node.T.x, node.T.y, node.T.z);
			R.set(node.R.x, node.R.y, node.R.z, node.R.w);
			S.set(node.S.x, node.S.y, node.S.z);
		}
	};
}

#endif // !BONE_H
