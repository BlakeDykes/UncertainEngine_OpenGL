#include "Anim.h"
#include "AnimMixer.h"
#include "Vec3App.h"
#include "QuatApp.h"
#include "SSBO.h"
#include "ShaderObject.h"
#include "FrameManager.h"
#include "FrameBucket.h"

namespace Uncertain
{
	Anim::Anim(AnimName name)
		: NumBones(0), NumFrames(0), poMap(nullptr), poBoneResult(nullptr), pFrames(nullptr), 
		pCallback(nullptr), poMixer(nullptr)
	{
		this->pFrames = FrameManager::Find(name);
		if (!pFrames)
		{
			pFrames = FrameManager::Add(name);
		}

		this->TotalTime = this->FindMaxTime();
		this->NumFrames = pFrames->GetNumFrames();
		this->NumBones = pFrames->GetNumBones();
		this->poBoneResult = new Bone[NumBones + 1];
		memcpy_s(this->pName, AnimData::ANIM_NAME_SIZE, pFrames->GetName(), AnimData::ANIM_NAME_SIZE);

		this->poMixer = new AnimMixer(*this);
	}

	Anim::Anim(ANIM_SPECIAL specialType, unsigned int numBones)
		: poMap(nullptr), poBoneResult(nullptr), pFrames(nullptr), 
		pCallback(nullptr), poMixer(nullptr)
	{
		this->NumBones = numBones;

		switch (specialType)
		{
		case Uncertain::Anim::ANIM_SPECIAL::IDENTITY:
			this->NumFrames = 1;
			this->poBoneResult = new Bone[this->NumBones + 1]();
			
			//
			//for (unsigned int i = 0; i < this->NumBones; i++)
			//{
			//	this->poBoneResult[i].T.set(anim.poFrames[0].poBones[i].poTrans.x, anim.poFrames[0].poBones[i].poTrans.y, anim.poFrames[0].poBones[i].poTrans.z);
			//	this->poBoneResult[i].R.set(anim.poFrames[0].poBones[i].poRot.x, anim.poFrames[0].poBones[i].poRot.y, anim.poFrames[0].poBones[i].poRot.z, anim.poFrames[0].poBones[i].poRot.w);
			//	this->poBoneResult[i].S.set(anim.poFrames[0].poBones[i].poScale.x, anim.poFrames[0].poBones[i].poScale.y, anim.poFrames[0].poBones[i].poScale.z);
			//}

			this->poMixer = new AnimMixer(*this);

			break;

		case Uncertain::Anim::ANIM_SPECIAL::BLEND:
		{
			this->poBoneResult = new Bone[this->NumBones + 1]();
			this->poMixer = new AnimMixer(*this);

			break;
		}

		default:
			break;
		}

	}

	Anim::~Anim()
	{
		if (this->pCallback)
		{
			delete this->pCallback;
		}

		if (this->poBoneResult)
		{
			delete[] this->poBoneResult;
		}

		if (this->poMap)
		{
			delete[] this->poMap;
		}

		if (this->poMixer)
		{
			delete this->poMixer;
		}
	}

	void Anim::Animate(_Time tCurr, ShaderObject* _pAnimMixerSO)
	{
		this->privAnimate(tCurr, _pAnimMixerSO);
	}

	// Blend bone TRS between previous and next keyframe
	void Anim::privAnimate(_Time tCurr, ShaderObject* _pAnimMixerSO)
	{
		SBOFrame* pNextFrame = this->pFrames->GetFrames();

		unsigned int i = 1;

		while (tCurr >= pNextFrame->KeyTime && i < NumFrames)
		{
			pNextFrame++;
			i++;
		}

		SBOFrame* pPrevFrame = pNextFrame - 1;

		float tS = (tCurr - pPrevFrame->KeyTime) / (pNextFrame->KeyTime - pPrevFrame->KeyTime);

		this->poMixer->Blend(_pAnimMixerSO, pPrevFrame->SSBO_Bones, pNextFrame->SSBO_Bones, tS);
	}

	_Time Anim::FindMaxTime()
	{
		if (pFrames)
		{
			return pFrames->GetMaxTime();
		}
		else
		{
			return _Time(_Time::Duration::ZERO);
		}
	}

	//void Anim::SetFrames(AnimData& anim)
	//{

	//	this->NumBones = anim.JointCount;
	//	this->NumFrames = anim.FrameCount;
	//	this->poBoneResult = new Bone[this->NumBones + 1]();

	//	this->poHeadFrame = new Frame[this->NumFrames]();
	//	Frame* pCur = this->poHeadFrame;
	//	Frame* pPrev = nullptr;

	//	for (unsigned int i = 0; i < this->NumFrames; i++)
	//	{
	//		pCur->prevBucket = pPrev;
	//		if (pPrev)
	//		{
	//			pPrev->nextBucket = pCur;
	//		}
	//		
	//		this->poHeadFrame[i].KeyTime = anim.poFrames[i].Time * _Time(_Time::Duration::ONE_SECOND);
	//		this->poHeadFrame[i].poBone = new Bone[this->NumBones + 1]();

	//		for (unsigned int j = 0; j < this->NumBones; j++)
	//		{
	//			this->poHeadFrame[i].poBone[j].T.set(
	//				anim.poFrames[i].poBones[j].poTrans.x,
	//				anim.poFrames[i].poBones[j].poTrans.y,
	//				anim.poFrames[i].poBones[j].poTrans.z
	//			);

	//			this->poHeadFrame[i].poBone[j].R.set(
	//				anim.poFrames[i].poBones[j].poRot.x,
	//				anim.poFrames[i].poBones[j].poRot.y,
	//				anim.poFrames[i].poBones[j].poRot.z,
	//				anim.poFrames[i].poBones[j].poRot.w
	//			);

	//			this->poHeadFrame[i].poBone[j].S.set(
	//				anim.poFrames[i].poBones[j].poScale.x,
	//				anim.poFrames[i].poBones[j].poScale.y,
	//				anim.poFrames[i].poBones[j].poScale.z
	//			);
	//		}

	//		this->poHeadFrame[i].SSBO_Bones.Set(NumBones + 1, sizeof(Bone), this->poHeadFrame[i].poBone, GL_STATIC_DRAW);
	//		
	//		pPrev = pCur++;
	//		if (i < this->NumFrames - 1)
	//		{
	//			pPrev->nextBucket = pCur;
	//		}
	//		else
	//		{
	//			pPrev->nextBucket = nullptr;
	//		}
	//	}
	//}

	void Anim::SetBoneMap(AnimData& anim)
	{
		this->poMap = new BoneMap[anim.JointCount]();
		BoneMap* pCur = this->poMap;

		for (unsigned int i = 0; i < anim.JointCount; i++)
		{
			pCur->Set(anim, i);
			pCur++;
		}
	}

	void Anim::CustomAnimate(ShaderObject* _pAnimMixerSO, SSBO* keyA_array, SSBO* keyB_array, const float tS)
	{
		this->poMixer->Blend(_pAnimMixerSO, keyA_array, keyB_array, tS);
	}

	void Anim::SetCallback(Command* callback)
	{
		if (this->pCallback)
		{
			delete this->pCallback;
		}
		this->pCallback = callback;
	}

	unsigned int Anim::GetBoneIndex(unsigned int nodeIndex) const
	{
		BoneMap* pCur = this->poMap;
		unsigned int index = 0;

		while (index < this->NumBones && pCur->NodeIndex != nodeIndex )
		{
			pCur++;
			index++;
		}

		if (index < this->NumBones)
		{
			return index;
		}

		else
		{
			return this->NumBones + 1;
		}
	}
	SSBO* Anim::GetBoneResultSSBO() const
	{
		return this->poMixer->poSSBO_Result; 
	}

	Bone* Anim::GetFirstBone() const
	{
		return nullptr;
	}
}

