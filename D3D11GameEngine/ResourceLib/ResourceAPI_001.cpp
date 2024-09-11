#include "Pre.h"
#include "ResourceAPI.h"
#include "ResourceContainer.h"
#include "Device.h"

VertexBuffer* Resource::CreateVertexBuffer(const char* _name, void* pVertexStruct, UINT _structSize, UINT _formatSize)
{
	VertexBuffer* newBuffer = new VertexBuffer();
	newBuffer->name = _name;

	D3D11_BUFFER_DESC desc = { 0 };
	D3D11_SUBRESOURCE_DATA subData = { 0 };

	subData.pSysMem = pVertexStruct;

	desc.ByteWidth = _structSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	newBuffer->strides = _formatSize;
	newBuffer->offsets = 0;

	if (S_OK != Device::mainDevice->CreateBuffer(&desc, &subData, &newBuffer->pBuffer))
	{
		EngineDebug::MsgBoxAssert("버텍스버퍼 생성 실패");
	}

	ResourceContainer<VertexBuffer>::Resources.insert({ _name, newBuffer });
	return newBuffer;
}

IndexBuffer* Resource::CreateIndexBuffer(const char* _name, void* pIndexStruct, UINT _structSize)
{
	IndexBuffer* newBuffer = new IndexBuffer();
	newBuffer->name = _name;

	D3D11_BUFFER_DESC desc = { 0 };
	D3D11_SUBRESOURCE_DATA subData = { 0 };

	subData.pSysMem = pIndexStruct;

	desc.ByteWidth = _structSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	newBuffer->strides = sizeof(UINT);
	newBuffer->offsets = 0;
	newBuffer->count = _structSize / sizeof(UINT);

	Device::mainDevice->CreateBuffer(&desc, &subData, &newBuffer->pBuffer);

	ResourceContainer<IndexBuffer>::Resources.insert({ _name, newBuffer });

	return newBuffer;
}

InputLayout* Resource::CreateInputLayout(const char* _name, VertexShader* _pShader)
{
	InputLayout* newLayout = new InputLayout();
	newLayout->name = _name;
	newLayout->SetContext(Device::mainContext);
	D3D11_INPUT_ELEMENT_DESC desc[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,16,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	if (S_OK != Device::mainDevice->CreateInputLayout(desc, 3, _pShader->pBlob->GetBufferPointer(), _pShader->pBlob->GetBufferSize(), &newLayout->pLayout))
	{
		EngineDebug::MsgBoxAssert("인풋레이아웃 생성 실패.");
	}

	ResourceContainer<InputLayout>::Resources.insert(std::make_pair(_name,newLayout));

	return newLayout;
}

VertexShader* Resource::CreateVertexShader(const char* _name, const char* _path)
{
	VertexShader* newShader = new VertexShader();
	newShader->name = _name;

	EngineString stringPath = _path;
	EngineFile file;
	file.SetPath(stringPath.c_str());

	EngineString fileName = file.GetFileName();
	fileName += "_VS";

	wchar_t* path_wide;
	stringPath.GetUTF8(&path_wide);

	int flag;
#ifdef _DEBUG
	flag = D3DCOMPILE_DEBUG;

#endif
	flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* pErrorBlob = nullptr;

	HRESULT result0 = D3DCompileFromFile(path_wide,
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, fileName.c_str(), "vs_5_0", flag, 0, &newShader->pBlob, &pErrorBlob);

	HRESULT result1 = Device::mainDevice->CreateVertexShader(newShader->pBlob->GetBufferPointer(),
		newShader->pBlob->GetBufferSize(), nullptr, &newShader->pShader);

	if (path_wide != nullptr)
	{
		delete[] path_wide;
		path_wide = nullptr;
	}

	ResourceContainer<VertexShader>::Resources.insert({ _name, newShader });
	return newShader;
}

PixelShader* Resource::CreatePixelShader(const char* _name, const char* _path)
{
	PixelShader* newShader = new PixelShader();
	newShader->name = _name;

	EngineString stringPath = _path;
	EngineFile file;
	file.SetPath(stringPath.c_str());

	EngineString fileName = file.GetFileName();
	fileName += "_PS";

	wchar_t* path_wide;
	stringPath.GetUTF8(&path_wide);

	int flag;
#ifdef _DEBUG
	flag = D3DCOMPILE_DEBUG;

#endif
	flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* pErrorBlob = nullptr;

	HRESULT result0 = D3DCompileFromFile(path_wide,
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, fileName.c_str(), "ps_5_0", flag, 0, &newShader->pBlob, &pErrorBlob);

	HRESULT result1 = Device::mainDevice->CreatePixelShader(newShader->pBlob->GetBufferPointer(),
		newShader->pBlob->GetBufferSize(), nullptr, &newShader->pShader);

	if (path_wide != nullptr)
	{
		delete[] path_wide;
		path_wide = nullptr;
	}

	ResourceContainer<PixelShader>::Resources.insert({ _name, newShader });
	return newShader;
}

