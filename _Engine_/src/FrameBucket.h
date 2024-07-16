#ifndef FRAME_BUCKET_H
#define FRAME_BUCKET_H

#include "DLink.h"
#include "_Time.h"
#include "Bone.h"
#include "SSBO.h"
#include "AnimNames.h"
#include "AnimData.h"

namespace Uncertain
{

	struct SBOFrame
	{
		SBOFrame();
		~SBOFrame();
		SBOFrame(const SBOFrame&) = delete;
		const SBOFrame& operator=(const SBOFrame&) = delete;

		_Time KeyTime;
		SSBO* SSBO_Bones;
	};

	class FrameBucket : public DLink
	{
	public:
		FrameBucket();
		FrameBucket(const FrameBucket&) = delete;
		const FrameBucket operator=(const FrameBucket&) = delete;
		virtual ~FrameBucket();

		void Set(AnimName name, AnimData& anim);
		void SetName(AnimName name) { this->Name = name; }

		_Time GetMaxTime() const;
		SBOFrame* GetFrames() const { return poFrames; }
		unsigned int GetNumFrames() const { return this->NumFrames; }
		unsigned int GetNumBones() const { return this->NumBones; }

		virtual void Wash() override;
		virtual bool Compare(NodeBase& pNode) override;
		virtual const char* GetName() override;

	private:

		AnimName Name;
		unsigned int NumBones;
		unsigned int NumFrames;
		SBOFrame* poFrames;
	};
}



#endif // !FRAME_BUCKET_H

