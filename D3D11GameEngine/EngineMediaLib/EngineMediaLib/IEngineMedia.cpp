#include "Pre.h"
#include "IEngineMedia.h"
#include "EngineInput.h"
#include "EngineWindow.h"

EngineMediaAPI void CreateEngineInput(IEngineInput** ppIEngineInput)
{
	*ppIEngineInput = new EngineInput();
}

EngineMediaAPI void DeleteEngineInput(IEngineInput* pIEngineInput)
{
	delete dynamic_cast<EngineInput*>(pIEngineInput);
}

EngineMediaAPI void CreateEngineWindow(IEngineWindow** ppIEngineWindow)
{
	*ppIEngineWindow = new EngineWindow();
}

EngineMediaAPI void DeleteEngineWindow(IEngineWindow* pIEngineWindow)
{
	delete dynamic_cast<EngineWindow*>(pIEngineWindow);
}
