#ifndef BONE_MAP_H
#define BONE_MAP_H

#include "AnimData.h"

class BoneMap
{
public:
	BoneMap();
	BoneMap(const BoneMap&) = delete;
	BoneMap& operator=(const BoneMap&) = delete;
	~BoneMap();

	void Set(AnimData& anim, unsigned int boneIndex);

	unsigned int NodeIndex;
	unsigned int BoneIndex;
	unsigned int ChildCount;
	int* poChildren;
};

#endif // !BONE_MAP_H

