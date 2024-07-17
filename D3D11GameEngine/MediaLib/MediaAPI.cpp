#include "Pre.h"
#include "MediaAPI.h"
#include "EngineInput.h"
#include "EngineWindow.h"

MediaAPI void CreateEngineInput(IEngineInput** ppIEngineInput)
{
	*ppIEngineInput = new EngineInput();
}

MediaAPI void DeleteEngineInput(IEngineInput* pIEngineInput)
{
	delete dynamic_cast<EngineInput*>(pIEngineInput);
}

MediaAPI void CreateEngineWindow(IEngineWindow** ppIEngineWindow)
{
	*ppIEngineWindow = new EngineWindow();
}

MediaAPI void DeleteEngineWindow(IEngineWindow* pIEngineWindow)
{
	delete dynamic_cast<EngineWindow*>(pIEngineWindow);
}
