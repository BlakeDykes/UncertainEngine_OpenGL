#include "TimerController.h"

namespace Uncertain
{

	TimerController::TimerController(_Time Min, _Time Max)
		: tCurr(_Time::Duration::ZERO),
		tMin(Min),
		tMax(Max)
	{
	}

	bool TimerController::Update(_Time delta)
	{
		tCurr += delta;

		// protection for time values for looping
		if (tCurr < tMin)
		{
			tCurr = tMax;
			return false;
		}
		else if (tCurr > tMax)
		{
			tCurr = tMin;
			return true;
		}
		else
		{
			return false;
		}
	}
}

// --- End of File ---
