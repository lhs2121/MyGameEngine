#include "Pre.h"
#include "MediaAPI.h"
#include "EngineInput.h"
#include "EngineWindow.h"

void CreateEngineInput(IEngineInput** ppIEngineInput)
{
	*ppIEngineInput = new EngineInput();
}

void DeleteEngineInput(IEngineInput* pIEngineInput)
{
	delete (EngineInput*)(pIEngineInput);
}

void CreateEngineWindow(IEngineWindow** ppIEngineWindow)
{
	*ppIEngineWindow = new EngineWindow();
}

void DeleteEngineWindow(IEngineWindow* pIEngineWindow)
{
	delete (EngineWindow*)(pIEngineWindow);
}
