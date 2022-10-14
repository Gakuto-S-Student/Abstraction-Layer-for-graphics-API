/*===================================================================================
*	Date : 2022/10/14(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics_Cube12.h
*		Detail	:
===================================================================================*/
#pragma once
#include "Graphics_DirectX12.h"

class GraphicsCube12
{
public:
	//---------------------------------------------
	/// コンストラクタ 
	/// 
	/// \return	none
	//---------------------------------------------
	GraphicsCube12();

	//---------------------------------------------
	/// 初期化処理 
	/// 
	/// \return	none
	//---------------------------------------------
	void Init();

	//---------------------------------------------
	/// 終了処理 
	/// 
	/// \return	none
	//---------------------------------------------
	void Uninit();

	//---------------------------------------------
	/// 描画処理 
	/// 
	/// \return	none
	//---------------------------------------------
	void Draw(float x, float y, float z);

private:
	//--------------------------------------------------------------------------
	Microsoft::WRL::ComPtr<ID3D12Resource>			m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource>			m_textureBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource>			m_worldMatrixBuffer;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_textureHeap;
	//--------------------------------------------------------------------------

	/// <summary>
	/// ID3D12Resource			m_vertexBuffer;			// 頂点バッファ
	/// ID3D12Resource			m_textureBuffer;		// テクスチャリソース
	/// ID3D12Resource			m_worldMatrixBuffer;	// 定数バッファ
	/// ID3D12DescriptorHeap	m_textureHeap;			// テクスチャのヒープ
	/// </summary>

	//--------------------------------------------------------------------------
	DirectX::XMFLOAT3 m_translate;
	DirectX::XMFLOAT3 m_rotate;
	DirectX::XMFLOAT3 m_scale;
	//--------------------------------------------------------------------------

	/// <summary>
	/// DirectX::XMFLOAT3 m_translate;	// 平行移動
	/// DirectX::XMFLOAT3 m_rotate;		// 回転
	/// DirectX::XMFLOAT3 m_scale;		// スケーリング
	/// </summary>
};

