#include "Pre.h"
#include "Device.h"
#include "VertexFormat.h"
#include "D3D11API.h"

void Device::InitMesh(IResManager* pManager)
{
	//Box2D
	{
		Vertex Box2D[] =
		{
			{float4(-0.5f, 0.5f), float2(0,0)},
			{float4( 0.5f, 0.5f), float2(1,0)},
			{float4( 0.5f,-0.5f), float2(1,1)},
			{float4(-0.5f,-0.5f), float2(0,1)}
		};
		IVertexBuffer* pVertexBuffer = (IVertexBuffer*)pManager->CreateResource( ResType::VB, "Box2D");
		pVertexBuffer->Setting( Box2D, sizeof(Vertex), sizeof(Box2D), 0);
	}

	{
		UINT Box2D[]
		{
			0,1,2,
			0,2,3
		};
		IIndexBuffer* pIndexBuffer = (IIndexBuffer*)pManager->CreateResource( ResType::IB, "Box2D");
		pIndexBuffer->Setting(Box2D, sizeof(Box2D));
	}

	//Box3D
	{
		Vertex Box3D[] =
		{
			// Front                      
			{ float4(-0.5f, 0.5f,-0.5f, 1.0f), float2(0,0) },
			{ float4( 0.5f, 0.5f,-0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f,-0.5f,-0.5f, 1.0f), float2(1,1) },
			{ float4(-0.5f,-0.5f,-0.5f, 1.0f), float2(0,1) },

			// Back                 
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f), float2(0,0) },
			{ float4( 0.5f, 0.5f, 0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f,-0.5f, 0.5f, 1.0f), float2(1,1) },
			{ float4(-0.5f,-0.5f, 0.5f, 1.0f), float2(0,1) },

			// Left                           
			{ float4(-0.5f, 0.5f,-0.5f, 1.0f), float2(0,0) },
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f), float2(1,0) },
			{ float4(-0.5f,-0.5f, 0.5f, 1.0f), float2(1,1) },
			{ float4(-0.5f,-0.5f,-0.5f, 1.0f), float2(0,1) },

			// Right                          
			{ float4(0.5f, 0.5f,-0.5f, 1.0f),  float2(0,0) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),  float2(1,0) },
			{ float4(0.5f,-0.5f, 0.5f, 1.0f),  float2(1,1) },
			{ float4(0.5f,-0.5f,-0.5f, 1.0f),  float2(0,1) },

			// Top                            
			{ float4(-0.5f, 0.5f,-0.5f, 1.0f), float2(0,0) },
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f, 0.5f, 0.5f, 1.0f), float2(1,1) },
			{ float4( 0.5f, 0.5f,-0.5f, 1.0f), float2(0,1) },

			// Bottom                         
			{ float4(-0.5f,-0.5f,-0.5f, 1.0f), float2(0,0) },
			{ float4(-0.5f,-0.5f, 0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f,-0.5f, 0.5f, 1.0f), float2(1,1) },
			{ float4( 0.5f,-0.5f,-0.5f, 1.0f), float2(0,1) }
		};

		IVertexBuffer* pVertexBuffer = (IVertexBuffer*)pManager->CreateResource(ResType::VB, "Box3D");
		pVertexBuffer->Setting(Box3D, sizeof(Vertex), sizeof(Box3D), 1);
	}

	{
		UINT Box3D[]
		{
			// Front
			0,1,2,
			2,3,0,

			// Back
			4,5,6,
			6,7,4,

			// Left
			8,9,10,
			10,11,8,

			// Right
			12,13,14,
			14,15,12,

			// Top
			16,17,18,
			18,19,16,

			// Bottom
			20,21,22,
			22,23,20
		};

		IIndexBuffer* pIndexBuffer = (IIndexBuffer*)pManager->CreateResource( ResType::IB, "Box3D");
		pIndexBuffer->Setting( Box3D, sizeof(Box3D));
	}

	// Circle2D
	{
		float4 Center = { 0.0f,0.0f };
		float4 Start = { 0.5f,0.0f };
		int PolygonCount = 32;
		float Rad = (2 * PI) / PolygonCount;
		
		float4x4 RotMat;
		RotMat.RotationZ(Rad);
		
		std::vector<Vertex> Vertiecs;
		Vertiecs.push_back({ Center });
		Vertiecs.push_back({ Start });
		for (size_t i = 0; i < PolygonCount; i++)
		{
			Start = Start * RotMat;
			Vertiecs.push_back({ Start });
		}

		std::vector<UINT> Indices;
		UINT CenterIndex = 0; 
		UINT First = 1;
		UINT Second = 2;
		for (size_t i = 0; i < PolygonCount; i++)
		{
			Indices.push_back(CenterIndex);
			Indices.push_back(First);
			Indices.push_back(Second);
			First++;
			Second++;
		}
		IVertexBuffer* pVertexBuffer = (IVertexBuffer*)pManager->CreateResource( ResType::VB, "Circle2D");
		pVertexBuffer->Setting( &Vertiecs[0], sizeof(Vertex),static_cast<int>(Vertiecs.size() * sizeof(Vertex)),0);

		IIndexBuffer* pIndexBuffer = (IIndexBuffer*)pManager->CreateResource( ResType::IB, "Circle2D");
		pIndexBuffer->Setting( &Indices[0], static_cast<int>(Indices.size() * sizeof(UINT)));
	}

}
