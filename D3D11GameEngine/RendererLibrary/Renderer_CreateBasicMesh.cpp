#include "pch.h"
#include "Renderer.h"

void CRenderer::CreateBasicMesh()
{
	SimpleVertex Rect2D[] =
	{
		{ float4(-0.5f, 0.5f, 0.0f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f, 0.5f, 0.0f, 1.0f), float2(1.0f, 0.0f) },
		{ float4(0.5f,-0.5f, 0.0f, 1.0f), float2(1.0f, 1.0f) },
		{ float4(-0.5f,-0.5f, 0.0f, 1.0f), float2(0.0f, 1.0f) }
	};

	USHORT Rect2DIndex[]
	{
		0,1,2,
		0,2,3
	};
	CreateMesh("Rect2D", Rect2D, sizeof(Rect2D), sizeof(SimpleVertex), Rect2DIndex, sizeof(Rect2DIndex), sizeof(USHORT));

	SimpleVertex Rect3D[] =
	{
		// front                     
		{ float4(-0.5f,  0.5f, -0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f,  0.5f, -0.5f, 1.0f), float2(1.0f, 0.0f) },
		{ float4(0.5f, -0.5f, -0.5f, 1.0f), float2(1.0f, 1.0f) },
		{ float4(-0.5f, -0.5f, -0.5f, 1.0f), float2(0.0f, 1.0f) },
		// back                
		{ float4(-0.5f, -0.5f,  0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f, -0.5f,  0.5f, 1.0f), float2(1.0f, 0.0f) },
		{ float4(0.5f,  0.5f,  0.5f, 1.0f), float2(1.0f, 1.0f) },
		{ float4(-0.5f,  0.5f,  0.5f, 1.0f), float2(0.0f, 1.0f) },
		// left                           
		{ float4(-0.5f,  0.5f,  0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(-0.5f,  0.5f, -0.5f, 1.0f), float2(1.0f, 0.0f) },
		{ float4(-0.5f, -0.5f, -0.5f, 1.0f), float2(1.0f, 1.0f) },
		{ float4(-0.5f, -0.5f,  0.5f, 1.0f), float2(0.0f, 1.0f) },
		// right                          
		{ float4(0.5f,  0.5f, -0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f,  0.5f,  0.5f, 1.0f), float2(1.0f, 0.0f) },
		{ float4(0.5f, -0.5f,  0.5f, 1.0f), float2(1.0f, 1.0f) },
		{ float4(0.5f, -0.5f, -0.5f, 1.0f), float2(0.0f, 1.0f) },
		// top                            
		{ float4(-0.5f,  0.5f,  0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f,  0.5f,  0.5f, 1.0f), float2(1.0f, 0.0f) },
		{ float4(0.5f,  0.5f, -0.5f, 1.0f), float2(1.0f, 1.0f) },
		{ float4(-0.5f,  0.5f, -0.5f, 1.0f), float2(0.0f, 1.0f) },
		// bottom                         
		{ float4(-0.5f, -0.5f, -0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f, -0.5f, -0.5f, 1.0f), float2(1.0f, 0.0f) },
		{ float4(0.5f, -0.5f,  0.5f, 1.0f), float2(1.0f, 1.0f) },
		{ float4(-0.5f, -0.5f,  0.5f, 1.0f), float2(0.0f, 1.0f) }
	};

	USHORT Rect3DIndex[]
	{
		// front
		0,1,2,
		2,3,0,
		// back
		4,5,6,
		6,7,4,
		// left
		8,9,10,
		10,11,8,
		// right
		12,13,14,
		14,15,12,
		// top
		16,17,18,
		18,19,16,
		// bottom
		20,21,22,
		22,23,20
	};

	CreateMesh("Rect3D", Rect3D, sizeof(Rect3D), sizeof(SimpleVertex), Rect3DIndex, sizeof(Rect3DIndex), sizeof(USHORT));
}