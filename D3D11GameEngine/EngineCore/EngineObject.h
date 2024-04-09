#pragma once

// Ό³Έν :
class EngineObject
{
public:
	// constrcuter destructer
	EngineObject();
	virtual ~EngineObject();

	// delete Function
	EngineObject(const EngineObject& _Other) = delete;
	EngineObject(EngineObject&& _Other) noexcept = delete;
	EngineObject& operator=(const EngineObject& _Other) = delete;
	EngineObject& operator=(EngineObject&& _Other) noexcept = delete;

	void SetName(std::string _Name)
	{
		Name = _Name;
	}

	virtual void Start();
	virtual void Update(float _Delta);
	virtual void Release();

private:
	std::string Name;
};