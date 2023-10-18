#include "TimeManager.h"
#include <windows.h>

using namespace std;

void TimeManager::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&g_cpuFrequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&g_prevCount));
}

void TimeManager::TimeUpdate()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	g_deltaTime = (currentCount - g_prevCount) / static_cast<float>(g_cpuFrequency);
	g_prevCount = currentCount;
	g_updateElapsed += g_deltaTime;
}
