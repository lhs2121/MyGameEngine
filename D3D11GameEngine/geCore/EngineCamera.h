#pragma once

class EngineCamera
{
public:
	// constrcuter destructer
	EngineCamera();
	~EngineCamera();

	// delete Function
	EngineCamera(const EngineCamera& _Other) = delete;
	EngineCamera(EngineCamera&& _Other) noexcept = delete;
	EngineCamera& operator=(const EngineCamera& _Other) = delete;
	EngineCamera& operator=(EngineCamera&& _Other) noexcept = delete;


private:

};