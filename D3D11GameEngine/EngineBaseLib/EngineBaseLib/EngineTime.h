#pragma once

class __declspec(dllexport) EngineTime
{
public:
	// constrcuter destructer
	EngineTime();
	~EngineTime();

	//constrcuter destructer
	EngineTime(const EngineTime& _Other) = delete;
	EngineTime(EngineTime&& _Other) noexcept = delete;
	EngineTime& operator=(const EngineTime& _Other) = delete;
	EngineTime& operator=(EngineTime&& _Other) noexcept = delete;

	void Init();
	void CountStart();
	float CountEnd();

protected:
	LARGE_INTEGER Frequency;
	LARGE_INTEGER Start;
	LARGE_INTEGER End;
};

