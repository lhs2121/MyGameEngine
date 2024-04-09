#pragma once

// ���� :
class EngineLevel : public EngineObject
{
public:
	// constrcuter destructer
	EngineLevel();
	~EngineLevel();

	// delete Function
	EngineLevel(const EngineLevel& _Other) = delete;
	EngineLevel(EngineLevel&& _Other) noexcept = delete;
	EngineLevel& operator=(const EngineLevel& _Other) = delete;
	EngineLevel& operator=(EngineLevel&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _Delta) override;

protected:
	std::list<EngineObject*> AllObject;
	
}; 

