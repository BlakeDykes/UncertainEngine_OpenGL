#include "FrameBucket.h"

namespace Uncertain
{

	FrameBucket::FrameBucket()
		: Name(AnimName::UNINITIALIZED), NumFrames(0), poFrames(nullptr)
	{
	}

	FrameBucket::~FrameBucket()
	{
		if (poFrames)
		{
			delete[] poFrames;
		}
	}

	void FrameBucket::Set(AnimName name, AnimData& anim)
	{
		this->NumFrames = anim.FrameCount;
		this->Name = name;
		this->NumBones = anim.JointCount;

		assert(NumFrames > 0);
		assert(!poFrames);

		this->poFrames = new SBOFrame[NumFrames];

		Bone* poTempBone = new Bone[NumBones + 1]();

		for (unsigned int i = 0; i < NumFrames; i++)
		{
			poFrames[i].KeyTime = anim.poFrames[i].Time * _Time(_Time::Duration::ONE_SECOND);

			for (unsigned int j = 0; j < NumBones; j++)
			{
				poTempBone[j].T.set(
					anim.poFrames[i].poBones[j].poTrans.x,
					anim.poFrames[i].poBones[j].poTrans.y,
					anim.poFrames[i].poBones[j].poTrans.z
				);

				poTempBone[j].R.set(
					anim.poFrames[i].poBones[j].poRot.x,
					anim.poFrames[i].poBones[j].poRot.y,
					anim.poFrames[i].poBones[j].poRot.z,
					anim.poFrames[i].poBones[j].poRot.w
				);

				poTempBone[j].S.set(
					anim.poFrames[i].poBones[j].poScale.x,
					anim.poFrames[i].poBones[j].poScale.y,
					anim.poFrames[i].poBones[j].poScale.z
				);
			}

			poFrames[i].SSBO_Bones->Set(anim.JointCount + 1, sizeof(Bone), poTempBone, GL_STATIC_DRAW);
		}

		delete[] poTempBone;
	}

	void FrameBucket::Wash()
	{
		Name = AnimName::UNINITIALIZED;
		NumFrames = 0;
		NumBones = 0;

		if (poFrames)
		{
			delete[] poFrames;
			poFrames = nullptr;
		}
	}

	bool FrameBucket::Compare(NodeBase& pNode)
	{
		FrameBucket* pComp = (FrameBucket*)&pNode;


		return this->Name == pComp->Name;
	}

	const char* FrameBucket::GetName()
	{
		return Stringify(Name);
	}

	_Time FrameBucket::GetMaxTime() const
	{
		if(poFrames)
		{ 
			return poFrames[NumFrames - 1].KeyTime; 
		}
		else
		{
			return _Time(_Time::Duration::ZERO);
		}
	}


	SBOFrame::SBOFrame()
		: KeyTime(), SSBO_Bones(new SSBO())
	{
	}

	SBOFrame::~SBOFrame()
	{
		delete SSBO_Bones;
	}
}

