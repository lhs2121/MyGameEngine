#include "IEngineInput.h"
#include "EngineInput.h"

void CreateInput(IEngineInput** ppIEngineInput)
{
	*ppIEngineInput = new EngineInput();
}
