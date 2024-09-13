#include "Pre.h"
#include "RenderManager.h"
#include "VertexFormat.h"
#include "ResourceAPI.h"
#include "ResMap.h"

void RenderManager::InitMesh()
{
	//Debug::CrtSetBreakAlloc(758);
	//Box2D
	{
		Vertex Box2D[] =
		{
			{float4(-0.5f, 0.5f), float2(0,0)},
			{float4( 0.5f, 0.5f), float2(1,0)},
			{float4( 0.5f,-0.5f), float2(1,1)},
			{float4(-0.5f,-0.5f), float2(0,1)}
		};

		Resource::CreateVertexBuffer("Box2D", Box2D, sizeof(Box2D), sizeof(Vertex));
	}

	{
		UINT Box2D[]
		{
			0,1,2,
			0,2,3
		};

		Resource::CreateIndexBuffer("Box2D", Box2D, sizeof(Box2D));
	}

	//Box3D
	{
		Vertex Box3D[] =
		{
			// front                     
			{ float4(-0.5f, 0.5f,-0.5f, 1.0f), float2(0,0) },
			{ float4( 0.5f, 0.5f,-0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f,-0.5f,-0.5f, 1.0f), float2(1,1) },
			{ float4(-0.5f,-0.5f,-0.5f, 1.0f), float2(0,1) },

			// back                
			{ float4(-0.5f,-0.5f, 0.5f, 1.0f), float2(0,0) },
			{ float4( 0.5f,-0.5f, 0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f,0.5f, 0.5f, 1.0f), float2(1,1) },
			{ float4(-0.5f,0.5f, 0.5f, 1.0f), float2(0,1) },

			// left                           
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f), float2(0,0) },
			{ float4(-0.5f, 0.5f,-0.5f, 1.0f), float2(1,0) },
			{ float4(-0.5f,-0.5f,-0.5f, 1.0f), float2(1,1) },
			{ float4(-0.5f,-0.5f, 0.5f, 1.0f), float2(0,1) },

			// right                          
			{ float4(0.5f, 0.5f,-0.5f, 1.0f),  float2(0,0) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),  float2(1,0) },
			{ float4(0.5f,-0.5f, 0.5f, 1.0f),  float2(1,1) },
			{ float4(0.5f,-0.5f,-0.5f, 1.0f),  float2(0,1) },

			// top                            
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f), float2(0,0) },
			{ float4( 0.5f, 0.5f, 0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f, 0.5f,-0.5f, 1.0f), float2(1,1) },
			{ float4(-0.5f, 0.5f,-0.5f, 1.0f), float2(0,1) },

			 // bottom                         
			{ float4(-0.5f,-0.5f, -0.5f, 1.0f), float2(0,0) }, //20
			{ float4( 0.5f,-0.5f, -0.5f, 1.0f), float2(1,0) }, //21
			{ float4( 0.5f,-0.5f, 0.5f, 1.0f), float2(1,1) }, //22
			{ float4(-0.5f,-0.5f, 0.5f, 1.0f), float2(0,1) }  //23
		};

		Resource::CreateVertexBuffer("Box3D", Box3D, sizeof(Box3D), sizeof(Vertex));
	}

	{
		UINT Box3D[]
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

		Resource::CreateIndexBuffer("Box3D", Box3D, sizeof(Box3D));
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

		int structSize = static_cast<int>(Vertiecs.size() * sizeof(Vertex));
		int indexStructSize = static_cast<int>(Indices.size() * sizeof(UINT));

		Resource::CreateVertexBuffer("Circle2D", &Vertiecs[0], structSize, sizeof(Vertex));
		Resource::CreateIndexBuffer("Circle2D", &Indices[0], indexStructSize);
	}

	{
		Mesh* newMesh = Resource::CreateMesh("Box2D");
		newMesh->pVertexBuffer = ResMap<VertexBuffer>::Find("Box2D");
		newMesh->pIndexBuffer = ResMap<IndexBuffer>::Find("Box2D");
	}

	{
		Mesh* newMesh = Resource::CreateMesh("Box3D");
		newMesh->pVertexBuffer = ResMap<VertexBuffer>::Find("Box3D");
		newMesh->pIndexBuffer = ResMap<IndexBuffer>::Find("Box3D");
	}

	{
		Mesh* newMesh = Resource::CreateMesh("Circle2D");
		newMesh->pVertexBuffer = ResMap<VertexBuffer>::Find("Circle2D");
		newMesh->pIndexBuffer = ResMap<IndexBuffer>::Find("Circle2D");
	}

}
