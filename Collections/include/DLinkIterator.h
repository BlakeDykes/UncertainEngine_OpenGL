#pragma once

#include "IteratorBase.h"

namespace Uncertain
{
	class DLink;

	class DLinkIterator : public IteratorBase
	{
	public:
		DLink* pHead;
		DLink* pCur;
		bool Done;

		DLinkIterator();

		virtual NodeBase* Next() override;
		virtual bool IsDone() override;
		virtual NodeBase* First() override;
		virtual NodeBase* Current() override;

		virtual IteratorBase* Reset(NodeBase* _pHead) override;

	private:
		void Clear();
	};
}
