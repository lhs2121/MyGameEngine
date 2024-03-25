#pragma once

// Ό³Έν :
class EngineObject
{
public:
	// constrcuter destructer
	EngineObject();
	~EngineObject();

	// delete Function
	EngineObject(const EngineObject& _Other) = delete;
	EngineObject(EngineObject&& _Other) noexcept = delete;
	EngineObject& operator=(const EngineObject& _Other) = delete;
	EngineObject& operator=(EngineObject&& _Other) noexcept = delete;

protected:
	virtual void Start() = 0;
	virtual void Update(float _Delta) = 0;
	virtual void Release() = 0;

	std::string a = "asdas";
};