#include "Pre.h"
#include "EngineDepthStencil.h"

EngineDepthStencil::EngineDepthStencil()
{
}

EngineDepthStencil::~EngineDepthStencil()
{
	if (m_pDepthStencil != nullptr)
	{
		m_pDepthStencil->Release();
	}
}

void EngineDepthStencil::IntoPipeLine()
{
	Device->GetContext()->OMSetDepthStencilState(m_pDepthStencil, 1);
}
