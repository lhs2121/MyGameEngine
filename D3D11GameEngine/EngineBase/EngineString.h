#pragma once

class EngineString
{
public:
	// constrcuter destructer
	EngineString();
	~EngineString();

	//constrcuter destructer
	EngineString(const EngineString& _Other) = delete;
	EngineString(EngineString&& _Other) noexcept = delete;
	EngineString& operator=(const EngineString& _Other) = delete;
	EngineString& operator=(EngineString&& _Other) noexcept = delete;

	static std::wstring ToWideByteString(std::string& _String);
};

