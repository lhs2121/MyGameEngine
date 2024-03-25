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

	void SetHinstance(HINSTANCE _HInst)
	{
		HInst = _HInst;
	}

	HINSTANCE GetHinstance() const
	{
		return HInst;
	}

	HINSTANCE HInst;
	HWND Hwnd;

	std::string Title = "String";

private:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void Register();
	void Create();

};

