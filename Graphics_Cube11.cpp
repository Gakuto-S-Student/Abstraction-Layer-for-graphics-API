/*===================================================================================
*	Date : 2022/10/14(Fri)
*		Author	: Gakuto.S
*		File	: Graphics_Cube11.cpp
*		Detail	:
===================================================================================*/
#include "Graphics.h"

#include "Graphics_Cube11.h"
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
/* Initialize */
void GraphicsCube11::Init()
{
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(Vertex3D) * ARRAYSIZE(g_cubeMeta);
	bufferDesc.Usage     = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = g_cubeMeta;					// ここにモデルデータ

	ID3D11Device* device = (ID3D11Device*)Graphics::Get()->Device();
	device->CreateBuffer(&bufferDesc, &subResource, &m_vertexBuffer);

	// テクスチャの読み込みは此処に追加
	//m_textureResource = GraphicsTexture::CreateTexture();
}

/* Uninitialize */
void GraphicsCube11::Uninit()
{
	SAFE_RELEASE(m_vertexBuffer);
}

/* Draw */
void GraphicsCube11::Draw(float x, float y, float z)
{
	m_rotate.y += 0.01f;
	m_rotate.z += 0.01f;

	// 行列変換(model)
	XMMATRIX trl, rot, scl;
	trl = XMMatrixTranslation(x, y, z);
	rot = XMMatrixRotationRollPitchYaw(m_rotate.x, m_rotate.y, m_rotate.z);
	scl = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMMATRIX view, projection;
	view = XMMatrixLookAtLH({ 0, 5, 5 }, {0, 0, 0}, { 0, 1, 0 });
	projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1280 / 780, 0.1f, 100.0f);

	XMMATRIX world = scl * rot * trl;
	world = XMMatrixTranspose(world * view * projection);
	Graphics::Get()->SetWorldMatrix(world);

	// テクスチャデータの送信
	// Graphics::Get()->Context()->PSSetShaderResources(0, 1, &m_textureResource);

	ID3D11DeviceContext* context = (ID3D11DeviceContext*)Graphics::Get()->Context();

	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->Draw(ARRAYSIZE(g_cubeMeta), 0);
}
