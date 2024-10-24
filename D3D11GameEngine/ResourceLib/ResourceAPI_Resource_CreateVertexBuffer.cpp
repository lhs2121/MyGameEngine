#include "Pre.h"
#include "ResourceAPI.h"
#include "ResMap.h"

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

	if (S_OK != Device::GetDevice()->CreateBuffer(&desc, &subData, &newBuffer->pBuffer))
	{
		Debug::MsgBoxAssert("버텍스버퍼 생성 실패");
	}

	ResMap<VertexBuffer>::map.insert({ _name, newBuffer });
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

	Device::GetDevice()->CreateBuffer(&desc, &subData, &newBuffer->pBuffer);

	ResMap<IndexBuffer>::map.insert({ _name, newBuffer });

	return newBuffer;
}

InputLayout* Resource::CreateInputLayout(const char* _name, VertexShader* _pShader)
{
	InputLayout* newLayout = new InputLayout();
	newLayout->SetContext(Device::GetContext());
	newLayout->name = _name;
	newLayout->desc =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,16,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	if (S_OK != Device::GetDevice()->CreateInputLayout(&newLayout->desc[0], 3, _pShader->pBlob->GetBufferPointer(), _pShader->pBlob->GetBufferSize(), &newLayout->pLayout))
	{
		Debug::MsgBoxAssert("인풋레이아웃 생성 실패.");
	}

	ResMap<InputLayout>::map.insert(std::make_pair(_name,newLayout));

	return newLayout;
}

VertexShader* Resource::CreateVertexShader(const char* _name, base::string& _path)
{
	VertexShader* newShader = new VertexShader();
	newShader->name = _name;

	wchar_t* path_wide;
	_path.w_str(&path_wide);

	base::string fileName = _path.get_name();
	fileName += "_VS";


	int flag;
#ifdef _DEBUG
	flag = D3DCOMPILE_DEBUG;

#endif
	flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* pErrorBlob = nullptr;

	HRESULT result0 = D3DCompileFromFile(path_wide,nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		fileName.c_str(), "vs_5_0", flag, 0, &newShader->pBlob, &pErrorBlob);

	HRESULT result1 = Device::GetDevice()->CreateVertexShader(newShader->pBlob->GetBufferPointer(),
		newShader->pBlob->GetBufferSize(), nullptr, &newShader->pShader);

	if (path_wide != nullptr)
	{
		delete[] path_wide;
		path_wide = nullptr;
	}

	ResMap<VertexShader>::map.insert({ _name, newShader });
	return newShader;
}

PixelShader* Resource::CreatePixelShader(const char* _name, base::string& _path)
{
	PixelShader* newShader = new PixelShader();
	newShader->name = _name;

	wchar_t* path_wide;
	_path.w_str(&path_wide);

	base::string fileName = _path.get_name();
	fileName += "_PS";

	int flag;
#ifdef _DEBUG
	flag = D3DCOMPILE_DEBUG;

#endif
	flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* pErrorBlob = nullptr;

	HRESULT result0 = D3DCompileFromFile(path_wide,
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, fileName.c_str(), "ps_5_0", flag, 0, &newShader->pBlob, &pErrorBlob);

	HRESULT result1 = Device::GetDevice()->CreatePixelShader(newShader->pBlob->GetBufferPointer(),
		newShader->pBlob->GetBufferSize(), nullptr, &newShader->pShader);

	if (path_wide != nullptr)
	{
		delete[] path_wide;
		path_wide = nullptr;
	}

	ResMap<PixelShader>::map.insert({ _name, newShader });
	return newShader;
}

