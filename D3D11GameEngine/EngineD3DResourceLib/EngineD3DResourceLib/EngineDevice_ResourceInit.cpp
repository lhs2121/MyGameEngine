#include "Pre.h"
#include "EngineD3DInterface.h"
#include "EngineD3DManager.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineRasterizer.h"
#include "EngineDepthStencil.h"
#include "EngineVertexFormat.h"
#include "EngineVertexFormat.h"

void EngineDevice::ResourceInit(void* pManager)
{
	EngineD3DManager* Manager = (EngineD3DManager*)pManager;

	{
		EngineDirectory Dir;
		Dir.GoChild("EngineShader");
		std::vector<EngineFile> AllShaderFile;
		Dir.GetAllFileExt(&AllShaderFile, ".fx");

		for (EngineFile& ShaderFile : AllShaderFile)
		{
			IEngineVertexShader* pVertexShader = Manager->CreateVertexShader(ShaderFile.GetFileName());
			pVertexShader->Setting(ShaderFile.GetFileName(), ShaderFile.GetPath());

			IEnginePixelShader* pPixelShader = Manager->CreatePixelShader(ShaderFile.GetFileName());
			pPixelShader->Setting(ShaderFile.GetFileName(), ShaderFile.GetPath());
		}
	}

	//IA����
	{
		{
			EngineVertexShader* TestVertexShader = (EngineVertexShader*)Manager->FindVertexShader("Test2DShader");

			D3D11_INPUT_ELEMENT_DESC Desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			IEngineInputLayout* pInputLayout = Manager->CreateInputLayout("Pos");
			pInputLayout->Setting(Desc, 1, TestVertexShader->GetShaderByteCode(), TestVertexShader->GetShaderByteLength());
		}

		{
			EngineVertexShader* TestVertexShader = (EngineVertexShader*)Manager->FindVertexShader("Test3DShader");

			D3D11_INPUT_ELEMENT_DESC Desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			IEngineInputLayout* pInputLayout = Manager->CreateInputLayout("PosColor");
			pInputLayout->Setting(Desc, 2, TestVertexShader->GetShaderByteCode(), TestVertexShader->GetShaderByteLength());
		}

		{
			EngineVertexShader* TestVertexShader = (EngineVertexShader*)Manager->FindVertexShader("TestSpriteShader");

			D3D11_INPUT_ELEMENT_DESC Desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			IEngineInputLayout* pInputLayout = Manager->CreateInputLayout("PosTexcoord");
			pInputLayout->Setting(Desc, 2, TestVertexShader->GetShaderByteCode(), TestVertexShader->GetShaderByteLength());
		}

	}

	//Box2D
	{
		float4 Box2D[] =
		{
			float4(-0.5f, 0.5f),
			float4(0.5f, 0.5f),
			float4(0.5f, -0.5f),
			float4(-0.5f, -0.5f)
		};
		IEngineVertexBuffer* pVertexBuffer = Manager->CreateVertexBuffer("Box2D");
		pVertexBuffer->Setting(Box2D, sizeof(float4), sizeof(Box2D));
	}

	{
		UINT Box2D[]
		{
			0,1,2,
			0,2,3
		};
		IEngineIndexBuffer* pIndexBuffer = Manager->CreateIndexBuffer("Box2D");
		pIndexBuffer->Setting(Box2D, sizeof(Box2D));
	}

	//Box2D with Tex
	{
		VERTEX_POS_TEXCOORD Box2D[] =
		{
			{float4(-0.5f, 0.5f), 0, 0},
			{float4(0.5f, 0.5f), 1, 0},
			{float4(0.5f,-0.5f), 1, 1},
			{float4(-0.5f,-0.5f), 0, 1}
		};
		IEngineVertexBuffer* pVertexBuffer = Manager->CreateVertexBuffer("Box2DTex");
		pVertexBuffer->Setting(Box2D, sizeof(VERTEX_POS_TEXCOORD), sizeof(Box2D));
	}

	//Box3D
	{
		VERTEX_POS_COLOR Box3D[] =
		{
			//�ո�
			//����
			{ float4(-0.5f, 0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ float4( 0.5f, 0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ float4( 0.5f,-0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ float4(-0.5f,-0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f) },

			//�޸�
			//�Ķ�
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f),  float4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),   float4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, 0.5f, 1.0f),  float4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, 0.5f, 1.0f), float4(0.0f, 0.0f, 1.0f, 1.0f) },

			//����
			//�ʷ�
			{ float4(-0.5f, 0.5f, -0.5f, 1.0f), float4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f),  float4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, 0.5f, 1.0f), float4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, -0.5f, 1.0f),float4(0.0f, 1.0f, 0.0f, 1.0f) },

			//������
			//����Ÿ
			{ float4(0.5f, 0.5f, -0.5f, 1.0f),  float4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),   float4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, 0.5f, 1.0f),  float4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 1.0f, 1.0f) },

			//����
			//�ϴ�
			{ float4(-0.5f, 0.5f, -0.5f, 1.0f), float4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f),  float4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),   float4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, -0.5f, 1.0f),  float4(0.0f, 1.0f, 1.0f, 1.0f) },

			//�Ʒ���
			//���
			{ float4(-0.5f, -0.5f, -0.5f, 1.0f),float4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, 0.5f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, 0.5f, 1.0f),  float4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, -0.5f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f) } ,
		};

		IEngineVertexBuffer* pVertexBuffer = Manager->CreateVertexBuffer("Box3D");
		pVertexBuffer->Setting(Box3D, sizeof(VERTEX_POS_COLOR), sizeof(Box3D));
	}

	{
		UINT Box3D[]
		{
			//�ո�
			0,1,2,
			2,3,0,

			//�޸�
			4,5,6,
			6,7,4,

			//����
			8,9,10,
			10,11,8,

			//������
			12,13,14,
			14,15,12,

			//����
			16,17,18,
			18,19,16,

			//�Ʒ���
			20,21,22,
			22,23,20
		};

		IEngineIndexBuffer* pIndexBuffer = Manager->CreateIndexBuffer("Box3D");
		pIndexBuffer->Setting(Box3D, sizeof(Box3D));
	}

	{
		D3D11_RASTERIZER_DESC Desc;

		Desc.FillMode = D3D11_FILL_SOLID;
		Desc.CullMode = D3D11_CULL_NONE;
		Desc.FrontCounterClockwise = false;
		Desc.DepthBias = 0;
		Desc.DepthBiasClamp = 0;
		Desc.SlopeScaledDepthBias = 0;
		Desc.DepthClipEnable = false;
		Desc.ScissorEnable = false;
		Desc.MultisampleEnable = false;
		Desc.AntialiasedLineEnable = false;

		IEngineRasterizer* pRasterizer = Manager->CreateRasterizer("Default");
		pRasterizer->Setting(Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		IEngineDepthStencil* pDepthStencil = Manager->CreateDepthStencil("Default");
		pDepthStencil->Setting(Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = {};
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // ���� ���͸�
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;    // U �������� �� ��巹��
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;    // V �������� �� ��巹��
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;    // W �������� �� ��巹��
		Desc.MipLODBias = 0.0f;                        // Mipmap ���� ������
		Desc.MaxAnisotropy = 1;                        // �ִ� �̹漺 ���͸� ���� (1�� �̹漺 ���͸� ��Ȱ��ȭ)
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS; // �� �Լ�
		Desc.BorderColor[0] = 1.0f;                    // �׵θ� ���� (RGBA)
		Desc.BorderColor[1] = 1.0f;
		Desc.BorderColor[2] = 1.0f;
		Desc.BorderColor[3] = 1.0f;
		Desc.MinLOD = 0;                               // �ּ� Mipmap ����
		Desc.MaxLOD = D3D11_FLOAT32_MAX;               // �ִ� Mipmap ����

		IEngineSampler* NewSampler = Manager->CreateSampler("Default");
		NewSampler->Setting(&Desc);
	}

}