#pragma once
#include "IEngineMedia.h"

class EngineWindow : public IEngineWindow
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

	void Init(const char* _WindowTile, float4 _WindowPos, float4 _WindowSize, const HINSTANCE _hInst, void(*UpdataFunc)(void), void(*ReleaseFunc)(void)) override;
	void MessageLoop() override;

	const char* GetWindowTitle() override;
	float4 GetWindowSize() const override;
	float4 GetWindowPos() const override;
	HINSTANCE GethInst() const override;
	HWND* GethWnd() override;

private:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	void(*UpdatePtr)(void) = nullptr;
	void(*ReleasePtr)(void) = nullptr;

	const char*  WindowTitle;
	float4       WindowPos;
	float4       WindowSize;
	HINSTANCE    hInst;
	HWND         hWnd;
};

