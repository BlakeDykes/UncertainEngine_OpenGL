#ifndef TIMER_CONTROLLER_H
#define TIMER_CONTROLLER_H

#include "_Time.h"

namespace Uncertain
{
	class TimerController
	{
	public:
		TimerController(_Time min, _Time max);

		TimerController() = delete;
		TimerController(const TimerController&) = delete;
		TimerController& operator = (const TimerController&) = delete;
		~TimerController() = default;

		bool Update(_Time delta);

		void SetCurrTime(const _Time time) { this->tCurr = time; };
		_Time GetCurrTime() const { return this->tCurr; };

		void SetMaxTime(const _Time time) { this->tMax = time; }
		_Time GetMaxTime() const { return this->tMax; }

		void SetMinTime(const _Time time) { this->tMin = time; }
		_Time GetMinTime() const { return this->tMin; }

	private:
		_Time tCurr;
		_Time tDelta;
		_Time tMin;
		_Time tMax;
	};
}

#endif