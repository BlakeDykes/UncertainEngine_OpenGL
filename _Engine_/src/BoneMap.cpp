#include "BoneMap.h"


BoneMap::BoneMap()
	: NodeIndex(0), BoneIndex(0), ChildCount(0), poChildren(nullptr)
{
}

BoneMap::~BoneMap()
{
	if (this->poChildren)
	{
		delete[] this->poChildren;
		this->poChildren = nullptr;
	}
}

void BoneMap::Set(AnimData& anim, unsigned int boneIndex)
{
	this->BoneIndex = boneIndex;
	this->NodeIndex = (unsigned int)anim.Joints[boneIndex].Index;
	this->ChildCount = (unsigned int)anim.Joints[boneIndex].ChildrenCount;

	this->poChildren = new int[this->ChildCount]();
	int* pCur = this->poChildren;

	for (unsigned int j = 0; j < this->ChildCount; j++)
	{
		*pCur++ = anim.Joints[boneIndex].ChildIndex[j];
	}
}