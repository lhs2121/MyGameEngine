#pragma once

// Ό³Έν :
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

	template<typename LevelType>
	static EngineLevel* CreateLevel(std::string LevelName)
	{
		EngineLevel* NewLevel = new LevelType();
		NewLevel->SetName(LevelName);
		NewLevel->Start();
		return NewLevel;
	}

	void Start() override;
	void Update(float _Delta) override;
protected:
	
}; 

