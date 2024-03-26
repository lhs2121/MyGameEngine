#pragma once

class EngineWindow
{
public:
	// constrcuter destructer
	EngineWindow();
	~EngineWindow();

	// constrcuter destructer
	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

	void OpenWindow();
	void MessageLoop();

	inline void SetWinPos(const float4 Value)
	{
		WinPos = Value;
	}

	inline void SetWinSize(const float4 Value)
	{
		WinSize = Value;
	}

	inline void SetWinTitle(const std::string Value)
	{
		WinTitle = Value;
	}

	inline void SetHinstance(const HINSTANCE _HInst)
	{
		HInst = _HInst;
	}

	HINSTANCE GetHinstance() const
	{
		return HInst;
	}

	HINSTANCE HInst;
	HWND Hwnd;

	std::string WinTitle;
	float4 WinSize;
	float4 WinPos;

private:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void Register();
	void Create();

};

