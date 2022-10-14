/*===================================================================================
*	Date : 2022/10/14(Fri)
*		Author	: Gakuto.S
*		File	: Graphics_Cube12.cpp
*		Detail	:
===================================================================================*/
#include <algorithm>
#include "Graphics.h"

#include "Graphics_Cube12.h"
using namespace graphicsStructure; 
using namespace DirectX;


// モデルデータ
static const Vertex3D g_cubeMeta[]
{
	// 頂点座標              // uv座標
	{{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}},
	{{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}},
	{{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}},

	{{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}},
	{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}},
	{{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}},

	{{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}},
	{{ 1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},
	{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}},

	{{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},
	{{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},
	{{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}},

	{{-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}},
	{{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}},
	{{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}},

	{{ 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}},
	{{-1.0f, -1.0f,  1.0f}, {1.0f, 0.0f}},
	{{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}},

	{{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}},
	{{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}},
	{{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}},

	{{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}},
	{{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}},
	{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}},

	{{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}},
	{{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}},
	{{ 1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},

	{{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},
	{{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}},
	{{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},

	{{-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}},
	{{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}},
	{{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}},

	{{ 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}},
	{{-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}},
	{{-1.0f, -1.0f,  1.0f}, {1.0f, 0.0f}},
};

// コンストラクタ
GraphicsCube12::GraphicsCube12()
	:m_translate(),
	m_rotate(),
	m_scale()
{
}

// 初期化処理
void GraphicsCube12::Init()
{
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type					= D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;					// mapができる設定
	heapProperties.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;

	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension			= D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width				= sizeof(g_cubeMeta);
	resourceDesc.Height				= 1;
	resourceDesc.DepthOrArraySize	= 1;
	resourceDesc.MipLevels			= 1;
	resourceDesc.Format				= DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	resourceDesc.SampleDesc.Count	= 1;
	resourceDesc.Flags				= D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	resourceDesc.Layout				= D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT ret{};
	ID3D12Device* device = (ID3D12Device*)Graphics::Get()->Device();
	ret = device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		__uuidof(ID3D12Resource),
		(void**)m_vertexBuffer.GetAddressOf()
	);
	if (FAILED(ret))
	{// 頂点バッファの生成に失敗
		return;
	}

	// 定数バッファの生成
	resourceDesc.Width = (sizeof(XMMATRIX) + 0xff) & ~0xff;
	ret = device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		__uuidof(ID3D12Resource),
		(void**)m_worldMatrixBuffer.GetAddressOf()
	);
	if (FAILED(ret))
	{// 頂点バッファの生成に失敗
		return;
	}

	Vertex3D* vertexMap;
	m_vertexBuffer->Map(0, nullptr, (void**)&vertexMap);
	std::copy(std::begin(g_cubeMeta), std::end(g_cubeMeta), vertexMap);
	m_vertexBuffer->Unmap(0, nullptr);

	m_scale = XMFLOAT3(1, 1, 1);
}

// 終了処理
void GraphicsCube12::Uninit()
{
}

// 描画処理
void GraphicsCube12::Draw(float x, float y, float z)
{
	D3D12_VERTEX_BUFFER_VIEW bufferView{};
	bufferView.BufferLocation	= m_vertexBuffer->GetGPUVirtualAddress();
	bufferView.SizeInBytes		= sizeof(g_cubeMeta);
	bufferView.StrideInBytes	= sizeof(g_cubeMeta[0]);

	static float angle;
	angle += 0.01f;

	m_rotate.x = angle;
	m_rotate.y = angle;

	// テクスチャの設定
	// Graphics::Get()->SetTexture(m_textureHeap.Get());

	// モデルの行列を設定
	XMMATRIX trl, rot, scl;
	trl = XMMatrixTranslationFromVector({ x, y, z });
	rot = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_rotate));
	scl = XMMatrixScalingFromVector(XMLoadFloat3(&m_scale));

	XMMATRIX view, projection;
	view = XMMatrixLookAtLH({ 0, 5, 5 }, {}, { 0, 1, 0 });
	projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1280 / 780, 0.1f, 100.0f);

	XMMATRIX world = scl * rot * trl;
	world = XMMatrixTranspose(world * view * projection);

	XMMATRIX* worldBuffer;
	m_worldMatrixBuffer->Map(0, nullptr, (void**)&worldBuffer);
	*worldBuffer = world;
	m_worldMatrixBuffer->Unmap(0, nullptr);
	Graphics::Get()->SetWorldMatrix(m_worldMatrixBuffer->GetGPUVirtualAddress());

	ID3D12GraphicsCommandList* context = (ID3D12GraphicsCommandList*)Graphics::Get()->Context();

	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetVertexBuffers(0, 1, &bufferView);
	context->DrawInstanced(ARRAYSIZE(g_cubeMeta), 1, 0, 0);
}