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
	EngineInput* castptr = (EngineInput*)pIEngineInput;
	delete castptr;
}

void CreateEngineWindow(IEngineWindow** ppIEngineWindow)
{
	*ppIEngineWindow = new EngineWindow();
}

void DeleteEngineWindow(IEngineWindow* pIEngineWindow)
{
	EngineWindow* castptr = (EngineWindow*)pIEngineWindow;
	delete castptr;
}
