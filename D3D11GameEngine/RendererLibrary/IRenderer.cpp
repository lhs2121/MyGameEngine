#include "pch.h"
#include "IRenderer.h"
#include "Renderer.h"

void CreateRenderer(IRenderer** ppRenderer)
{
    *ppRenderer = new CRenderer();
}

void DeleteRenderer(IRenderer* pRenderer)
{
    CRenderer* pCast = (CRenderer*)pRenderer;
    delete pCast;
}
