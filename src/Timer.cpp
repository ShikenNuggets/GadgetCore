#include "GCore/Timer.hpp"

using namespace Gadget;

Timer::Timer() : startTick(0), previousTick(0), currentTick(0)
{
	Reset();
}

void Timer::Update()
{
	previousTick = currentTick;
	currentTick = GetCurrentTick();
}

void Timer::Reset()
{
	startTick = GetCurrentTick();
	previousTick = startTick;
	currentTick = startTick;
}

double Timer::DeltaSeconds() const
{
	return TicksToSeconds(currentTick - previousTick);
}

double Timer::SecondsSinceLastUpdate() const
{
	return TicksToSeconds(GetCurrentTick() - currentTick);
}

double Timer::SecondsSinceStart() const
{
	return TicksToSeconds(currentTick - startTick);
}
