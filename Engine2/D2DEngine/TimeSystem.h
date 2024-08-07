#pragma once
#include <Windows.h>

#define timeManager TimeManager::GetInstance()

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	static TimeManager* GetInstance();
	static void DestroyInstance();

	void InitTime();
	void UpdateTime();
	const float GetFrameRate();
	const float GetDeltaTime();

	void SetTimeScale(float scale);
	float GetTimeScale() { return _TimeScale; }

private:
	LARGE_INTEGER _CurTime;
	LARGE_INTEGER _PrevTime;
	LARGE_INTEGER _Frequency;

	float _DeltaTime;
	float _TimeScale;

	static TimeManager* Instance;
};