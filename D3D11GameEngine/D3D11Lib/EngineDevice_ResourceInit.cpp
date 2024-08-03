#include "Pre.h"
#include "EngineDevice.h"
#include "EngineVertexFormat.h"
#include "D3D11API.h"

void EngineDevice::ResourceInit(IEngineD3DManager* pManager)
{
	{
		EngineDirectory Dir;

		Dir.GoChild("EngineShader");
		std::vector<EngineFile> AllShaderFile = Dir.GetAllFileExt(".fx");

		for (EngineFile& ShaderFile : AllShaderFile)
		{
			EngineString FileName = ShaderFile.GetFileName();
			EngineString FilePath = ShaderFile.GetPath();

			IEngineVertexShader* pVS = (IEngineVertexShader*)pManager->CreateResource(ResType::VS, FileName);
			pVS->Setting(FileName, FilePath);

			IEnginePixelShader* pPS = (IEnginePixelShader*)pManager->CreateResource(ResType::PS, FileName);
			pPS->Setting(FileName, FilePath);
		}
	}

	{
		IEngineInputLayout* pIA = (IEngineInputLayout*)pManager->CreateResource(ResType::IA, "POSITION");
		ShaderInput input[] = { ShaderInput::POSITION };
		pIA->SetDesc(input, 1);
	}

	{
		IEngineInputLayout* pIA = (IEngineInputLayout*)pManager->CreateResource(ResType::IA, "POSITION_COLOR");
		ShaderInput input[] = { ShaderInput::POSITION,ShaderInput::COLOR };
		pIA->SetDesc(input, 2);
	}

	{
		IEngineInputLayout* pIA = (IEngineInputLayout*)pManager->CreateResource(ResType::IA, "POSITION_TEXCOORD");
		ShaderInput input[] = { ShaderInput::POSITION,ShaderInput::TEXCOORD };
		pIA->SetDesc(input, 2);
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
		IEngineVertexBuffer* pVertexBuffer = (IEngineVertexBuffer*)pManager->CreateResource(ResType::VB, "Box2D");
		pVertexBuffer->Setting(Box2D, sizeof(float4), sizeof(Box2D), 0);
	}

	{
		UINT Box2D[]
		{
			0,1,2,
			0,2,3
		};
		IEngineIndexBuffer* pIndexBuffer = (IEngineIndexBuffer*)pManager->CreateResource(ResType::IB, "Box2D");
		pIndexBuffer->Setting(Box2D, sizeof(Box2D));
	}

	//Box2D with Tex
	{
		POSITION_TEXCOORD Box2D[] =
		{
			{float4(-0.5f, 0.5f), float2(0,0)},
			{float4( 0.5f, 0.5f), float2(1,0)},
			{float4( 0.5f,-0.5f), float2(1,1)},
			{float4(-0.5f,-0.5f), float2(0,1)}
		};
		IEngineVertexBuffer* pVertexBuffer = (IEngineVertexBuffer*)pManager->CreateResource(ResType::VB, "Box2DTex");
		pVertexBuffer->Setting(Box2D, sizeof(POSITION_TEXCOORD), sizeof(Box2D), 1);
	}

	//Box3D
	{
		POSITION_COLOR Box3D[] =
		{
			//�ո�                              //����
			{ float4(-0.5f, 0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ float4(0.5f, 0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ float4(0.5f,-0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ float4(-0.5f,-0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f) },

			//�޸�                              //�Ķ�
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f),  float4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),   float4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, 0.5f, 1.0f),  float4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, 0.5f, 1.0f), float4(0.0f, 0.0f, 1.0f, 1.0f) },

			//����                              //�ʷ�
			{ float4(-0.5f, 0.5f, -0.5f, 1.0f), float4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f),  float4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, 0.5f, 1.0f), float4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, -0.5f, 1.0f),float4(0.0f, 1.0f, 0.0f, 1.0f) },

			//������                             //����Ÿ
			{ float4(0.5f, 0.5f, -0.5f, 1.0f),  float4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),   float4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, 0.5f, 1.0f),  float4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 1.0f, 1.0f) },

			//����                               //�ϴ�
			{ float4(-0.5f, 0.5f, -0.5f, 1.0f), float4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f),  float4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),   float4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, -0.5f, 1.0f),  float4(0.0f, 1.0f, 1.0f, 1.0f) },

			//�Ʒ���                            //���
			{ float4(-0.5f, -0.5f, -0.5f, 1.0f),float4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, 0.5f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, 0.5f, 1.0f),  float4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, -0.5f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f) } ,
		};

		IEngineVertexBuffer* pVertexBuffer = (IEngineVertexBuffer*)pManager->CreateResource(ResType::VB, "Box3D");
		pVertexBuffer->Setting(Box3D, sizeof(POSITION_COLOR), sizeof(Box3D), 2);
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

		IEngineIndexBuffer* pIndexBuffer = (IEngineIndexBuffer*)pManager->CreateResource(ResType::IB, "Box3D");
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

		IEngineRasterizer* pRasterizer = (IEngineRasterizer*)pManager->CreateResource(ResType::RS, "Default");
		pRasterizer->Setting(Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		IEngineDepthStencil* pDepthStencil = (IEngineDepthStencil*)pManager->CreateResource(ResType::DS, "Default");
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

		IEngineSampler* NewSampler = (IEngineSampler*)pManager->CreateResource(ResType::Sampler, "Default");
		NewSampler->Setting(&Desc);
	}

	{
		EngineDirectory Dir;
		Dir.GoBase();
		Dir.GoChild("Assets");
		std::vector<EngineFile> Files = Dir.GetAllFileExt(".png");

		IEngineTexture* NewTexture = (IEngineTexture*)pManager->CreateResource(ResType::Texture, "Default");
		NewTexture->Setting(Files[0]);
	}

	{
		IMesh* NewMesh = (IMesh*)pManager->CreateResource(ResType::Mesh, "Box2D");
		NewMesh->Setting("Box2DTex", "Box2D");

		IMaterial* NewMat = (IMaterial*)pManager->CreateResource(ResType::Material, "Default");
		NewMat->Setting("TestSpriteShader");
	}
}