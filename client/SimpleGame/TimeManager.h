#pragma once
#include "Config.h"

class TimeManager {

public:
	void Init();
	void TimeUpdate();

public:
	float GetUpdateTime() { return g_updateElapsed; }
	void OnUpdate() { g_updateElapsed -= UPDATE_FREQUENCY; }

private:
	uint64 g_cpuFrequency;
	uint64 g_prevCount;

	float g_updateElapsed;
	float g_frameTime;
	float g_deltaTime;
};